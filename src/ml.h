#ifndef ml_h
#define ml_h

#include <mlparser.h>

const char* ml_detect_encoding(const char* data, size_t *size);

enum ml_error ml_normalize_encoding(uint8_t *data, uint8_t *dataend
		, uint8_t **outbuf, uint8_t **outbufend);
#endif

