#ifndef mstring_h
#define mstring_h

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

	/* string defined by a pointer to it's start
	 * and by size */
	struct sstring
	{
		uint8_t *str;
		size_t size;
	};

	/* string defined by it's ends' pointers */
	struct estring
	{
		uint8_t *str;
		uint8_t *end;
	};

#endif

