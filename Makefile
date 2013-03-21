# makefile

CC=gcc
CFLAGS=-c
MAKE = make

MAIN: test_c.o test_cpp.o
	$(MAKE) -C cbignum # Test depends lib
	$(MAKE) -C cppbignum

	$(CC) -o test_c test_c.o -L. -lbignum -Wl,-rpath,.
	g++ -o test_cpp test_cpp.o -L. -lbignum -lcppbignum -Wl,-rpath,. -I/usr/include/python2.7


test_c.o: test_c.c 
	$(CC) $(CFLAGS) test_c.c

test_cpp.o: test_cpp.cpp
	g++ $(CFLAGS) test_cpp.cpp

clean:
	rm -f *.o
	$(MAKE) clean -C cbignum
	$(MAKE) clean -C cppbignum
