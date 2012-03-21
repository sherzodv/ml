#include "lexer.h"
#include "ext/utf8proc/utf8proc.h"
#include "ustream.h"

/* tokenizer states according to whatwg.org */
enum lstate
{
	LSTATE_DATA					/* 12.2.4.1 */
	, LSTATE_CHARREF_IN_DATA			/* 12.2.4.2 */
	, LSTATE_RCDATA					/* 12.2.4.3 */
	, LSTATE_CHARREF_IN_RCDATA			/* 12.2.4.4 */
	, LSTATE_RAWTEXT				/* 12.2.4.5 */
	, LSTATE_SCRIPT_DATA				/* 12.2.4.6 */
	, LSTATE_PLAIN_TEXT				/* 12.2.4.7 */
	, LSTATE_TAG_OPEN				/* 12.2.4.8 */
	, LSTATE_END_TAG_OPEN				/* 12.2.4.9 */
	, LSTATE_TAG_NAME				/* 12.2.4.10 */
	, LSTATE_RCDATA_LT_SIGN				/* 12.2.4.11 */
	, LSTATE_RCDATA_END_TAG_OPEN			/* 12.2.4.12 */
	, LSTATE_RCDATA_END_TAG_NAME			/* 12.2.4.13 */
	, LSTATE_RAWTEXT_LT_SIGN			/* 12.2.4.14 */
	, LSTATE_RAWTEXT_END_TAG_OPEN			/* 12.2.4.15 */
	, LSTATE_RAWTEXT_END_TAG_NAME			/* 12.2.4.16 */
	, LSTATE_SCRIPT_DATA_LT				/* 12.2.4.17 */
	, LSTATE_SCRIPT_DATA_END_TAG_OPEN		/* 12.2.4.18 */
	, LSTATE_SCRIPT_DATA_END_TAG_NAME		/* 12.2.4.19 */
	, LSTATE_SCRIPT_DATA_ESCAPE_START		/* 12.2.4.20 */
	, LSTATE_SCRIPT_DATA_ESCAPE_START_DASH		/* 12.2.4.21 */
	, LSTATE_SCRIPT_DATA_ESCAPED			/* 12.2.4.22 */
	, LSTATE_SCRIPT_DATA_ESCAPED_DASH		/* 12.2.4.23 */
	, LSTATE_SCRIPT_DATA_ESCAPED_DASH_DASH		/* 12.2.4.24 */
	, LSTATE_SCRIPT_DATA_ESCAPED_LT			/* 12.2.4.25 */
	, LSTATE_SCRIPT_DATA_ESCAPED_END_TAG_OPEN	/* 12.2.4.26 */
	, LSTATE_SCRIPT_DATA_ESCAPED_END_TAG_NAME	/* 12.2.4.27 */
	, LSTATE_SCRIPT_DATA_DOUBLE_ESCAPE_START	/* 12.2.4.28 */
	, LSTATE_SCRIPT_DATA_DOUBLE_ESCAPED		/* 12.2.4.29 */
	, LSTATE_SCRIPT_DATA_DOUBLE_ESCAPED_DASH	/* 12.2.4.30 */
	, LSTATE_SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH	/* 12.2.4.31 */
	, LSTATE_SCRIPT_DATA_DOUBLE_ESCAPED_LT		/* 12.2.4.32 */
	, LSTATE_SCRIPT_DATA_DOUBLE_ESCAPE_END		/* 12.2.4.33 */
	, LSTATE_BEFORE_ATTRIBUTE_NAME			/* 12.2.4.34 */
	, LSTATE_ATTRIBUTE_NAME				/* 12.2.4.35 */
	, LSTATE_AFTER_ATTRIBUTE_NAME			/* 12.2.4.36 */
	, LSTATE_BEFORE_ATTRIBUTE_VALUE			/* 12.2.4.37 */
	, LSTATE_ATTRIBUTE_VALUE_DQUOTED		/* 12.2.4.38 */
	, LSTATE_ATTRIBUTE_VALUE_SQUOTED		/* 12.2.4.39 */
	, LSTATE_ATTRIBUTE_VALUE_UNQUOTED		/* 12.2.4.40 */
	, LSTATE_CHARREF_IN_ATTRIBUTE_VALUE		/* 12.2.4.41 */
	, LSTATE_AFTER_ATTRIBUTE_VALUE_QUOTED		/* 12.2.4.42 */
	, LSTATE_SELF_CLOSING_START_TAG			/* 12.2.4.43 */
	, LSTATE_BOGUS_COMMENT				/* 12.2.4.44 */
	, LSTATE_MARKUP_DECLARATION_OPEN		/* 12.2.4.45 */
	, LSTATE_COMMENT_START				/* 12.2.4.46 */
	, LSTATE_COMMENT_START_DASH			/* 12.2.4.47 */
	, LSTATE_COMMENT				/* 12.2.4.48 */
	, LSTATE_COMMENT_END_DASH			/* 12.2.4.49 */
	, LSTATE_COMMENT_END				/* 12.2.4.50 */
	, LSTATE_COMMENT_END_BANG			/* 12.2.4.51 */
	, LSTATE_DOCTYPE				/* 12.2.4.52 */
	, LSTATE_BEFORE_DOCTYPE_NAME			/* 12.2.4.53 */
	, LSTATE_DOCTYPE_NAME				/* 12.2.4.54 */
	, LSTATE_AFTER_DOCTYPE_NAME			/* 12.2.4.55 */
	, LSTATE_AFTER_DOCTYPE_PUBLIC_KEYWORD		/* 12.2.4.56 */
	, LSTATE_BEFORE_DOCTYPE_PUBLIC_IDENTIFIER	/* 12.2.4.57 */
	, LSTATE_DOCTYPE_PUBLIC_IDENTIFIER_DQUOTED	/* 12.2.4.58 */
	, LSTATE_DOCTYPE_PUBLIC_IDENTIFIER_SQUOTED	/* 12.2.4.59 */
	, LSTATE_AFTER_DOCTYPE_PUBLIC_IDENTIFIER	/* 12.2.4.60 */
	, LSTATE_BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS
							/* 12.2.4.61 */ 
	, LSTATE_AFTER_DOCTYPE_SYSTEM_KEYWORD		/* 12.2.4.62 */
	, LSTATE_BEFORE_DOCTYPE_SYSTEM_IDENTIFIER	/* 12.2.4.63 */
	, LSTATE_DOCTYPE_SYSTEM_IDENTIFIER_DQUOTED	/* 12.2.4.64 */
	, LSTATE_DOCTYPE_SYSTEM_IDENTIFIER_SQUOTED	/* 12.2.4.65 */
	, LSTATE_AFTER_DOCTYPE_SYSTEM_IDENTIFIER	/* 12.2.4.66 */
	, LSTATE_BOGUS_DOCTYPE				/* 12.2.4.67 */
	, LSTATE_CDATA_SECTION_STATE			/* 12.2.4.68 */
};

struct context
{
	struct ustream* stream;
	enum lstate state;
};

#define CONTEXT(l) ((struct context*)(l->context))
#define STATE(l) (CONTEXT(l)->state)
#define STREAM(l) (CONTEXT(l)->stream)
#define NEXTCH(l) do {						\
	l->mistake = STREAM(l)->next(STREAM(l));		\
} while (0)
#define SWITCH(l, s) do { STATE(l) = s; } while(0)
#define EMIT_CURR_CHAR(l) do { 					\
	l->token.type = HTML_TOKEN_CHARACTER;			\
	l->token.data.ch = STREAM(l)->point;			\
	l->emit(&l->token);					\
} while (0)

int slexer_next(struct lexer* l)
{
	while (1) {
		switch (STATE(l)) {
			case LSTATE_DATA: {
				NEXTCH(l);
				if (l->mistake == STRM_END) {
					l->token.type = HTML_TOKEN_EOF;
					l->emit(&l->token);
					continue;
				}
				switch (STREAM(l)->point) {

					case 0x0026: /* AMPERSAND (&) */
						SWITCH(l, LSTATE_CHARREF_IN_DATA);
						continue;
					case 0x003C: /* LESS-THAN SIGN (<) */
						SWITCH(l, LSTATE_TAG_OPEN);
						continue;
					case 0x0000:
					default:
						EMIT_CURR_CHAR(l);
						continue;
				}
				break;
			}
			/* ... */
			/* Do all other 67 states. */
			/* ... */
		}
	}

	return OK;
}

int slexer_prev(struct lexer* l)
{
	return OK;
}

/* string lexer's context */
struct context* create_scontext(struct sstring* ss)
{
	struct context *ctxt = (struct context *)malloc(sizeof(struct context));
	ctxt->stream = new_sustream(ss);
	if (!ctxt->stream) {
		free(ctxt);
		return NULL;
	}
	ctxt->state = LSTATE_DATA;
	return ctxt;
}

void free_scontext(struct context* ctxt)
{
	if (ctxt) {
		delete_sustream(ctxt->stream);
		free(ctxt);
	}
}

/* string lexer */
struct lexer* new_slexer(struct sstring* ss)
{
	struct lexer *l = (struct lexer *)malloc(sizeof(struct lexer));
	if (!l)
		return NULL;
	l->context = create_scontext(ss);
	if (!l->context) {
		free(l);
		return NULL;
	}
	l->next = slexer_next;
	l->prev = slexer_prev;
	return l;
}

void delete_slexer(struct lexer *l)
{
	if (l) {
		free_scontext(l->context);
		free(l);
	}
}

