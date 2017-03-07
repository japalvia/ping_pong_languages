all:
	gcc -Wall -std=c99 -pedantic -g -ljansson main.c -o main

run:
	./python-send-bytes.py ./main | ./python-recv-bytes.py

clean:
	rm -rf main
