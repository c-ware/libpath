

# Programs
CC=cc
CPP=cc -E
RM=rm -rf
FIND=find
DIRNAME=dirname

# Configuration
LDLIBS=
LDFLAGS=
OSFLAGS=
CFLAGS=
CPPFLAGS=$(OSFLAGS) -I/usr/include -Isrc/liberror -Isrc/objects -Itests -Isrc -DLIBERROR_ENABLED -DLIBERROR_STREAM=stderr
OBJS=src/objects/path.o
TESTS=tests/path/init





all: $(OBJS) $(TESTS)

clean:
	$(RM) `find . -name '*.i' -print`
	$(RM) `find . -name '*.i.c' -print`
	$(RM) `find . -name '*.o' -print`
	$(RM) $(TESTS)

# Object file building
src/objects/path.o: src/objects/path.c
	$(CC) -c src/objects/path.c $(CFLAGS) $(CPPFLAGS) -o src/objects/path.o

# Test building
tests/path/init: tests/path/init.c
	$(CC) tests/path/init.c $(CFLAGS) $(CPPFLAGS) $(OBJS) -o tests/path/init

.PHONY: all clean
.SUFFIXES:
