# libpath

Libpath is a C library for portably handling paths in a generic and system
independent fashion. It supports common operations like directory creation
and removal, iterating through directories, system-independent path representation,
and more for the following operating systems:
    - MS-DOS
</br>
    - Windows NT
</br>
    - OS/2
</br>
    - \*NIX
</br>
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
normal build steps using `Makefile.cc`. Note, however, that this is for
building *tests*. If you want to use libpath in your project, see `Using Libpath
In Your Project`.

### ULTRIX VCC
VAX ULTRIX 4.5, which this was tested on, has two compilers on it-- `vcc`, and `cc`.
This library was tested with `vcc`, and will likely not work with `cc`. Because of
this, if you are compiling on ULTRIX, please use `Makefile.vcc`

### OS/2 Warp, DOS, and NT
OS/2, DOS, and NT all have no C compiler installed on them by default. However,
Watcom is one of the compilers that can be built on them. While MSVC support is in
the works, currently, this only supports a Makefile for the Watcom compiler. If
you are using Watcom, please use `Makefile.wat`

## Possible Questions

### Why is the code so ugly?
It's not. At least, I hope it's not. What you are probably looking at is the *preprocessed*
source code of some parts of libpath. Some source and header files will have files which are
intended to be preprocessed before being pushed as \*.m4c and \*.m4h respectively. If the
source code in their preprocessed forms are too much for you-- and I don't blame you-- then
see the non-preprocessed code.

### Why are there so many changes in commits?
Well, it's once again because of our code generation. If you think it's weird, so be it, but
you have to remember that this is a library that is intended to be very portable. If our commit
logs are a bit bloated, and that's the worst thing someone can find, I think I did an OK job.
