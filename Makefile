# makefile

CC=gcc
CFLAGS=-c
MAKE = make

MAIN: test_c.o test_cpp.o 
	$(MAKE) -C cbignum # Test depends lib
	$(MAKE) -C cppbignum
	$(CC) -o test_c test_c.o -L. -lbignum -lm -Wl,-rpath,.
	g++ -o test_cpp test_cpp.o -L. -lbignum -lcppbignum -Wl,-rpath,. -I/usr/include/python2.7


test_c.o: test_c.c libbignum.so
	$(CC) $(CFLAGS) test_c.c

test_cpp.o: test_cpp.cpp libbignum.so libbignum.so
	g++ $(CFLAGS) test_cpp.cpp

clean:
	rm -f *.o
	$(MAKE) clean -C cbignum
	$(MAKE) clean -C cppbignum
