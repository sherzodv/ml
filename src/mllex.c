#include "mllex.h"
#include "thirdparty/utf8proc.h"
#include <string.h>

#ifdef DEBUG
#include <stdio.h>
#endif

static inline enum ml_error ml_lccontent(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_ccontent(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_cdata(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_ascii_symbol(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_lt(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_gt(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_slash(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_identifier(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_measure(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_rgb_value(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_uri(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_attribute_value(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_quoted_string(struct ml_lex_ctxt*, struct ml_token*, uint8_t quote);
static inline enum ml_error ml_single_quoted_string(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_double_quoted_string(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_eq(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_space(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_comment(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_script(struct ml_lex_ctxt*, struct ml_token*);
static inline enum ml_error ml_proc_instr_closer(struct ml_lex_ctxt*, struct ml_token*);

/* 
 * Lex states:
 * 	The order should be keeped, as states are used as indexes of internal
 * 	tables.
 */
#define MLMAX_STATE 12
enum ml_state_type {
	MLSTATE_INITIAL				= 0
	, MLSTATE_START_TAG_OPENED		= 1
	, MLSTATE_DTD_OPENED			= 2
	, MLSTATE_ELEMENT_IDENTIFIED		= 3
	, MLSTATE_ATTR_EQ_FOUND			= 4
	, MLSTATE_ATTR_VALUE_FOUND		= 5
	, MLSTATE_ELEMENT_OPENED		= 6
	, MLSTATE_ELEMENT_CONTENT_FOUND		= 7
	, MLSTATE_END_TAG_OPENED		= 8
	, MLSTATE_END_TAG_IDENTIFIER_FOUND	= 9
	, MLSTATE_SCRIPT_ELEMENT_IDENTIFIED	= 10
	, MLSTATE_PROC_INSTR_OPENED		= 11
	, MLSTATE_PROC_INSTR_CLOSED		= 12
};

#include "mllextbl.c"

int ml_prevch(struct ml_lex_ctxt* l)
{
	l->curr -= l->rres;
	
	if (l->curr >= l->end)
	{
		l->error = MLERR_EOF;
		l->errmsg = "No data left.";
		return l->error;
	}

	l->res = l->rres;
	l->ch = l->rch;

	if (l->res == 0)
	{
		l->error = MLERR_EOF;
		l->errmsg = "No data left.";
		return l->error;
	}

	if (l->res < 0)
	{
		l->error = MLERR_ENCODING;
		l->errmsg = utf8proc_errmsg(l->res);
		return l->error;
	}
	
	return ML_OK;
}

int ml_nextch(struct ml_lex_ctxt* l)
{
	l->curr += l->res;

	if (l->curr >= l->end)
	{
		l->error = MLERR_EOF;
		l->errmsg = "No data left.";
		return l->error;
	}

	l->rres = l->res;
	l->rch = l->ch;
	l->res = utf8proc_iterate(l->curr, 4, &l->ch);

	if (l->res == 0)
	{
		l->error = MLERR_EOF;
		l->errmsg = "No data left.";
		return l->error;
	}

	if (l->res < 0)
	{
		l->error = MLERR_ENCODING;
		l->errmsg = utf8proc_errmsg(l->res);
		return l->error;
	}
	
	return ML_OK;
}

enum ml_error ml_init_lex(struct ml_lex_ctxt* l
	, const char* data_start
	, const char* data_end
	, int (*nextch)(struct ml_lex_ctxt* l)
	, int (*prevch)(struct ml_lex_ctxt* l))
{
	l->start = data_start;
	l->end = data_end;
	l->curr = data_start;

	l->error = 0;
	l->errmsg = "";

	l->ch = 0;
	l->state = 0;
	l->ttype = 0;
	l->res = 0;
	l->rres = 0;

	l->nextch = nextch != NULL ? nextch : ml_nextch;
	l->prevch = prevch != NULL ? prevch : ml_prevch;

	l->internal = MLSTATE_INITIAL;

	ml_fill_transition_table();

	return l->nextch(l);
}

void ml_copy(struct ml_lex_ctxt* src, struct ml_lex_ctxt* dst)
{
	*dst = *src;
}

static inline enum ml_error ml_parse(struct ml_lex_ctxt* l, struct ml_token* t)
{
	switch (l->state)
	{
		case MLSTATE_INITIAL:

			if (l->ch != '<')
				return ml_ccontent(l, t);

			break;

		case MLSTATE_START_TAG_OPENED:
		
			if (l->ch == 's' || l->ch == 'S')
			{
				enum ml_error result = ml_identifier(l, t);
				if (ml_string2tag(t->start, t->end) == MLWORD_script)
					l->internal = MLSTATE_SCRIPT_ELEMENT_IDENTIFIED;
				return result;
			}

			break;

		case MLSTATE_ATTR_VALUE_FOUND:

			if (l->ch == '\'' || l->ch == '"')
				return ml_ascii_symbol(l, t);

			break;

		case MLSTATE_ATTR_EQ_FOUND:

			return ml_attribute_value(l, t);

		case MLSTATE_ELEMENT_OPENED:
		case MLSTATE_ELEMENT_CONTENT_FOUND:

			if (l->internal == MLSTATE_SCRIPT_ELEMENT_IDENTIFIED)
			{
				enum ml_error result =  ml_script(l, t);
				l->internal = MLSTATE_INITIAL;
				return result;
			}

			if (l->ch == '<')
				return ml_lt(l, t);

			return ml_ccontent(l, t);

		case MLSTATE_END_TAG_OPENED:

			if (l->internal == MLSTATE_SCRIPT_ELEMENT_IDENTIFIED)
				l->internal = MLSTATE_INITIAL;
			break;
	}
	
	if (l->ch <= 127)
		return ascii[l->ch].parse(l, t);
	
	return ml_lccontent(l, t);
}

enum ml_error ml_next_token(struct ml_lex_ctxt* l, struct ml_token* t)
{
	l->state = transition[l->state][l->ttype];
	//l->state = ml_transition(l->state, t->type);
	enum ml_error result = ml_parse(l, t);
	l->ttype = t->type;
	return result;
}

// quoted string
// terminated with quote, quote escaping allowed quotequote, \quote
static inline enum ml_error ml_quoted_string(struct ml_lex_ctxt* l, struct ml_token* t, uint8_t quote)
{
	t->start = l->curr + l->res;
	uint32_t save_ch = l->ch;
	int end_detected = 0;
	while (l->nextch(l) == ML_OK)
	{
		if (end_detected)
		{
			if(l->ch == quote)
			{
				end_detected = 0;
				save_ch = 0;
				continue;
			}

			t->end = l->curr - l->res;
			return l->error;
		}

		if (l->ch == quote)
		{
			if (save_ch == '\\')
			{
				save_ch = 0;
				continue;
			}

			end_detected = 1;
			continue;
		}
		
		if (l->ch == '\\' && save_ch == '\\')
			save_ch = 0;
		else
			save_ch = l->ch;
	}
	
	t->end = l->curr;
	return l->error;
}

// attribute value
// terminated with quote only
static inline enum ml_error ml_attribute_value(struct ml_lex_ctxt* l, struct ml_token* t)
{
	uint8_t quote = l->ch;
	switch (quote)
	{
		case '\'':
			t->type = MLTOKEN_SINGLE_QUOTED_STRING;
			break;
		case '"':
			t->type = MLTOKEN_DOUBLE_QUOTED_STRING;
			break;
		case '#':
			return ml_rgb_value(l, t);
		case '/':
			return ml_uri(l, t);
		case '>':
			return ml_gt(l, t);
		default:
			t->type = MLTOKEN_DOUBLE_QUOTED_STRING;
			t->start = l->curr;
			while (l->nextch(l) == ML_OK)
				if (l->ch == ' ' || l->ch == '>')
				{
					t->end = l->curr;
					return l->error;
				}
			t->end = l->curr;
			return l->error;
	}
	t->start = l->curr + l->res;
	while (l->nextch(l) == ML_OK)
		if (l->ch == quote)
		{
			t->end = l->curr;
			l->nextch(l);
			return l->error;
		}
	t->end = l->curr;
	return l->error;
}

// uri
static inline enum ml_error ml_uri(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->type = MLTOKEN_URI;
	t->start = l->curr;
	while (l->nextch(l) == ML_OK)
		if (l->ch <= 127 && !ascii[l->ch].isuri)
			break;
	t->end = l->curr;
	return l->error;
}

// Measure (100px, 53)
// [0-9][a-zA-Z0-9_-]*
static inline enum ml_error ml_measure(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->start = l->curr;
	t->type = MLTOKEN_MEASURE;
	while (l->nextch(l) == ML_OK)
		if (l->ch <= 127 || !ascii[l->ch].isibody
			|| l->ch == '-' || l->ch == '+')
			break;
	t->end = l->curr;
	return l->error;
}

// RGB color definition
// [a-zA-Z_][a-zA-Z0-9_-]*
static inline enum ml_error ml_rgb_value(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->type = MLTOKEN_RGB_VALUE;
	t->start = l->curr;
	while (l->nextch(l) == ML_OK)
		if (l->ch <= 127 && !ascii[l->ch].isdigit && !ascii[l->ch].ishexdigit)
			break;
	t->end = l->curr;
	return l->error;
}

// non ascii ccontent
static inline enum ml_error ml_lccontent(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->type = MLTOKEN_LCCONTENT;
	t->start = l->curr;
	while (l->nextch(l) == ML_OK)
		if (l->ch <= 127 && !ascii[l->ch].isspace && !ascii[l->ch].islccontent)
			break;
	t->end = l->curr;
	return l->error;
}

// any content containing ascii characters including scripts, styles
static inline enum ml_error ml_ccontent(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->type = MLTOKEN_CCONTENT;
	t->start = l->curr;

	while (l->nextch(l) == ML_OK)
		if (l->ch == '<')
		{
			t->end = l->curr;
			return ML_OK;
		}

	t->end = l->curr;
	return l->error;
}

// CDATA
static inline enum ml_error ml_cdata(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->type = MLTOKEN_CDATA;

	if (l->nextch(l) != ML_OK)
	{
		t->start = l->curr;
		t->end = l->curr;
		return l->error;
	}

	t->start = l->curr;

	uint8_t ch1 = 0, ch2 = 0, ch3 = 0;

	while (!(ch1 == ']' && ch2 == ']' && ch3 == '>'))
	{
		if (l->nextch(l) != ML_OK)
			break;

		ch1 = ch2;
		ch2 = ch3;
		ch3 = l->ch;
	}

	if (l->error == ML_OK)
		t->end = l->curr - 2;
	else
		t->end = l->curr;

	return l->error;
}

// comment
static inline enum ml_error ml_comment(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->type = MLTOKEN_COMMENT;

	if (l->nextch(l) != ML_OK)
	{
		t->start = l->curr;
		t->end = l->curr;
		return ML_OK;
	}
		
	t->start = l->curr;

	uint8_t ch1 = 0, ch2 = 0, ch3 = 0;

	while (!(ch1 == '-' && ch2 == '-' && ch3 == '>'))
	{
		if (l->nextch(l) != ML_OK)
			break;

		ch1 = ch2;
		ch2 = ch3;
		ch3 = l->ch;
	}

	if (l->error == ML_OK)
	{
		t->end = l->curr - 2;
		l->nextch(l);
		return l->error;
	}
	
	t->end = l->curr;
	return l->error;
}

// script
static inline enum ml_error ml_script(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->type = MLTOKEN_SCRIPT;

	t->start = l->curr;

	struct ml_lex_ctxt save_l;
	struct ml_token temp_t;

	while (1)
	{
		if (l->ch == '\'' || l->ch == '"')
			if (ml_quoted_string(l, &temp_t, l->ch) != ML_OK)
				break;
		
		if (l->ch == '<')
		{
			t->end = l->curr;

			ml_copy(l, &save_l);

			if (l->nextch(l) == ML_OK) if (l->ch == '/')
			{
				ml_copy(&save_l, l);
				return l->error;
			}
		}
		
		if (l->nextch(l) != ML_OK)
			break;
	}

	t->end = t->start;
	return l->error;
}

// '<[:space]/'
static inline enum ml_error ml_lt(struct ml_lex_ctxt* l, struct ml_token*t)
{
	t->type = MLTOKEN_LT;
	
	if (l->nextch(l) != ML_OK)
		return l->error;

	struct ml_lex_ctxt save_l;
	enum ml_error tmp_r = ML_OK;
	ml_copy(l, &save_l);

	while (ascii[l->ch].isspace)
		tmp_r = l->nextch(l);

	if (tmp_r == ML_OK)
		switch (l->ch)
		{
			case '/': 
				
				t->type = MLTOKEN_END_TAG_OPENER;
				return l->nextch(l);

			case '?':

				t->type = MLTOKEN_PROC_INSTR_OPENER;
				return l->nextch(l);

			case '!': 
				
				ml_copy(l, &save_l);

				if (l->nextch(l) == ML_OK)
				{
					switch (l->ch)
					{
						case '-':
							if (l->nextch(l) == ML_OK) if (l->ch == '-')
								return ml_comment(l, t);
							break;

						case '[':
							if (l->nextch(l) == ML_OK) if (l->ch == 'C')
							if (l->nextch(l) == ML_OK) if (l->ch == 'D')
							if (l->nextch(l) == ML_OK) if (l->ch == 'A')
							if (l->nextch(l) == ML_OK) if (l->ch == 'T')
							if (l->nextch(l) == ML_OK) if (l->ch == 'A')
							if (l->nextch(l) == ML_OK) if (l->ch == '[')
								return ml_cdata(l, t);
							break;
					}
				}

				t->type = MLTOKEN_DTD_OPENER;
				ml_copy(&save_l, l);
				return l->nextch(l);
		}

	ml_copy(&save_l, l);
	return l->error;
}

// '/[:space]>'
static inline enum ml_error ml_slash(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->ch = l->ch;
	t->type = MLTOKEN_ASCII_SYMBOL;

	if (l->nextch(l) != ML_OK)
		return l->error;

	struct ml_lex_ctxt save_l;
	enum ml_error tmp_r = ML_OK;
	ml_copy(l, &save_l);

	while (l->ch <= 127 && ascii[l->ch].isspace)
		tmp_r = l->nextch(l);

	if (tmp_r != ML_OK || l->ch != '>')
	{
		ml_copy(&save_l, l);
		return l->error;
	}

	t->type = MLTOKEN_START_TAG_CLOSER;
	return l->nextch(l);
}

// '?>'
static inline enum ml_error ml_proc_instr_closer(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->ch = l->ch;
	t->type = MLTOKEN_ASCII_SYMBOL;

	if (l->nextch(l) != ML_OK)
		return l->error;

	if (l->ch != '>')
		return l->error;

	t->type = MLTOKEN_PROC_INSTR_CLOSER;
	return l->nextch(l);
}

// ascii symbol
static inline enum ml_error ml_ascii_symbol(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->type = MLTOKEN_ASCII_SYMBOL;
	t->ch = l->ch;
	return l->nextch(l);
}

// '>'
static inline enum ml_error ml_gt(struct ml_lex_ctxt* l, struct ml_token*t)
{
	t->type = MLTOKEN_GT;
	return l->nextch(l);
}

// '='
static inline enum ml_error ml_eq(struct ml_lex_ctxt* l, struct ml_token*t)
{
	t->type = MLTOKEN_EQ;
	return l->nextch(l);
}

// Element name or any text wich format is like element name
// [a-zA-Z_][a-zA-Z0-9_-]*
static inline enum ml_error ml_identifier(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->start = l->curr;
	t->type = MLTOKEN_IDENTIFIER;
	while (l->nextch(l) == ML_OK)
		if (l->ch > 127 || !ascii[l->ch].isibody)
			break;
	t->end = l->curr;
	return l->error;
}

// single quoted string
// terminated with ' or vertical space
static inline enum ml_error ml_single_quoted_string(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->type = MLTOKEN_SINGLE_QUOTED_STRING;
	return ml_quoted_string(l, t, '\'');
}

// double quoted string
// terminated with " or vertical space
static inline enum ml_error ml_double_quoted_string(struct ml_lex_ctxt* l, struct ml_token* t)
{
	t->type = MLTOKEN_DOUBLE_QUOTED_STRING;
	return ml_quoted_string(l, t, '"');
}

// [:space]
static inline enum ml_error ml_space(struct ml_lex_ctxt* l, struct ml_token*t)
{
	t->start = l->curr;
	t->type = MLTOKEN_SPACE;

	while (l->nextch(l) == ML_OK)
		if (l->ch > 127 || !ascii[l->ch].isspace)
		{
			t->end = l->curr;
			return l->error;
		}

	t->end = l->curr;
	return l->nextch(l);
}

#ifdef DEBUG

const char* mld_token2string(enum ml_token_type t)
{
	switch (t)
	{
		case MLTOKEN_LT:
			return "TOKEN_LT (<)";
		case MLTOKEN_GT:
			return "TOKEN_GT (>)";
		case MLTOKEN_EQ:
			return "TOKEN_EQ (=)";
		case MLTOKEN_IDENTIFIER:
			return "TOKEN_IDENTIFIER";
		case MLTOKEN_LCCONTENT:
			return "TOKEN_LCCONTENT";
		case MLTOKEN_CCONTENT:
			return "TOKEN_CCONTENT";
		case MLTOKEN_CDATA:
			return "TOKEN_CDATA";
		case MLTOKEN_ASCII_SYMBOL:
			return "TOKEN_ASCII_SYMBOL";
		case MLTOKEN_START_TAG_CLOSER:
			return "TOKEN_START_TAG_CLOSER (/>)";
		case MLTOKEN_END_TAG_OPENER:
			return "TOKEN_END_TAG_OPENER (</)";
		case MLTOKEN_DTD_OPENER:
			return "TOKEN_DTD_OPENER (<!)";
		case MLTOKEN_COMMENT:
			return "TOKEN_COMMENT";
		case MLTOKEN_SCRIPT:
			return "TOKEN_SCRIPT";
		case MLTOKEN_SINGLE_QUOTED_STRING:
			return "TOKEN_SINGLE_QUOTED_STRING";
		case MLTOKEN_DOUBLE_QUOTED_STRING:
			return "TOKEN_DOUBLE_QUOTED_STRING";
		case MLTOKEN_SPACE:
			return "TOKEN_SPACE";
		case MLTOKEN_MEASURE:
			return "TOKEN_MEASURE";
		case MLTOKEN_RGB_VALUE:
			return "TOKEN_RGB_VALUE";
		case MLTOKEN_URI:
			return "TOKEN_URI";
		case MLTOKEN_PROC_INSTR_OPENER:
			return "TOKEN_PROC_INSTR_OPENER (<?)";
		case MLTOKEN_PROC_INSTR_CLOSER:
			return "TOKEN_PROC_INSTR_CLOSER (?>)";
		default:
			return "unknown_token";
	}
}

void mld_print_token(FILE* f, struct ml_token* t)
{
	const uint8_t* s = 0;
	s = t->start;
	fprintf(f, "%s: ", mld_token2string(t->type));
	switch (t->type)
	{
		case MLTOKEN_LT:
		case MLTOKEN_GT:
		case MLTOKEN_EQ:
		case MLTOKEN_START_TAG_CLOSER:
		case MLTOKEN_END_TAG_OPENER:
		case MLTOKEN_DTD_OPENER:
		case MLTOKEN_PROC_INSTR_OPENER:
		case MLTOKEN_PROC_INSTR_CLOSER:
			break;
		case MLTOKEN_ASCII_SYMBOL:
			fprintf(f, " %c", t->ch);
			break;
		case MLTOKEN_SPACE:
			while (s != t->end)
				fprintf(f, "%d ", *s++);
			break;
		default:
			while (s != t->end)
				fprintf(f, "%c", *s++);
	}
	fprintf(f, "\n");
}

void mld_print_state(FILE* f, enum ml_state_type state)
{
	switch (state) {
		case MLSTATE_INITIAL:
			fprintf(f, "MLSTATE_INITIAL\n");
			break;
		case MLSTATE_START_TAG_OPENED:
			fprintf(f, "MLSTATE_START_TAG_OPENED\n");
			break;
		case MLSTATE_DTD_OPENED:
			fprintf(f, "MLSTATE_DTD_OPENED\n");
			break;
		case MLSTATE_ELEMENT_IDENTIFIED:
			fprintf(f, "MLSTATE_ELEMENT_IDENTIFIED\n");
			break;
		case MLSTATE_ATTR_EQ_FOUND:
			fprintf(f, "MLSTATE_ATTR_EQ_FOUND\n");
			break;
		case MLSTATE_ATTR_VALUE_FOUND:
			fprintf(f, "MLSTATE_ATTR_VALUE_FOUND\n");
			break;
		case MLSTATE_ELEMENT_OPENED:
			fprintf(f, "MLSTATE_ELEMENT_OPENED\n");
			break;
		case MLSTATE_ELEMENT_CONTENT_FOUND:
			fprintf(f, "MLSTATE_ELEMENT_CONTENT_FOUND\n");
			break;
		case MLSTATE_END_TAG_OPENED:
			fprintf(f, "MLSTATE_END_TAG_OPENED\n");
			break;
		case MLSTATE_END_TAG_IDENTIFIER_FOUND:
			fprintf(f, "MLSTATE_END_TAG_IDENTIFIER_FOUND\n");
			break;
		case MLSTATE_SCRIPT_ELEMENT_IDENTIFIED:
			fprintf(f, "MLSTATE_SCRIPT_ELEMENT_IDENTIFIED\n");
			break;
	}
}

#endif

