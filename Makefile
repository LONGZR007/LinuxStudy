s = sum.c

.PHONY: all clean
all:
	gcc hello.c $(s)

clean:
	-rm -v a.out
