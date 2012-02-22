
#include "ext/utf8proc/utf8proc.h"
#include <string.h>
#include <stdio.h>

enum ml_error
{
	MLERR_ENCODING = -2
	, MLERR_EOF = -1
	, ML_OK = 0
	, MLERR_NO_TRANSITION
};

#define MLMAX_STATE 12
enum ml_state_type
{
	MLSTATE_INITIAL				= 0
};

#define MLMAX_TOKEN_TYPE 22
enum ml_lex_token_type
{
	MLTOKEN_START			= 0
	, MLTOKEN_INTEGER		= 1
};

#define BUFF_SIZE 10000

char *p_buff;

struct ml_lex_t
{
	const uint8_t* start;	/* data stream start */
	const uint8_t* end;	/* data stream end */
	const uint8_t* curr;	/* current character */

	const uint8_t* sstart;

	enum ml_error error;
	const char* errmsg;
	
	uint32_t ch;
	ssize_t state;
	enum ml_lex_token_type ttype;
	ssize_t res;

	uint32_t rch;
	ssize_t rres;

	int (*nextch)(struct ml_lex_t* l);
	int (*prevch)(struct ml_lex_t* l);
	
	ssize_t internal;
};

int ml_prevch(struct ml_lex_t* l)
{
	l->curr -= l->rres;
	
	if (l->curr >= l->end)
	{
		l->error = MLERR_EOF;
		l->errmsg = "No data left.";
		return l->error;
	}

	l->res = l->rres;
	l->ch = l->rch;

	if (l->res == 0)
	{
		l->error = MLERR_EOF;
		l->errmsg = "No data left.";
		return l->error;
	}

	if (l->res < 0)
	{
		l->error = MLERR_ENCODING;
		l->errmsg = utf8proc_errmsg(l->res);
		return l->error;
	}
	
	return ML_OK;
}

int ml_nextch(struct ml_lex_t* l)
{
	l->curr += l->res;

	if (l->curr >= l->end)
	{
		l->error = MLERR_EOF;
		l->errmsg = "No data left.";
		return l->error;
	}

	l->rres = l->res;
	l->rch = l->ch;
	l->res = utf8proc_iterate(l->curr, 4, &l->ch);

	if (l->res == 0)
	{
		l->error = MLERR_EOF;
		l->errmsg = "No data left.";
		return l->error;
	}

	if (l->res < 0)
	{
		l->error = MLERR_ENCODING;
		l->errmsg = utf8proc_errmsg(l->res);
		return l->error;
	}
	
	return ML_OK;
}

enum ml_error ml_init(struct ml_lex_t* l
	, const char* data_start
	, const char* data_end
	, int (*nextch)(struct ml_lex_t* l)
	, int (*prevch)(struct ml_lex_t* l))
{
	l->start = data_start;
	l->end = data_end;
	l->curr = data_start;

	l->error = 0;
	l->errmsg = "";

	l->ch = 0;
	l->state = 0;
	l->ttype = 0;
	l->res = 0;
	l->rres = 0;

	l->nextch = nextch != NULL ? nextch : ml_nextch;
	l->prevch = prevch != NULL ? prevch : ml_prevch;

	l->internal = MLSTATE_INITIAL;

	return l->nextch(l);
}

enum ml_error ml_next_token(struct ml_lex_t* ctxt, int* token)
{
	return 0;
}

int load_file(char *p, char *fname)
{
	FILE *fp;
	int i=0;
	if ((fp=fopen(fname,"rb"))==NULL)
		return 0;
	i=0;
	do
	{
		if(i>BUFF_SIZE)
		{
			if((p=(char*)realloc(p,BUFF_SIZE))==NULL)
			{
				printf("No memory!\n");
				exit(1);
			}
			i=0;
		}
		*p=getc(fp);
		p++; i++;
	} while(!feof(fp));
	if(*(p-2)==0x1a) *(p-2)='\0';
	else *(p-1)='\0';
	fclose(fp);
	return 1;
}

int main(int argc, char** argv)
{
	struct ml_lex_t context;
	
	char* input;

	if(argc!=2)
	{
		printf("Error:\n\tSyntax: testmld [file]\n");
		exit(1);
	}

	if ((p_buff=(char*)malloc(BUFF_SIZE))==NULL)
	{
		printf("No memory!\n");
		exit(1);
	}
	
	if(!load_file(p_buff,argv[1])) exit(1);
	
	input=p_buff;

	char* input_end = input + strlen(input);

	if (ml_init(&context, input, input_end, 0, 0) != ML_OK)
		return 1;

	int token = 0;

	while (ml_next_token(&context, &token) != ML_OK)
		printf("Next token: %d\n", token);

	free(p_buff);
	return 0;
}

