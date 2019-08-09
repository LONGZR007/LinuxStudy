EXE = main
#OBJ = hello.o sum.o
SRC = hello.c sum.c

EXE:$(SRC)
	arm-linux-gnueabi-gcc -o $(EXE) $^

.PHONY:clean

clean:
	-rm -vfr a.out *.o $(EXE)
