#ifndef mllex_h
#define mllex_h

#include <mldom.h>

/* Lexer:
 * 	The lexer API is open, in order to let one to build custom parsers
 * 	on the top of it, though not stable yet, and not seem to be in the
 * 	nearest future.
 */

/* Token type:
 * 	The order should be keeped, as token typed is used as index of internal
 * 	tables.
 */

#define MLMAX_TOKEN_TYPE 22
enum ml_token_type
{
	MLTOKEN_START			= 0
	, MLTOKEN_LT 			= 1
	, MLTOKEN_GT 			= 2
	, MLTOKEN_EQ			= 3 
	, MLTOKEN_START_TAG_CLOSER	= 4
	, MLTOKEN_END_TAG_OPENER	= 5
	, MLTOKEN_DTD_OPENER		= 6
	, MLTOKEN_ASCII_SYMBOL		= 7
	, MLTOKEN_IDENTIFIER		= 8
	, MLTOKEN_CCONTENT		= 9
	, MLTOKEN_LCCONTENT		= 10
	, MLTOKEN_CDATA			= 11
	, MLTOKEN_COMMENT		= 12
	, MLTOKEN_SCRIPT		= 13
	, MLTOKEN_SPACE			= 14
	, MLTOKEN_SINGLE_QUOTED_STRING	= 15
	, MLTOKEN_DOUBLE_QUOTED_STRING	= 16
	, MLTOKEN_MEASURE		= 17
	, MLTOKEN_RGB_VALUE		= 18
	, MLTOKEN_URI			= 19
	, MLTOKEN_PROC_INSTR_OPENER	= 20
	, MLTOKEN_PROC_INSTR_CLOSER	= 21
};

struct ml_token
{
	enum ml_token_type type;
	uint32_t ch;

	const uint8_t* start;
	const uint8_t* end;
};

struct ml_lex_ctxt
{
	const uint8_t* start;	/* data stream start */
	const uint8_t* end;	/* data stream end */
	const uint8_t* curr;	/* current character */

	const uint8_t* sstart;

	enum ml_error error;
	const char* errmsg;
	
	uint32_t ch;
	ssize_t state;
	enum ml_token_type ttype;
	ssize_t res;

	uint32_t rch;
	ssize_t rres;

	int (*nextch)(struct ml_lex_ctxt* l);
	int (*prevch)(struct ml_lex_ctxt* l);
	
	ssize_t internal;
};

/* Default functions for obtaining the next character from the stream. */
int ml_nextch(struct ml_lex_ctxt* l);
int ml_prevch(struct ml_lex_ctxt* l);

/* 
 * The lexer initializer. One may pass NULL in nextch, prevch arguments in order
 * to use default character walking functions
 */
enum ml_error ml_init_lex(struct ml_lex_ctxt* l
		, const char* data_start
		, const char* data_end
		, int (*nextch)(struct ml_lex_ctxt* l)
		, int (*prevch)(struct ml_lex_ctxt* l));

/*
 * Obtains the next token from the stream.
 */
enum ml_error ml_next_token(struct ml_lex_ctxt* l, struct ml_token* t);

/* Define the tag type by a name (string) */
enum ml_word ml_string2tag(const uint8_t* start, const uint8_t* end);

#ifdef DEBUG

const char* mld_token2string(enum ml_token_type t);
void mld_print_token(FILE* f, struct ml_token* t);

#endif

#endif

