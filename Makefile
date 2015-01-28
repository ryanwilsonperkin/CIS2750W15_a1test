CC=gcc
CFLAGS=-Wall
PROGNAME=./a1test

test: build
	$(PROGNAME)

build: a1test.c ParameterManager.h libpm.a
	$(CC) $(CFLAGS) a1test.c libpm.a -o $(PROGNAME)

clean:
	$(RM) *.h *.o libpm.a a1test
