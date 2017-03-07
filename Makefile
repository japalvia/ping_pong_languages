all:
	gcc -Wall -std=c99 -pedantic -g -ljansson main.c -o main

clean:
	rm -rf main
