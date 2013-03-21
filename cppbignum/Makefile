# makefile

CC=g++
CFLAGS=-c

MAIN: cppbignum.o pybignum.o 
	$(CC) -shared -o libcppbignum.so cppbignum.o -L. -lbignum -Wl,-rpath,.
	$(CC) -shared -o pybignum.so pybignum.o -L.. -lcppbignum -Wl,-rpath,.
cppbignum.o: cppbignum.cpp
	$(CC) $(CFLAGS) -fPIC cppbignum.cpp 
pybignum.o: pybignum.cpp
	$(CC) $(CFLAGS) -fPIC pybignum.cpp -I/usr/include/python2.7 

clean:
	rm -f *.o
