
#include <stdio.h>

FILE *input= 0;
static int   lineNumber= 1;

#define YY_INPUT(buf, result, max)			\
{							\
  int c= getc(input);					\
  if ('\n' == c || '\r' == c) ++lineNumber;		\
  result= (EOF == c) ? 0 : (*(buf)= c, 1);		\
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
           
