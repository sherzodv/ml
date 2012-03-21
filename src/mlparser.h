#ifndef mlparser_h
#define mlparser_h

#include <mllex.h>

#ifdef DEBUG
enum ml_error ml_parse_sgml(uint8_t* dstart
		, uint8_t* dend
		, struct ml_dom** dom
		, FILE* log);
#else
enum ml_error ml_parse_sgml(uint8_t* dstart
		, uint8_t* dend
		, struct ml_dom** dom);
#endif

void ml_free_dom(struct ml_dom* dom);

#endif

