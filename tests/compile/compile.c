/*
 * Tests for compiling paths.
*/

#include "../common.h"

int main(void) {
    char buffer[2048 + 1] = "";
    struct LibpathPath *new_path = libpath_path_init();

    libpath_path_add_component(new_path, LIBPATH_COMPONENT_DRIVE, "foo");
    assert(strcmp(new_path->contents[0].component, "foo") == 0);
    assert(new_path->contents[0].type == LIBPATH_COMPONENT_DRIVE);
    assert(new_path->length == 1);
    
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_FILE, "bar");
    assert(strcmp(new_path->contents[1].component, "bar") == 0);
    assert(new_path->contents[1].type == LIBPATH_COMPONENT_FILE);
    assert(new_path->length == 2);

    /* This is creates an invalid path (directories cannot come after files) */
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_DIRECTORY, "baz");
    assert(strcmp(new_path->contents[2].component, "baz") == 0);
    assert(new_path->contents[2].type == LIBPATH_COMPONENT_DIRECTORY);
    assert(new_path->length == 3);

    libpath_path_compile(new_path, buffer, 2048);

    libpath_path_free(new_path);

    return 0;
}
