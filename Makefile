a.out: *.c *.h
	@gcc -std=c99 test.c
	@./a.out

clean:
	@rm a.out

all:
	a.out

