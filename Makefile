# makefile

CC=gcc
CFLAGS=-c

MAIN: test.o cbignum/libbignum.so
	$(CC) -o test test.o -L. -lbignum -Wl,-rpath,.
test.o: test.c 
	$(CC) $(CFLAGS) test.c

clean:
	rm -f *.o
