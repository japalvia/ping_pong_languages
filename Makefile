all:
	gcc -Wall -std=c99 -pedantic -g main.c -o main

clean:
	rm -rf main
