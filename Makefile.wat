

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
CPPFLAGS=$(OSFLAGS) -i\usr\include -isrc\liberror -isrc\objects -itests -isrc -DLIBERROR_ENABLED -DLIBERROR_STREAM=stderr
OBJS=src\objects\path.obj
TESTS=tests\path\init.exe tests\path\free.exe





all: $(OBJS) $(TESTS) .symbolic

clean: .symbolic
	$(RM) $(TESTS)

# Object file building
src\objects\path.obj: src\objects\path.c
	$(CC) src\objects\path.c $(CFLAGS) $(CPPFLAGS) /fo=src\objects\path.obj

# Test building
tests\path\init.exe: tests\path\init.c
	$(CC) tests\path\init.c $(CFLAGS) $(CPPFLAGS) /fo=tests\path\init.obj
	$(LD) FILE tests\path\init.obj,$(OBJS) NAME tests\path\init.exe
tests\path\free.exe: tests\path\free.c
	$(CC) tests\path\free.c $(CFLAGS) $(CPPFLAGS) /fo=tests\path\free.obj
	$(LD) FILE tests\path\free.obj,$(OBJS) NAME tests\path\free.exe

.SUFFIXES:
