#include "ml.h"

#include <iconv.h>
#include <errno.h>

const char* ml_detect_encoding(const char* data, size_t *size)
{
	size_t i;
	size_t sz = *size;
	if (sz > 2024)
		sz = 2024;

	const char* start;
	const char* end;

	for (i = 0; i < sz; ++i) {

		if (i < sz - 1) {

			*size = 10;

			if (data[i] == 0xFE && data[i+1] == 0xFF)
				return "UTF-16BE//";
			if (data[i] == 0xFF && data[i+1] == 0xFE)
				return "UTF-16LE//";
		}

		if (i < sz - 2) {

			*size = 7;

			if (data[i] == 0xEF
				&& data[i+1] == 0xBB
				&& data[i+2] == 0xBF)
				return "UTF-8//";
		}

		if (i < sz - 4 
			&& data[i] == '<'
			&& data[i+1] == '!'
			&& data[i+2] == '-'
			&& data[i+3] == '-')

			while (i < sz - 3
				&& ! (
					data[i] == '-'
					&& data[i+1] == '-'
					&& data[i+2] == '>'
				)
			)
				++i;

		if (i < sz - 7
			&& ( data[i] == 'c' || data[i] == 'C')
			&& ( data[i+1] == 'h' || data[i+1] == 'H')
			&& ( data[i+2] == 'a' || data[i+1] == 'A')
			&& ( data[i+3] == 'r' || data[i+1] == 'R')
			&& ( data[i+4] == 's' || data[i+1] == 'S')
			&& ( data[i+5] == 'e' || data[i+1] == 'E')
			&& ( data[i+6] == 't' || data[i+1] == 'T')
		   ) {
			i += 7;

			while (i < sz
				&& (
					data[i] == ' '
					|| data[i] == '\t'
					|| data[i] == '\''
					|| data[i] == '"'
					|| data[i] == '='
				)
			)
				++i;

			start = data + i;

			while (i < sz
				&& data[i] != '\''
				&& data[i] != '"'
				&& data[i] != '>')
				++i;

			end = data + i;
			*size = end - start;

			return start;
		}
	}

	*size = 0;
	return NULL;
}

int ml_normalize_encoding(uint8_t *data, uint8_t *dataend
		, uint8_t **outbuf, uint8_t **outbufend)
{
	size_t sz = *dataend - *data;

	const char* encoding = ml_detect_encoding(data, &sz);

	if (sz == 0)
		return MLERR_ENCODING;

	char* enc = malloc(sz + 3);

	strncpy(enc, encoding, sz);
	strncpy(enc + sz, "//\0", 3);

	iconv_t cvthandle = iconv_open("UTF-8//", enc);

	free(enc);

	if (errno)
		return MLERR_ENCODING;

	char *inbuf = data;
	size_t inbufsz = dataend - data;
	size_t outbufsz = inbufsz * 1.5;

	*outbuf = malloc(outbufsz);
	*outbufend = *outbuf;

	sz = iconv(cvthandle, &inbuf, &inbufsz, (char**)outbufend, &outbufsz);

	iconv_close(cvthandle);

	if (errno) {
		free(outbuf);
		return MLERR_ENCODING;
	}
}


