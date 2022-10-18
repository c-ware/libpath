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

define(<<RUN_TEST>>, <<echo "Running test $1"
	$1
	echo "Ran test $1">>)

all: $(OBJS) $(TESTS)

clean:
	$(RM) `find . -name '*.i' -print`
	$(RM) `find . -name '*.i.c' -print`
	$(RM) `find . -name '*.o' -print`
	$(RM) $(TESTS)

check:
	RUN_TEST(tests/path/init)
	RUN_TEST(tests/path/free)
	RUN_TEST(tests/path/add_root)
	RUN_TEST(tests/path/add_driv)
	RUN_TEST(tests/path/add_dir)
	RUN_TEST(tests/path/add_driv)
	RUN_TEST(tests/path/add_ext)

# Object file building
COMPILE_FILE(src/objects/path)

# Test building
COMPILE_TEST(tests/path/init)
COMPILE_TEST(tests/path/free)
COMPILE_TEST(tests/path/add_root)
COMPILE_TEST(tests/path/add_driv)
COMPILE_TEST(tests/path/add_dir)
COMPILE_TEST(tests/path/add_ext)
COMPILE_TEST(tests/path/add_file)

.PHONY: all clean check
.SUFFIXES:
