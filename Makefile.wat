

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
TESTS=tests\path\init.exe tests\path\free.exe tests\path\add_root.exe tests\path\add_dir.exe tests\path\add_ext.exe tests\path\add_file.exe tests\path\add_driv.exe







all: $(OBJS) $(TESTS) .symbolic

clean: .symbolic
	$(RM) $(TESTS)

check: .symbolic
	echo "Running test tests\path\init.exe"
	tests\path\init.exe
	echo "Ran test tests\path\init.exe"
	echo "Running test tests\path\free.exe"
	tests\path\free.exe
	echo "Ran test tests\path\free.exe"
	echo "Running test tests\path\add_root.exe"
	tests\path\add_root.exe
	echo "Ran test tests\path\add_root.exe"
	echo "Running test tests\path\add_driv.exe"
	tests\path\add_driv.exe
	echo "Ran test tests\path\add_driv.exe"
	echo "Running test tests\path\add_dir.exe"
	tests\path\add_dir.exe
	echo "Ran test tests\path\add_dir.exe"
	echo "Running test tests\path\add_file.exe"
	tests\path\add_file.exe
	echo "Ran test tests\path\add_file.exe"
	echo "Running test tests\path\add_ext.exe"
	tests\path\add_ext.exe
	echo "Ran test tests\path\add_ext.exe"

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
tests\path\add_root.exe: tests\path\add_root.c
	$(CC) tests\path\add_root.c $(CFLAGS) $(CPPFLAGS) /fo=tests\path\add_root.obj
	$(LD) FILE tests\path\add_root.obj,$(OBJS) NAME tests\path\add_root.exe
tests\path\add_driv.exe: tests\path\add_driv.c
	$(CC) tests\path\add_driv.c $(CFLAGS) $(CPPFLAGS) /fo=tests\path\add_driv.obj
	$(LD) FILE tests\path\add_driv.obj,$(OBJS) NAME tests\path\add_driv.exe
tests\path\add_dir.exe: tests\path\add_dir.c
	$(CC) tests\path\add_dir.c $(CFLAGS) $(CPPFLAGS) /fo=tests\path\add_dir.obj
	$(LD) FILE tests\path\add_dir.obj,$(OBJS) NAME tests\path\add_dir.exe
tests\path\add_file.exe: tests\path\add_file.c
	$(CC) tests\path\add_file.c $(CFLAGS) $(CPPFLAGS) /fo=tests\path\add_file.obj
	$(LD) FILE tests\path\add_file.obj,$(OBJS) NAME tests\path\add_file.exe
tests\path\add_ext.exe: tests\path\add_ext.c
	$(CC) tests\path\add_ext.c $(CFLAGS) $(CPPFLAGS) /fo=tests\path\add_ext.obj
	$(LD) FILE tests\path\add_ext.obj,$(OBJS) NAME tests\path\add_ext.exe

.SUFFIXES:
