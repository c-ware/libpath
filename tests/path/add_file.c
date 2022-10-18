/*
 * Test the addition of a "root" of the path.
*/

#include "common.h"

int main() {
    struct LibpathPath *my_path = libpath_path_init();

    libpath_path_add_root(my_path);

    LIBPATH_PATH_VALIDATE(my_path);
    ASSERT_PTREQ(my_path->contents[0].text, CWUTILS_NULL);
    ASSERT_NUMEQ(my_path->contents[0].type, LIBPATH_PATH_TYPE_ROOT);

    return 0;
}
