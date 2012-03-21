#ifndef ustream_h
#define ustream_h

#include "mstring.h"
#include "mistake.h"

	struct ustream
	{
		uint32_t point; /* Current code point (character) */
		
		void *stream;

		int (*next)(struct ustream* _this);
		int (*prev)(struct ustream* _this);
	};

	struct ustream* new_sustream(struct sstring* ss);
	void delete_sustream(struct ustream* ustrm);

#endif

