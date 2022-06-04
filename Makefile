# This Makefile is the output of a template Makefile that was
# processed by the m4 macro preprocessor. It is not intended
# to be human readable.

CC=cc
PREFIX=/usr/local
CFLAGS=
OBJS=src/exists.o src/cwd.o src/mkdir.o src/join_path.o src/rmdir.o src/is_directory.o 
TESTS=tests/test_rmdir.out tests/test_join_path.out tests/test_mkdir.out 
DOCS=./doc/libpath_join_path.cware ./doc/libpath.cware ./doc/libpath_exists.cware ./doc/libpath_mkdir.cware 
MANNAMES=libpath_join_path.cware libpath.cware libpath_exists.cware libpath_mkdir.cware 
DEBUGGER=

all: $(OBJS) $(TESTS)

clean:
	rm -f $(TESTS)
	rm -f $(OBJS)

check:
	./scripts/check.sh $(DEBUGGER)

install:
	for manual in $(MANNAMES); do					  \
		cp doc/$$manual $(PREFIX)/share/man/mancware; \
	done

uninstall:
	for manual in $(MANNAMES); do					 \
		rm -f $(PREFIX)/share/man/mancware/$$manual; \
    done

.c.out:
	$(CC) $< $(OBJS) $(CFLAGS) -o $@

.c.o:
	$(CC) -c $< $(CFLAGS) -o $@
