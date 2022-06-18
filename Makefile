OBJS=./src/libpath.o 
TESTS=./tests/joinpath ./tests/mkdir ./tests/rmdir 
HEADERS=./src/lp_inter.h ./src/libpath.h ./src/carray/carray.h ./src/liberror/liberror.h 
CC=cc
PREFIX=/usr/local
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

./tests/joinpath: ./tests/joinpath.c ./tests/common.h $(OBJS)
	$(CC) ./tests/joinpath.c -o ./tests/joinpath $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

./tests/mkdir: ./tests/mkdir.c ./tests/common.h $(OBJS)
	$(CC) ./tests/mkdir.c -o ./tests/mkdir $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

./tests/rmdir: ./tests/rmdir.c ./tests/common.h $(OBJS)
	$(CC) ./tests/rmdir.c -o ./tests/rmdir $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

./src/libpath.o: ./src/libpath.c ./src/libpath.h ./src/lp_inter.h
	$(CC) -c $(CFLAGS) ./src/libpath.c -o ./src/libpath.o $(LDFLAGS) $(LDLIBS)

libpath.so: $(OBJS)
	$(CC) $(OBJS) -shared -o libpath.so
