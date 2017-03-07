all:
	gcc -Wall -std=c99 -pedantic -g -ljansson main.c -o main

run:
	./python-send-bytes.py | ./main | ./python-recv-bytes.py

run-with-memcheck:
	 ./python-send-bytes.py | \
		valgrind --leak-check=full ./main | \
		./python-recv-bytes.py

clean:
	rm -rf main
