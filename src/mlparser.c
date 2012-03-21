#include "mlparser.h"

#include <assert.h>
#include <string.h>

#define MLPARSER_STACK_SEGMENT_COUNT 100
#define MLPARSER_STACK_SEGMENT_SIZE 10000

#ifdef DEBUG
#include <stdio.h>
#endif

/* parser states */
enum ml_pstate {
	MLPSTATE_START
	, MLPSTATE_START_TAG_START 
	, MLPSTATE_START_TAG_NAME
	, MLPSTATE_START_TAG
	, MLPSTATE_END_TAG_START
	, MLPSTATE_END_TAG_NAME
	, MLPSTATE_ATTRIBUTE_NAME
	, MLPSTATE_ATTRIBUTE_EQ
};

/* right hand sides of the reduction rules */
enum ml_rule {
	MLRULE_TOKEN
	, MLRULE_ATTRIBUTE
	, MLRULE_ATTRIBUTE_LIST
	, MLRULE_START_TAG
	, MLRULE_ELEMENT
};

/* reduction product */
struct ml_prod {
	enum ml_rule type;
	union {
		struct ml_dom_text* text;
		struct ml_dom_attribute* attribute;
		struct ml_dom_element* element;
		struct ml_token token;
	} as;
};

/* dom data container */
struct ml_dom_data {
	uint8_t* dstart;	/* data stream start */
	uint8_t* dend;		/* data stream end */
	MLSTACK(struct ml_dom_attribute) astack;
	MLSTACK(struct ml_dom_element) estack;
};

struct ml_parser_ctxt {
	MLSTACK(enum ml_pstate) sstack;		/* state stack */
	MLSTACK(struct ml_prod) pstack;		/* production stack */
	
	/* 
	 * ddata contains dom tree elements
	 * and will be past to ml_dom
	 */
	struct ml_dom_data* ddata;

	/* helper fields, to avoid using local variables */
	enum ml_pstate state;
	struct ml_token token;
	struct ml_prod* prod;

#ifdef DEBUG
	FILE* log;
#endif
};

#ifdef DEBUG

void mld_print_prod(FILE* f, struct ml_prod* p)
{
	fprintf(f, "************** production rule ******************\n");
	switch (p->type) {
		case MLRULE_TOKEN:
			fprintf(f, "MLRULE_TOKEN: ");
			mld_print_token(f, &p->as.token);
			break;
		case MLRULE_ATTRIBUTE:
			fprintf(f, "MLRULE_ATTRIBUTE\n");
			break;
		case MLRULE_ATTRIBUTE_LIST:
			fprintf(f, "MLRULE_ATTRIBUTE_LIST\n");
			break;
		case MLRULE_START_TAG:
			fprintf(f, "MLRULE_START_TAG\n");
			break;
		case MLRULE_ELEMENT:
			fprintf(f, "MLRULE_ELEMENT\n");
			break;
		default:
			fprintf(f, "MLRULE:unknown\n");
			break;
	}
	fprintf(f, "************** production rule end ******************\n");
}

void mld_print_pstate(FILE* f, enum ml_pstate state)
{
	switch (state) {
		case MLPSTATE_START:
			fprintf(f,"MLPSTATE_START\n");
			break;
		case MLPSTATE_START_TAG_START:
			fprintf(f,"MLPSTATE_START_TAG_START\n");
			break;
		case MLPSTATE_START_TAG_NAME:
			fprintf(f,"MLPSTATE_START_TAG_NAME\n");
			break;
		case MLPSTATE_START_TAG:
			fprintf(f,"MLPSTATE_START_TAG\n");
			break;
		case MLPSTATE_END_TAG_START:
			fprintf(f,"MLPSTATE_END_TAG_START\n");
			break;
		case MLPSTATE_END_TAG_NAME:
			fprintf(f,"MLPSTATE_END_TAG_NAME\n");
			break;
		case MLPSTATE_ATTRIBUTE_NAME:
			fprintf(f,"MLPSTATE_ATTRIBUTE_NAME\n");
			break;
		case MLPSTATE_ATTRIBUTE_EQ:
			fprintf(f,"MLPSTATE_ATTRIBUTE_EQ\n");
			break;
	}
}

#endif

static inline int ml_is_element_simple(struct ml_parser_ctxt* p)
{
	struct ml_prod* prod = MLSTACK_TOP(&(p->pstack));
	assert("The top of the stack is not an element" && prod->type == MLRULE_START_TAG);
	switch (ml_string2tag(prod->as.element->start, prod->as.element->end)) {
		case MLWORD_img:
		case MLWORD_meta:
		case MLWORD_link:
#ifdef DEBUG
			fprintf(p->log, "--------------------------> element is simple\n");
#endif
			return 1;
		default:
#ifdef DEBUG
			fprintf(p->log, "--------------------------> element is not simple\n");
#endif
			return 0;
	}
}

void ml_init_parser(struct ml_parser_ctxt* p, uint8_t* dstart, uint8_t* dend)
{
	MLSTACK_INIT(&(p->sstack)
			, MLPARSER_STACK_SEGMENT_COUNT
			, MLPARSER_STACK_SEGMENT_SIZE);
	MLSTACK_INIT(&(p->pstack)
			, MLPARSER_STACK_SEGMENT_COUNT
			, MLPARSER_STACK_SEGMENT_SIZE);

	p->ddata = malloc(sizeof(struct ml_dom_data));

	p->ddata->dstart = dstart;
	p->ddata->dend = dend;

	MLSTACK_INIT(&(p->ddata->astack), (dend - dstart) / 10, dend - dstart);
	MLSTACK_INIT(&(p->ddata->estack), (dend - dstart) / 10, dend - dstart);

	p->state = MLPSTATE_START;
}

void ml_free_parser(struct ml_parser_ctxt* p)
{
	MLSTACK_FREE(&(p->sstack));
	MLSTACK_FREE(&(p->pstack));
}

/* 
 * Reduce functions:
 *
 * 	One should remember that reducing a rule happens from the left to
 * 	the right and a stack contains the rightmost token on the top of it.
 *
 * 	Parser does not push 'service' tokens, which are used only to define
 * 	structure, on the stack. Like '<', '=', and so on. At least it should
 * 	not :). That's why only effective data is poped from the stack when
 * 	reducing.
 *
 */

void ml_reduce_simple_attribute(struct ml_parser_ctxt* p)
{
	struct ml_prod* prod;
	struct ml_dom_attribute* attribute;

	/* allocate a new attribute */
	MLSTACK_PUSH_NEW(&(p->ddata->astack), attribute);

	attribute->vstart = NULL;
	attribute->vend = NULL;

	/* get an attribute name from the stack */
	MLSTACK_POPREF(&(p->pstack), prod);
	attribute->nstart = prod->as.token.start;
	attribute->nend = prod->as.token.end;

	prod = MLSTACK_TOP(&(p->pstack));
	assert("The top of the stack is not an element."
		"Wrong reduction rule." 
		&& prod->type == MLRULE_START_TAG);

	MLDOM_ELEMENT_ADD_ATTRIBUTE(prod->as.element, attribute);

#ifdef DEBUG
	fprintf(p->log, "--------------------------> ml_reduce_simple_attribute\n");
#endif
}

void ml_reduce_attribute(struct ml_parser_ctxt* p)
{
	struct ml_prod* prod;
	struct ml_dom_attribute* attribute;

	/* allocate a new attribute */
	MLSTACK_PUSH_NEW(&(p->ddata->astack), attribute);

	/* get an attribute value from the stack */
	MLSTACK_POPREF(&(p->pstack), prod);
	attribute->vstart = prod->as.token.start;
	attribute->vend = prod->as.token.end;

	/* skip the '=' symbol */
	MLSTACK_SKIP_POP(&(p->pstack));

	/* get an attribute name from the stack */
	MLSTACK_POPREF(&(p->pstack), prod);
	attribute->nstart = prod->as.token.start;
	attribute->nend = prod->as.token.end;

	prod = MLSTACK_TOP(&(p->pstack));
	assert("The top of the stack is not an element."
		"Wrong reduction rule." 
		&& prod->type == MLRULE_START_TAG);

	MLDOM_ELEMENT_ADD_ATTRIBUTE(prod->as.element, attribute);

#ifdef DEBUG
	fprintf(p->log, "--------------------------> ml_reduce_attribute\n");
#endif
}

void ml_reduce_start_tag(struct ml_parser_ctxt* p)
{
	struct ml_prod* prod;
	struct ml_dom_element* element;

	/*
	 * Just create a new dom element. No special data structure
	 * for a start tag itself.
	 */

	/* allocate a new dom element */
	MLSTACK_PUSH_NEW(&(p->ddata->estack), element);

	/* get an element name from the stack */
	MLSTACK_POPREF(&(p->pstack), prod);

	MLDOM_ELEMENT_INIT(element
		, prod->as.token.start	/* name start */
		, prod->as.token.end	/* name end */
		, NULL			/* attribute list */
		, MLDOM_CONTENT_ELEMENT);
	
	/* skip the '<' symbol */
	MLSTACK_SKIP_POP(&(p->pstack));

	/* push on the stack */
	MLSTACK_PUSH_NEW(&(p->pstack), prod);
	prod->type = MLRULE_START_TAG;
	prod->as.element = element;

#ifdef DEBUG
	fprintf(p->log, "--------------------------> ml_reduce_start_tag\n");
#endif
}

void ml_reduce_simple_element(struct ml_parser_ctxt* p)
{
	struct ml_prod* parent;
	struct ml_prod* child;

	/* pop the last parsed element */
	MLSTACK_POPREF(&(p->pstack), child);
	
	/* get a pointer to the parent element */
	parent = MLSTACK_TOP(&(p->pstack));
	assert("The top of the stack is not an element."
		"Wrong reduction rule." 
		&& parent->type == MLRULE_START_TAG);

	MLDOM_ELEMENT_ADD_CONTENT(parent->as.element, child->as.element);

#ifdef DEBUG
	fprintf(p->log, "--------------------------> ml_reduce_simple_element\n");
#endif
}

void ml_reduce_element(struct ml_parser_ctxt* p)
{
	struct ml_prod* parent;
	struct ml_prod* child;

	/* skip the '>' symbol */
	MLSTACK_SKIP_POP(&(p->pstack));
	
	/* skip the end tag name */
	MLSTACK_SKIP_POP(&(p->pstack));
	
	/* skip the '</' symbol */
	MLSTACK_SKIP_POP(&(p->pstack));
	
	/* pop the last parsed element */
	MLSTACK_POPREF(&(p->pstack), child);
	
	/* get a pointer to the parent element */
	parent = MLSTACK_TOP(&(p->pstack));
	assert("The top of the stack is not an element."
		"Wrong reduction rule." 
		&& parent->type == MLRULE_START_TAG);

	MLDOM_ELEMENT_ADD_CONTENT(parent->as.element, child->as.element);

#ifdef DEBUG
	fprintf(p->log, "--------------------------> ml_reduce_element\n");
#endif
}

void ml_reduce_remaining(struct ml_parser_ctxt* p)
{
	struct ml_prod* parent;
	struct ml_prod* child;

	while (p->pstack.sg >= 0 && p->pstack.si > 1) {

#ifdef DEBUG
		MLSTACK_DUMP(&(p->pstack));
#endif

		/* pop the last parsed element */
		MLSTACK_POPREF(&(p->pstack), child);
		
		/* get a pointer to the parent element */
		parent = MLSTACK_TOP(&(p->pstack));

#ifdef DEBUG
		mld_print_prod(p->log, parent);
#endif

		assert("The top of the stack is not an element."
			"Wrong reduction rule." 
			&& parent->type == MLRULE_START_TAG);

		MLDOM_ELEMENT_ADD_CONTENT(parent->as.element, child->as.element);

#ifdef DEBUG
		fprintf(p->log, "--------------------------> ml_reduce_simple_element\n");
#endif
	}
}

void ml_reduce_content(struct ml_parser_ctxt* p, enum ml_dom_content_type type)
{
	struct ml_prod* prod;
	struct ml_dom_element* text;

	/* allocate a new text element */
	MLSTACK_PUSH_NEW(&(p->ddata->estack), text);

	/* pop a content from the stack */
	MLSTACK_POPREF(&(p->pstack), prod);

	MLDOM_ELEMENT_INIT(text
		, prod->as.token.start	/* name start */
		, prod->as.token.end	/* name end */
		, NULL			/* attribute list */
		, type);
	
	prod = MLSTACK_TOP(&(p->pstack));
	assert("The top of the stack is not an element."
		"Wrong reduction rule." 
		&& prod && prod->type == MLRULE_START_TAG);

	MLDOM_ELEMENT_ADD_CONTENT(prod->as.element, text);

#ifdef DEBUG
	fprintf(p->log, "--------------------------> ml_reduce_content\n");
#endif
}

#define SHIFT() do {						\
	MLSTACK_PUSH_NEW(&(p.pstack), (p.prod));		\
	p.prod->as.token = p.token;				\
	p.prod->type = MLRULE_TOKEN;				\
} while (0)

#define NEXT_TOKEN() if ( ml_next_token(&l, &p.token) != ML_OK ) goto END

#define CREATE_ROOT() do {					\
	struct ml_prod* prod;					\
	struct ml_dom_element* element;				\
	MLSTACK_PUSH_NEW(&(p.ddata->estack), element);		\
	MLDOM_ELEMENT_INIT(element				\
		, NULL			/* name start */	\
		, NULL			/* name end */		\
		, NULL			/* attribute list */	\
		, MLDOM_CONTENT_ELEMENT);			\
	MLSTACK_PUSH_NEW(&(p.pstack), prod);			\
	prod->type = MLRULE_START_TAG;				\
	prod->as.element = element;				\
	(*dom)->document = element;				\
} while (0)

#ifdef DEBUG
enum ml_error ml_parse_sgml(uint8_t* dstart, uint8_t* dend, struct ml_dom** dom, FILE* log)
#else
enum ml_error ml_parse_sgml(uint8_t* dstart, uint8_t* dend, struct ml_dom** dom)
#endif
{
	*dom = malloc(sizeof(struct ml_dom));

	struct ml_lex_ctxt l;
	struct ml_parser_ctxt p;

#ifdef DEBUG
	p.log = log;
#endif

	if (ml_init_lex(&l, dstart, dend, NULL, NULL) != ML_OK)
		return l.error;

	ml_init_parser(&p, dstart, dend);

	(*dom)->data = p.ddata;

	CREATE_ROOT();

	while (1) {

#ifdef DEBUG
		mld_print_pstate(p.log, p.state);
#endif

		NEXT_TOKEN();

#ifdef DEBUG
		mld_print_token(p.log, &p.token);
#endif

		switch (p.state) {
			case MLPSTATE_START:
			case MLPSTATE_START_TAG:
				switch (p.token.type) {
					case MLTOKEN_LT:
						SHIFT();
						p.state = MLPSTATE_START_TAG_START;
						continue;
					case MLTOKEN_CCONTENT:
						SHIFT();
						ml_reduce_content(&p, MLDOM_CONTENT_TEXT);
						p.state = MLPSTATE_START_TAG;
						continue;
					case MLTOKEN_SCRIPT:
						SHIFT();
						ml_reduce_content(&p, MLDOM_CONTENT_SCRIPT);
						p.state = MLPSTATE_START_TAG;
						continue;
					case MLTOKEN_COMMENT:
						SHIFT();
						ml_reduce_content(&p, MLDOM_CONTENT_COMMENT);
						p.state = MLPSTATE_START_TAG;
						continue;
					case MLTOKEN_END_TAG_OPENER:
						SHIFT();
						p.state = MLPSTATE_END_TAG_START;
						continue;
					default:
						continue;
				}
			case MLPSTATE_START_TAG_START:
				switch (p.token.type) {
					case MLTOKEN_IDENTIFIER:
						SHIFT();
						ml_reduce_start_tag(&p);
						p.state = MLPSTATE_START_TAG_NAME;
						continue;
					default:
						continue;
				}
			case MLPSTATE_START_TAG_NAME:
				switch (p.token.type) {
					case MLTOKEN_GT:
						if (ml_is_element_simple(&p)) {
							ml_reduce_simple_element(&p);
							p.state = MLPSTATE_START;
						} else {
							p.state = MLPSTATE_START_TAG;
						}
						continue;
					case MLTOKEN_START_TAG_CLOSER:
						ml_reduce_simple_element(&p);
						p.state = MLPSTATE_START;
						continue;
					case MLTOKEN_IDENTIFIER:
						SHIFT();
						p.state = MLPSTATE_ATTRIBUTE_NAME;
						continue;
					default:
						continue;
				}
			case MLPSTATE_ATTRIBUTE_NAME:
				switch (p.token.type) {
					case MLTOKEN_GT:
						ml_reduce_simple_attribute(&p);
						p.state = MLPSTATE_START_TAG;
						continue;
					case MLTOKEN_START_TAG_CLOSER:
						ml_reduce_simple_attribute(&p);
						ml_reduce_simple_element(&p);
						p.state = MLPSTATE_START;
						continue;
					case MLTOKEN_EQ:
						p.state = MLPSTATE_ATTRIBUTE_EQ;
						SHIFT();
						continue;
					case MLTOKEN_IDENTIFIER:
						ml_reduce_simple_attribute(&p);
						SHIFT();
						p.state = MLPSTATE_ATTRIBUTE_NAME;
						continue;
					default:
						continue;
				}
			case MLPSTATE_ATTRIBUTE_EQ:
				switch (p.token.type) {
					case MLTOKEN_GT:
						if (ml_is_element_simple(&p))
							ml_reduce_simple_element(&p);
						p.state = MLPSTATE_START;
						continue;
					case MLTOKEN_SINGLE_QUOTED_STRING:
					case MLTOKEN_DOUBLE_QUOTED_STRING:
					case MLTOKEN_IDENTIFIER:
					case MLTOKEN_MEASURE:
					case MLTOKEN_RGB_VALUE:
					case MLTOKEN_URI:
						SHIFT();
						ml_reduce_attribute(&p);
						p.state = MLPSTATE_START_TAG_NAME;
						continue;
					default:
						continue;
				}
			case MLPSTATE_END_TAG_START:
				switch (p.token.type) {
					case MLTOKEN_IDENTIFIER:
						SHIFT();
						p.state = MLPSTATE_END_TAG_NAME;
						continue;
					default:
						continue;
				}
			case MLPSTATE_END_TAG_NAME:
				switch (p.token.type) {
					case MLTOKEN_GT:
						SHIFT();
						ml_reduce_element(&p);
						p.state = MLPSTATE_START;
						continue;
					default:
						continue;
				}
			default:
				continue;
		}

	}

END:
	ml_reduce_remaining(&p);
	ml_free_parser(&p);

	return ML_OK;
}

void ml_dom_free(struct ml_dom* dom)
{
	MLSTACK_FREE(&(dom->data->astack));
	MLSTACK_FREE(&(dom->data->estack));
	free(dom->data->dstart);
	free(dom->data);
	free(dom);
}

