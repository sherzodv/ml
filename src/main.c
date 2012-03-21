
#include "ml.h"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>

uint8_t* ml_read_file(const char* fileName, uint8_t** data);

int main(int argc, char** argv)
{
	uint8_t* data = NULL;
	uint8_t* dataend = NULL;

	if (argc > 1) {
		dataend = ml_read_file(argv[1], &data);
		if (dataend == NULL) {
			printf("Can't open file for reading: %s\n", argv[1]);
			exit(1);
		}
	} else {
		dataend = ml_read_file(NULL, &data);
		if (dataend == NULL) {
			printf("Can't read from standard input.\n");
			exit(1);
		}
	}

	ml_normalize_encoding(data, dataend, &data, &dataend);
	
	struct ml_dom* dom;
	int level = 0;

#ifdef DEBUG
	if (ml_parse_sgml(data, dataend, &dom, stdout) == ML_OK)
#else
	if (ml_parse_sgml(data, dataend, &dom) == ML_OK)
#endif
		mld_print_text(stdout, dom);

	ml_dom_free(dom);

	return 0;
}

uint8_t* ml_read_file(const char* fileName, uint8_t** data)
{
	FILE *f = NULL;

	if (fileName == NULL)
		f = stdin;

	if (!(f = fopen(fileName, "r"))) {
		*data = NULL;
		return NULL;
	}

	size_t delta = 100000;
	size_t size = delta;
	size_t rcount = 0;
	
	*data = malloc(size * sizeof(uint8_t));

	uint8_t* curr = *data;
	size_t dsize = 0;

	while (rcount = fread(curr, sizeof(uint8_t), delta, f))
	{
		dsize += rcount;
		if (rcount < delta || feof(f))
			break;
		*data = realloc(*data, size + delta);
		curr = *data + size - 1;
		size += delta;
	}

	fclose(f);

	return *data + dsize + 1;
}

