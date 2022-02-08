#include <stdio.h>

/**
 * matrixTypeIn
 *
 * Dibuja una matriz de dimensiones:
 * (size_of_v * max_of_v)
 *
 * v es un vector char
 *
 * Eje de uso:
 * 	matrixTypeIn(char,char *)
 *      Primer parametro puede ser un caracter 'c' o 'i':
 *      matrixTypeIn('c',v); por default es 'c';
 *
 */
void  matrixTypeIn(char type,char *v);

int main(int argc, char *argv[]) 
{
	if (argc < 3 || (argv[1][1] != 'c' && argv[1][1] != 'i')) {
		printf("Uso: %s option string\n", argv[0]);
		printf("\t-c String of chars\n");
		printf("\t-i String of numbers\n");
		return -1;
	}
	matrixTypeIn(argv[1][1],argv[2]);
	return 0;
}


static int 
maxOf(void *vector,int t,char type) 
{	
	if(!vector) 
		return 0;

	int i = 1;
	char *v = (char *)vector;
	int max = *v;
	if(type == 'i') {
	   int *v = (int *)vector;
	   max = *v;
	}
	for (; i < t; i++) 
	    if(v[i] > max) 
	       max = v[i];

	return max;
}

static int
toInt(char var)
{
	return var - '0';
}

static int
charsIn(char *v) 
{
       int i = 0;
       if(v)
          while(*(v++))
	        i++; 
       return i;
}

void 
matrixTypeIn(char type,char *v)
{
	int t = charsIn(v); 
	char *format = "%c "; 
        int max = maxOf(v,t,'c');
	if(type == 'i') {
		format = "%d ";
		max = toInt(max);
	}
	int matrix[t][max + 1];
	int n,i,j;
	for (i = 0; i < t; i++){
		n = (type == 'i' ? toInt(v[i]) : v[i]);
		for (j = 0; j <= max; j++)  {
			if (n == j)
			    matrix[i][j] = n;
			else 
			    matrix[i][j] = 0;
		        
			printf(format,matrix[i][j]);
		}
		putchar('\n');
	}

	printf("MAX of V => ");
	printf(format, max);
	printf("\n");
}
