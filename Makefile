EXE = main
OBJ = hello.o sum.o
SRC = hello.c sum.c

EXE:$(OBJ)
	gcc -o $(EXE) $^

.PHONY:clean

clean:
	-rm -vfr a.out *.o $(EXE)
