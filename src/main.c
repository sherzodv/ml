
#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

#define BUFF_SIZE 10000

char *p_buff;

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

int main(int argc, char **argv)
{
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

	struct sstring input;

	input.str = p_buff;
	input.size = strlen(input.str);

	struct lexer *l = new_slexer(&input);

	if (!l)
		return 1;

	while (l->next(l) == OK) {
		/* do some action here */
	}

	delete_slexer(l);

	free(p_buff);
	return 0;
}

