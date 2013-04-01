# Makefile for cppbignum module

CC = g++
DBG = 
CFLAGS = -c
PY_INCLUDE_PATH = /usr/include/python2.7

MAIN: cppbignum.o cppbignum_wrap.o
	$(CC) $(DBG)  -shared -o libcppbignum.so cppbignum.o -L. -lbignum -Wl,-rpath,.
	$(CC) $(DBG) cppbignum_wrap.o cppbignum.o -shared -fPIC -L. -lbignum -Wl,-rpath,. -o _cppbignum.so


cppbignum_wrap.o: cppbignum_wrap.cxx 
	$(CC) $(DBG) -fPIC -c cppbignum.cpp cppbignum_wrap.cxx -I$(PY_INCLUDE_PATH)

cppbignum_wrap.cxx: cppbignum.i cppbignum.o
	# Compile c++ wrapper for py 
	swig -c++ -python cppbignum.i

cppbignum.o: cppbignum.cpp libbignum.so
	$(CC) $(DBG) $(CFLAGS) -fPIC cppbignum.cpp 

clean:
	rm -f *.o
