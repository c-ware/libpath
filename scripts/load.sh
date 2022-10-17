#!/bin/sh
# Process all files with m4 and output them to their respective directories.
# This should be called from the root directory of the project.

# Process m4c files with m4
for M4C_FILE in `find . -type f -name '*.m4c'`; do
    STRIPPED=`echo $M4C_FILE | sed 's/\.m4c$/.c/g'`;
    m4 -Itemplate $M4C_FILE > $STRIPPED;
done

# Process m4h files with m4
for M4H_FILE in `find . -type f -name '*.m4h'`; do
    STRIPPED=`echo $M4H_FILE | sed 's/\.m4h$/.h/g'`;
    m4 -Itemplate $M4H_FILE > $STRIPPED;
done

# These environment variables tell certain Make variables what to store
# to allow for consistency between them.

UNIX_OBJS="src/objects/path.o"
UNIX_TESTS="tests/path/init tests/path/free"
UNIX_CPPFLAGS="-I/usr/include -Isrc/liberror -Isrc/objects -Itests -Isrc -DLIBERROR_ENABLED -DLIBERROR_STREAM=stderr"

WAT_OBJS="src\objects\path.obj"
WAT_TESTS="tests\path\init.exe tests\path\free.exe"
WAT_CPPFLAGS="-i\usr\include -isrc\liberror -isrc\objects -itests -isrc -DLIBERROR_ENABLED -DLIBERROR_STREAM=stderr"


# Process the Makefiles
m4 -DMK_CPPFLAGS="$UNIX_CPPFLAGS" -DMK_OBJECTS="$UNIX_OBJS" \
    -DMK_TESTS="$UNIX_TESTS" \
    template/Makefile.cc > Makefile.cc

m4 -DMK_CPPFLAGS="$UNIX_CPPFLAGS" -DMK_OBJECTS="$UNIX_OBJS" \
    -DMK_TESTS="$UNIX_TESTS" \
    template/Makefile.vcc > Makefile.vcc

m4 -DMK_CPPFLAGS="$WAT_CPPFLAGS" -DMK_OBJECTS="$WAT_OBJS" \
    -DMK_TESTS="$WAT_TESTS" \
    template/Makefile.wat > Makefile.wat

# Load documentation
cat src/libpath.h | docgen-extractor-c | docgen-compiler-c | docgen-backend-manpage --section 'cware' --title 'C-Ware Manuals' --date "`date +'%b %d, %Y'`"
cat src/objects/path.h | docgen-extractor-c | docgen-compiler-c | docgen-backend-manpage --section 'cware' --title 'C-Ware Manuals' --date "`date +'%b %d, %Y'`"
