# Makefile for cppbignum module

CC=g++
CFLAGS=-c

MAIN: cppbignum.o 
	$(CC) -shared -o libcppbignum.so cppbignum.o -L. -lbignum -Wl,-rpath,.

	# Compile c++ wrapper for py 
	swig -c++ -python cppbignum.i
	$(CC) -fPIC -c cppbignum.cpp cppbignum_wrap.cxx -I/usr/include/python2.7
	$(CC) cppbignum_wrap.o cppbignum.o -shared -fPIC -L. -lbignum -Wl,-rpath,. -o _cppbignum.so

cppbignum.o: cppbignum.cpp libbignum.so
	$(CC) $(CFLAGS) -fPIC cppbignum.cpp 

clean:
	rm -f *.o
