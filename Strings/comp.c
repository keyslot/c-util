#include "strings.h"

int main(int argc, char **argv)
{	
    if(argc < 2) {
	 printf("%s word\n",argv[0]);
	 return -1;
	}
  
    printf("Composition of {%s} =  %d \n",argv[1],composition(argv[1]));

    return 0;
}

