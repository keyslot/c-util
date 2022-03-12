#include "strings.h"

int 
indexOf(char *w, char *v)
{
	int i = 0;
	int j = 0;
	int k = 0;
	for(; v[i] && w[j]; i++ ) {
	    for(k = i, j = 0; v[k] && w[j]; k++,j++) {
		if (v[k] != w[j]) 
		    break;
		}
	}
	return (!w[j] ? i - 1 : -1); 
}

int 
frecuency(char *w, char *v)
{
	int i = 0;
	int pos = indexOf(w,v);
	while(pos >= 0){
	      v += pos + 1;
	      pos = indexOf(w,v);
	      i++;
	}
	return i;
}

int
composition(char *v)
{	
	int n = 0;
	if(*v) 
	    n = composition(v+1);
	int i = 0;
	char *p = v;
	char *c = v;
	while(*v++) {
	     for(c = p; *(c + i); c++)
                putchar(*c);
	     i++; 
	     n++;
	     putchar('\n');
	}
	return n;
}

