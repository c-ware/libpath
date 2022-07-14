/*
 * Tests for compiling paths. Specifically, make sure adding all types of
 * components will be successful (regardless of whether or not they are in
 * a proper order. hint: its not)
*/

#include "../common.h"

int main(void) {
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

    libpath_path_add_component(new_path, LIBPATH_COMPONENT_ROOT, "");
    assert(strcmp(new_path->contents[3].component, "") == 0);
    assert(new_path->contents[3].type == LIBPATH_COMPONENT_ROOT);
    assert(new_path->length == 4);

    libpath_path_free(new_path);

    return 0;
}
