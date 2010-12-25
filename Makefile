CC = gcc
CFLAGS = -g -Wall -ansi

read.o: read.c read.h shell.h
	$(CC) $(CFLAGS) -c read.c -o read.o
analyze.o: analyze.c analyze.h shell.h 
	$(CC) $(CFLAGS) -c analyze.c -o analyze.o
execute.o: execute.c execute.h shell.h
	$(CC) $(CFLAGS) -c execute.c -o execute.o
auxiliary.o: auxiliary.c shell.h
	$(CC) $(CFLAGS) -c auxiliary.c -o auxiliary.o	
shell: main.c read.o analyze.o execute.o auxiliary.o
	$(CC) $(CFLAGS) main.c read.o analyze.o execute.o auxiliary.o -o shell
run: shell
	./shell
clean:
	rm -f *.o 
