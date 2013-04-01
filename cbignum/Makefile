# makefile

CC=gcc
CFLAGS=-c
DBG = -ggdb -Wall
MAIN:  bignum.o 
	$(CC) $(DBG) -shared -o libbignum.so bignum.o


bignum.o: bignum.c
	$(CC) $(DBG) $(CFLAGS) -fPIC bignum.c

clean:
	rm -f *.o
