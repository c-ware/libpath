/*
 * Test the initialization of the path object. Basically, verify
 * that it's initialized in the way we expect it to be.
*/

#include "common.h"

int main() {
    struct LibpathPath *my_path = libpath_path_init();

    ASSERT_PTRNEQ(my_path, CWUTILS_NULL);
    ASSERT_PTRNEQ(my_path->contents, CWUTILS_NULL);
    ASSERT_NUMEQ(my_path->length, 0);
    ASSERT_NUMEQ(my_path->capacity, 3);
    ASSERT_NUMEQ(my_path->used, 0);

    return 0;
}
