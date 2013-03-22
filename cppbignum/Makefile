# makefile

CC=g++
CFLAGS=-c

MAIN: cppbignum.o pybignum.o 
	$(CC) -shared -o libcppbignum.so cppbignum.o -L. -lbignum -Wl,-rpath,.
	$(CC) -shared -o pybignum.so pybignum.o -L.. -lcppbignum -Wl,-rpath,.


	swig -c++ -python cppbignum.i
	$(CC) -fPIC -c cppbignum.cpp cppbignum_wrap.cxx -I/usr/include/python2.7
	$(CC) cppbignum_wrap.o cppbignum.o -shared -fPIC -L. -lbignum -Wl,-rpath,. -o _cppbignum.so

cppbignum.o: cppbignum.cpp
	$(CC) $(CFLAGS) -fPIC cppbignum.cpp 
pybignum.o: pybignum.cpp
	$(CC) $(CFLAGS) -fPIC pybignum.cpp -I/usr/include/python2.7 

clean:
	rm -f *.o
