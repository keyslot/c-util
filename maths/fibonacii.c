#include <stdio.h>
#include <stdlib.h>

typedef long int unsigned fibo_num;
#define FORMAT_FIBO "%lu"

fibo_num fibonacci(fibo_num);

int main(int argc,char *argv[])
{
	if(argc < 2) {
          fprintf(stderr,"%s number_to_fibonacci\n",*argv);
	  return -1;
	}
	fibo_num f = fibonacci(atoi(argv[1]));
	printf("\n["FORMAT_FIBO"]\n",f);
	return 0;
}

fibo_num
fibonacci(fibo_num n) 
{	
	static fibo_num f0 = -1;
	static fibo_num f1 = 1;
	static fibo_num fn = 0;
	fn = f0 + f1;
	f0 = f1;
	f1 = fn;
	/* fibo_list */
	printf(FORMAT_FIBO"  ", fn);
	if(n >= 1) {
	   return fibonacci(n - 1);
	}
	else {
	  n = fn; 
	  /* reset static values */
	  f0 = -1;
	  f1 = 1;	
	  fn = 0;
	  /* last value */
	  return n;
       }
}	
