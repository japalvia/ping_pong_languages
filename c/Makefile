UTILS := ../utils

all:
	gcc -Wall -std=c99 -pedantic -g -ljansson main.c -o main

run:
	"${UTILS}/python-send-bytes.py"  \
		| ./main \
		| "${UTILS}/python-recv-bytes.py"

run-with-memcheck:
	 "${UTILS}/python-send-bytes.py" \
		| valgrind --leak-check=full ./main \
		| "${UTILS}/python-recv-bytes.py"

clean:
	rm -rf main
