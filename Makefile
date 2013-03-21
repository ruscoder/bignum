# makefile

CC=gcc
CFLAGS=-c
MAKE = make

MAIN: test.o cbignum/libbignum.so
	$(CC) -o test test.o -L. -lbignum -Wl,-rpath,.
	$(MAKE) -C cbignum
	$(MAKE) -C cppbignum
test.o: test.c 
	$(CC) $(CFLAGS) test.c

clean:
	rm -f *.o
	$(MAKE) clean -C cbignum
	$(MAKE) clean -C cppbignum
