/*
 * Test the releasing of the path object. Basically, verify
 * that the operation does not cause a segfault or whatever.
*/

#include "common.h"

int main() {
    struct LibpathPath *my_path = libpath_path_init();

    libpath_path_free(my_path);

    return 0;
}
