# libpath

Libpath is a C library for portably handling paths in a generic and system
independent fashion. It supports common operations like directory creation
and removal, iterating through directories, system-independent path representation,
and more for the following operating systems:
    - MS-DOS
    - Windows NT
    - OS/2
    - \*NIX
    - OpenVMS

## System-independent paths
A big part of what makes libpath easy to port to other systems is that it comes
with interfaces for writing system-independent paths, which can then be compiled
to paths that match other system's path layouts. For example..

```c
#include "libpath/libpath.h"

int main(void) {
    struct LibpathPath *path = libpath_path_init();  

    /* Make a path which will compile to:
     * UNIX: /foo/bar/baz/tuna.txt
     * OS2, DOS, NT: C:\foo\bar\baz\tuna.txt
     * VMS: DKA0:[000000.foo.bar.baz]tuna.txt
    */
    libpath_path_add_root(path);
    libpath_path_add_directory(path, "foo");
    libpath_path_add_directory(path, "bar");
    libpath_path_add_directory(path, "baz");
    libpath_path_add_file(path, "tuna");
    libpath_path_add_ext(path, "txt");

    libpath_path_free(path);

    return 0;
}
```

## Test build instructions
When using libpath, there are some things that must be done to build tests.
Unless you are on an operating system specified below, you can go through the
normal build steps. Note, however, that this is for building *tests*. If you
want to use libpath in your project, see `Using Libpath In Your Project`.

### NeXTSTEP
To build on NeXTSTEP, you will need to pass `CPP=path/to/cpp` for your build.

### ULTRIX
To build on ULTRIX, You will need to add `-D__ULTRIX__` to your OSFLAGS to
signal to the code that you are building on ULTRIX.

### QuasiBSD
To build on QuasiBSD, You will need to add `-D__QuasiBSD__` to your OSFLAGS to
signal to the code that you are building on QuasiBSD.

## Using Libpath In Your Project
