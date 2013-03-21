# makefile

CC=g++
CFLAGS=-c

MAIN: cppbignum.o 
	$(CC) -shared -o libcppbignum.so cppbignum.o


cppbignum.o: cppbignum.cpp
	$(CC) $(CFLAGS) -fPIC cppbignum.cpp -I/usr/include/python2.7

clean:
	rm -f *.o
