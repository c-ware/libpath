#include "common.h"

int main(void) {
    assert(libpath_mkdir("foo", 0777) == 0);
    assert(libpath_mkdir("bar", 0777) == 0);
    assert(libpath_mkdir("baz", 0777) == 0);

    assert(libpath_mkdir("foo", 0777) == -1);
    assert(libpath_mkdir("bar", 0777) == -1);
    assert(libpath_mkdir("baz", 0777) == -1);

    return EXIT_SUCCESS;
}
