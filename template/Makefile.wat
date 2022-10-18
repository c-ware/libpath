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

define(<<RUN_TEST>>, <<echo "Running test $1"
	$1
	echo "Ran test $1">>)

all: $(OBJS) $(TESTS) .symbolic

clean: .symbolic
	$(RM) $(TESTS)

check: .symbolic
	RUN_TEST(tests\path\init.exe)
	RUN_TEST(tests\path\free.exe)
	RUN_TEST(tests\path\add_root.exe)
	RUN_TEST(tests\path\add_driv.exe)
	RUN_TEST(tests\path\add_dir.exe)
	RUN_TEST(tests\path\add_file.exe)
	RUN_TEST(tests\path\add_ext.exe)

# Object file building
COMPILE_FILE(src\objects\path)

# Test building
COMPILE_TEST(tests\path\init)
COMPILE_TEST(tests\path\free)
COMPILE_TEST(tests\path\add_root)
COMPILE_TEST(tests\path\add_driv)
COMPILE_TEST(tests\path\add_dir)
COMPILE_TEST(tests\path\add_file)
COMPILE_TEST(tests\path\add_ext)

.SUFFIXES:
