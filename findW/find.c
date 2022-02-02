#include <stdio.h>
/* 
 * Buscar indice de w en v  
 * Obtener frecuencia de w en v
 * ((Sin  uso de bibliotecas C))
 * */

int indexOf(char *v, char *w);
int frecuency(char *v, char *w);
void findW(char *v, char *w);


int main(int argc, char **argv) {

	if(argc < 3) { 
		printf("uso: %s file word\n",argv[0]);
		return -1;
	}
	char *vector = argv[1];
	char *word   = argv[2];
	findW(vector, word);
	return 0;
}

int 
indexOf(char *v, char *w)
{  
	int i = 0;
        int j = 0;
	for(; v[i] != '\0'; i++) {
		  if(v[i] == w[j]) 
		       j++;
		  else if(w[j] == '\0')
		       return i -  j; 
		  else 
		       j = 0;
	}
	return -1;
}

int 
frecuency(char *v, char*w)
{
	int i = 0;
	int pos = indexOf(v,w);
	while(pos >= 0){
	      v += pos + 1;
	      pos = indexOf(v,w);
	      i++;
	}
	return i;
}


void 
findW(char *file, char *v) 
{
	FILE *f = fopen(file,"r");
	/* solo lectura de 1Kb */
	char w[1024] = "\0";
	fread(w,1024,1,f);
	printf("v in w => %d times\n",frecuency(w,v));
	fclose(f);
	f = NULL;
}
