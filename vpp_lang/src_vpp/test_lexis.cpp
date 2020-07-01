
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *input= 0;
static int   lineNumber= 1;

static char* open_raw = NULL;
//static char* close_raw = NULL;

#define YY_INPUT(buf, result, max)			\
{							\
  int c= getc(input);					\
  if ('\n' == c || '\r' == c) ++lineNumber;		\
  result= (EOF == c) ? 0 : (*(buf)= c, 1);		\
}


static int set_open_raw(char* tok){
	if(tok != NULL){
		if(open_raw != NULL){
			free(open_raw);
			open_raw = NULL;
		}
		open_raw = strdup(tok);
		fprintf(stdout, "Setted open_raw=%s\n", open_raw);
	}
	return 1;
}

static int is_close_raw(char* tok){
	int ret = 0;
	if(tok != NULL){
		if(open_raw != NULL){
			ret = (strcmp(open_raw, tok) == 0);
			fprintf(stdout, "Cmp %s==%s ? ret=%d\n", open_raw, tok, ret);
			free(open_raw);
			open_raw = NULL;
		}
	}
	return ret;
}

#include "peg_output.c"

int yyparse();

int main(int argc, char **argv)
{
	if(argc < 2){
		fprintf(stderr, "%s <i_file_nam>\n", argv[0]);
		return -1;
	}
	char* fileName = argv[1];
	input = fopen(fileName, "r");
	if(input == NULL){
		fprintf(stderr, "Cannot open file %s\n", fileName);
		return -1;
	}
	
	if(! yyparse()){
		fprintf(stderr, "GOT AN ERROR!!!\n");
	}
	
	return 0;
}
           
