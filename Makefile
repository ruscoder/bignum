# makefile

CC = gcc
CFLAGS = -c
DBG = -Wall -ggdb
MAKE = make

MAIN: depends test_c.o test_cpp.o 
	$(MAKE) -C cbignum # depends lib
	$(MAKE) -C cppbignum
	$(CC) $(DBG) -o test_c test_c.o -L. -lbignum -lm -Wl,-rpath,.
	g++ $(DBG) -o test_cpp test_cpp.o -L. -lbignum -lcppbignum -Wl,-rpath,. 

depends:
	ln -f -s cbignum/libbignum.so libbignum.so
	ln -f -s ../cbignum/libbignum.so cppbignum/libbignum.so	
	ln -f -s cppbignum/_cppbignum.so _cppbignum.so
	ln -f -s cppbignum/cppbignum.py cppbignum.py
	ln -f -s cppbignum/libcppbignum.so libcppbignum.so
	ln -f -s cppbignum/cppbignum.py cppbignum.py


test_c.o: test_c.c libbignum.so
	$(CC) $(DBG) $(CFLAGS) test_c.c

test_cpp.o: test_cpp.cpp libbignum.so libbignum.so
	g++ $(DBG) $(CFLAGS) test_cpp.cpp

clean:
	rm -f *.o
	$(MAKE) clean -C cbignum
	$(MAKE) clean -C cppbignum
