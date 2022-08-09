#include <stdio.h>
#include <stdlib.h>

#define BYTE 8 
#define returnIF(INT) if((INT)){return;};

int *toBinary(int unsigned,int);

static void 
printIntVector(int unsigned *v,int l) 
{
	returnIF(!v);
	int i = 0;
	while(i < l)
	      printf("%d",v[i++]); 
}

static void 
destroyIntVector(int unsigned **v) 
{
	returnIF(!v || !*v);
	free(*v);
	*v = NULL;
}
int main(int argc, char **argv) 
{
	
	int unsigned decimal = 0;
	if(argc < 2 )
	   return fprintf(stderr,"%s decimal_to_8_bits\n",argv[0]);

	int unsigned *v = toBinary(atoi(argv[1]),BYTE);
	printIntVector(v,BYTE);
	destroyIntVector(&v);
	return 0;
}

int * 
toBinary(int unsigned n,int byte)
{
	int i = 0;
	int k = byte;
	int *binary = calloc(byte,sizeof(int));
	for(k--; i < byte; i++) 
	    binary[k--] = (n >> i) % 2;       
	return binary;
}
