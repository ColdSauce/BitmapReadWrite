all : standardMake

standardMake:
	gcc -std=c99 -o bin/main -Wall -Werror -g main.c

clean:
	rm -f bin/*
