.PHONY: all clean
all:
	gcc hello.c sum.c

clean:
	-rm -v a.out
