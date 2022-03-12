CC=gcc
SRC=src/
CLASS=*.c
INCLUDE=include
FLAGS=-Wall -Wextra

.PHONY:	comp find main clean

main:	find comp

find:
	$(CC) -o find.exe find.c -I$(INCLUDE) $(SRC)$(CLASS) $(FLAGS) 
comp:
	$(CC) -o comp.exe comp.c -I$(INCLUDE) $(SRC)$(CLASS) $(FLAGS) 

clean:
	rm  -f *.exe 


