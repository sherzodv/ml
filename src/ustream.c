#include "ustream.h"
#include "ext/utf8proc/utf8proc.h"

struct sustream
{
	uint8_t *str; /* string start */
	uint8_t *end; /* just beyond the last octet */
	uint8_t *cur;

	/* octets scanned when reading unicode point */
	ssize_t octcnt;
};

inline int sustream_next_char(struct ustream *ustrm)
{
	struct sustream* sstrm = (struct sustream*)(ustrm->stream);
	sstrm->cur += sstrm->octcnt;
	if (sstrm->cur >= sstrm->end)
		return STRM_END;
	sstrm->octcnt = utf8proc_iterate(sstrm->cur, 4, &ustrm->point);
	if (sstrm->octcnt < 0)
		return WRONG_ENCODING;
	return OK;
}

inline int sustream_prev_char(struct ustream *ustrm)
{
	struct sustream* sstrm = (struct sustream*)(ustrm->stream);
	sstrm->cur -= sstrm->octcnt;
	if (sstrm->cur < sstrm->str)
		return STRM_END;
	sstrm->octcnt = utf8proc_iterate(sstrm->cur, 4, &ustrm->point);
	if (sstrm->octcnt < 0)
		return WRONG_ENCODING;
	return OK;
}

struct sustream* create_sustream(struct sstring* ss)
{
	struct sustream* sstrm = malloc(sizeof(struct sustream));
	if (!sstrm)
		return NULL;
	sstrm->str = malloc(ss->size);
	if (!sstrm->str) {
		free(sstrm);
		return NULL;
	}
	strncpy(sstrm->str, ss->str, ss->size);
	sstrm->end = sstrm->str + ss->size;
	sstrm->cur = sstrm->str;
	sstrm->octcnt = 0;
	return sstrm;
}

void free_sustream(struct sustream* sstrm)
{
	if (sstrm) {
		if (sstrm->str)
			free(sstrm->str);
		free(sstrm);
	}
}

struct ustream* new_sustream(struct sstring* ss)
{
	struct ustream* ustrm = malloc(sizeof(struct ustream));
	if (!ustrm)
		return NULL;
	ustrm->stream = create_sustream(ss);
	if (!ustrm->stream) {
		free_sustream(ustrm->stream);
		free(ustrm);
		return NULL;
	}
	ustrm->next = sustream_next_char;
	ustrm->prev = sustream_prev_char;
	return ustrm;
}

void delete_sustream(struct ustream* ustrm)
{
	if (ustrm) {
		free_sustream(ustrm->stream);
		free(ustrm);
	}
}

