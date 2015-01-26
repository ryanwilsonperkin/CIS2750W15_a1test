CC=g++
LIBDIR=./lib/.libs
CFLAGS=-I./include
LDFLAGS=-L$(LIBDIR) -lgtest -lpthread
PROGNAME=./a1test

test: build
	LD_LIBRARY_PATH=$(LIBDIR) $(PROGNAME)

build: a1test.cpp ParameterManager.h libpm.a
	$(CC) $(CFLAGS) $(LDFLAGS) a1test.cpp libpm.a -o $(PROGNAME)

clean:
	$(RM) *.h *.o libpm.a a1test
