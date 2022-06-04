#include "common.h"

int main(void) {
    libpath_mkdir("foo", 0777);
    libpath_mkdir("bar", 0777);
    libpath_mkdir("baz", 0777);

    assert(libpath_rmdir("foo") == 0);
    assert(libpath_rmdir("bar") == 0);
    assert(libpath_rmdir("baz") == 0);

    assert(libpath_rmdir("foo") == -1);
    assert(libpath_rmdir("bar") == -1);
    assert(libpath_rmdir("baz") == -1);

    return EXIT_SUCCESS;
}
