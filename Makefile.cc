

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
TESTS=tests/path/init tests/path/free tests/path/add_root tests/path/add_dir tests/path/add_ext tests/path/add_file tests/path/add_driv







all: $(OBJS) $(TESTS)

clean:
	$(RM) `find . -name '*.i' -print`
	$(RM) `find . -name '*.i.c' -print`
	$(RM) `find . -name '*.o' -print`
	$(RM) $(TESTS)

check:
	echo "Running test tests/path/init"
	tests/path/init
	echo "Ran test tests/path/init"
	echo "Running test tests/path/free"
	tests/path/free
	echo "Ran test tests/path/free"
	echo "Running test tests/path/add_root"
	tests/path/add_root
	echo "Ran test tests/path/add_root"
	echo "Running test tests/path/add_driv"
	tests/path/add_driv
	echo "Ran test tests/path/add_driv"
	echo "Running test tests/path/add_dir"
	tests/path/add_dir
	echo "Ran test tests/path/add_dir"
	echo "Running test tests/path/add_driv"
	tests/path/add_driv
	echo "Ran test tests/path/add_driv"
	echo "Running test tests/path/add_ext"
	tests/path/add_ext
	echo "Ran test tests/path/add_ext"

# Object file building
src/objects/path.o: src/objects/path.c
	$(CC) -c src/objects/path.c $(CFLAGS) $(CPPFLAGS) -o src/objects/path.o

# Test building
tests/path/init: tests/path/init.c
	$(CC) tests/path/init.c $(CFLAGS) $(CPPFLAGS) $(OBJS) -o tests/path/init
tests/path/free: tests/path/free.c
	$(CC) tests/path/free.c $(CFLAGS) $(CPPFLAGS) $(OBJS) -o tests/path/free
tests/path/add_root: tests/path/add_root.c
	$(CC) tests/path/add_root.c $(CFLAGS) $(CPPFLAGS) $(OBJS) -o tests/path/add_root
tests/path/add_driv: tests/path/add_driv.c
	$(CC) tests/path/add_driv.c $(CFLAGS) $(CPPFLAGS) $(OBJS) -o tests/path/add_driv
tests/path/add_dir: tests/path/add_dir.c
	$(CC) tests/path/add_dir.c $(CFLAGS) $(CPPFLAGS) $(OBJS) -o tests/path/add_dir
tests/path/add_ext: tests/path/add_ext.c
	$(CC) tests/path/add_ext.c $(CFLAGS) $(CPPFLAGS) $(OBJS) -o tests/path/add_ext
tests/path/add_file: tests/path/add_file.c
	$(CC) tests/path/add_file.c $(CFLAGS) $(CPPFLAGS) $(OBJS) -o tests/path/add_file

.PHONY: all clean check
.SUFFIXES:
