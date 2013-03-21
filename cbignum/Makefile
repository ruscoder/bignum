# makefile

CC=gcc
CFLAGS=-c

MAIN:  bignum.o 
	$(CC) -shared -o libbignum.so bignum.o


bignum.o: bignum.c
	$(CC) $(CFLAGS) -fPIC bignum.c

clean:
	rm -f *.o
