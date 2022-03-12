#include "strings.h"
#include <stdlib.h>

void findW(char*,char*);

int main(int argc, char **argv) {

	if(argc < 3) { 
		printf("%s file word\n",argv[0]);
		return -1;
	}
	char *vector = argv[1];
	char *word   = argv[2];
	puts("Finding vectors...");
	findW(vector, word);
	return 0;
}

void 
findW(char *file, char *w) 
{
	FILE *f = fopen(file,"r");
	if(!f) 
	   return perror(file);
	fseek(f,0,SEEK_END);
	size_t s =  ftell(f) * sizeof(char);
	rewind(f);
	char *v = (char*)malloc(s);
	if (!v)
	   return perror("Error");
	fread(v,s,1,f);
	printf("{%s} in %s => %d times\n",w,file,frecuency(w,v));
	free(v);
	v = NULL;
	fclose(f);
	f = NULL;
}

