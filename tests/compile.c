/*
 * Tests for compiling paths.
*/

#include "common.h"

int main(void) {
    char buffer[2048 + 1] = "";
    struct LibpathPath *new_path = libpath_path_init();

    libpath_path_add_component(new_path, 0, "foo");
    assert(strcmp(new_path->contents[0].component, "foo") == 0);
    assert(new_path->length == 1);

    libpath_path_compile(new_path, buffer, 2048);

    libpath_path_free(new_path);

    return 0;
}
