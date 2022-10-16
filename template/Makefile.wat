changequote(<<,>>)

# Programs
CC=wcc386
LD=wlink
CPP=wcc386 /p
RM=del
FIND=find

# Configuration
LDLIBS=
LDFLAGS=
OSFLAGS=
CFLAGS=
CPPFLAGS=$(OSFLAGS) MK_CPPFLAGS
OBJS=MK_OBJECTS
TESTS=MK_TESTS

define(<<COMPILE_FILE>>, <<$1.obj: $1.c
	$(CC) $1.c $(CFLAGS) $(CPPFLAGS) /fo=$1.obj>>)

define(<<COMPILE_TEST>>, <<$1.exe: $1.c
	$(CC) $1.c $(CFLAGS) $(CPPFLAGS) /fo=$1.obj
	$(LD) FILE $1.obj,$(OBJS) NAME $1.exe>>)

all: $(OBJS) $(TESTS) .symbolic

clean: .symbolic
	$(RM) $(TESTS)

# Object file building
COMPILE_FILE(src\objects\path)

# Test building
COMPILE_TEST(tests\path\init)

.SUFFIXES:
