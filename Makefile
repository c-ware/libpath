OBJS=src/iter.o src/libpath.o src/compile/error.o src/compile/path.o src/compile/backends/unix.o 
TESTS=tests/joinpath tests/mkdir tests/globbing tests/rmdir tests/compile/compile tests/compile/adding 
HEADERS=src/lp_inter.h src/libpath.h src/compile/path.h src/carray/carray.h src/liberror/liberror.h 
CC=cc
PREFIX=/usr/local
LDFLAGS=
LDLIBS=
CFLAGS=-fpic

all: $(OBJS) $(TESTS) libpath.so

clean:
	rm -rf $(OBJS)
	rm -rf $(TESTS)
	rm -rf vgcore.*
	rm -rf core*
	rm -rf libpath.so

install:
	mkdir -p $(PREFIX)
	mkdir -p $(PREFIX)/lib
	mkdir -p $(PREFIX)/include
	mkdir -p $(PREFIX)/include/libpath
	install -m 755 libpath.so $(PREFIX)/lib
	install -m 644 $(HEADERS) $(PREFIX)/include/libpath

uninstall:
	rm -rf $(PREFIX)/include/libpath
	rm -f $(PREFIX)/lib/libpath.so

tests/joinpath: tests/joinpath.c tests/common.h $(OBJS)
	$(CC) tests/joinpath.c -o tests/joinpath $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

tests/mkdir: tests/mkdir.c tests/common.h $(OBJS)
	$(CC) tests/mkdir.c -o tests/mkdir $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

tests/globbing: tests/globbing.c tests/common.h $(OBJS)
	$(CC) tests/globbing.c -o tests/globbing $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

tests/rmdir: tests/rmdir.c tests/common.h $(OBJS)
	$(CC) tests/rmdir.c -o tests/rmdir $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

tests/compile/compile: tests/compile/compile.c tests/common.h $(OBJS)
	$(CC) tests/compile/compile.c -o tests/compile/compile $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

tests/compile/adding: tests/compile/adding.c tests/common.h $(OBJS)
	$(CC) tests/compile/adding.c -o tests/compile/adding $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

src/iter.o: src/iter.c
	$(CC) -c $(CFLAGS) src/iter.c -o src/iter.o

src/libpath.o: src/libpath.c src/libpath.h src/lp_inter.h
	$(CC) -c $(CFLAGS) src/libpath.c -o src/libpath.o

src/compile/error.o: src/compile/error.c src/compile/path.h src/libpath.h src/lp_inter.h
	$(CC) -c $(CFLAGS) src/compile/error.c -o src/compile/error.o

src/compile/path.o: src/compile/path.c src/compile/path.h src/libpath.h src/lp_inter.h
	$(CC) -c $(CFLAGS) src/compile/path.c -o src/compile/path.o

src/compile/backends/unix.o: src/compile/backends/unix.c src/compile/path.h src/libpath.h src/lp_inter.h
	$(CC) -c $(CFLAGS) src/compile/backends/unix.c -o src/compile/backends/unix.o

libpath.so: $(OBJS)
	$(CC) $(OBJS) -shared -o libpath.so
