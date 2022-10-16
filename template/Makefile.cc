changequote(<<,>>)

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
CPPFLAGS=$(OSFLAGS) MK_CPPFLAGS
OBJS=MK_OBJECTS
TESTS=MK_TESTS

define(<<COMPILE_FILE>>, <<$1.o: $1.c
	$(CC) -c $1.c $(CFLAGS) $(CPPFLAGS) -o $1.o>>)

define(<<COMPILE_TEST>>, <<$1: $1.c
	$(CC) $1.c $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $1>>)

all: $(OBJS) $(TESTS)

clean:
	$(RM) `find . -name '*.i' -print`
	$(RM) `find . -name '*.i.c' -print`
	$(RM) `find . -name '*.o' -print`
	$(RM) $(TESTS)

# Object file building
COMPILE_FILE(src/objects/path)

# Test building
COMPILE_TEST(tests/path/init)

.PHONY: all clean
.SUFFIXES:
