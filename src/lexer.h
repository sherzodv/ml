#ifndef lexer_h
#define lexer_h

#include "mstring.h"
#include "mistake.h"

	enum token_type
	{
		HTML_TOKEN_CHARACTER
		, HTML_TOKEN_EOF
	};

	struct token
	{
		enum token_type type;
		union {
			uint32_t ch;
			struct sstring ss;
			struct estring es;
		} data;
	};

	struct lexer
	{
		struct token token;

		int mistake;
		void *context;

		/* next/prev token */
		int (*next)(struct lexer* l);
		int (*prev)(struct lexer* l);
		int (*emit)(struct token* t);
	};

	struct lexer* new_slexer(struct sstring* s);
	void delete_slexer(struct lexer *l);

#endif

