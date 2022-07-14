/*
 * Tests for compiling paths. Specifically, try a bunch of UNIX paths for now.
*/

#include "../common.h"

int main(void) {
    char buffer[1024 + 1];
    struct LibpathPath *new_path = libpath_path_init();

    /* Drive should literally not affect the final product. If it does,
     * we got a problem. */
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_DRIVE, "C:");
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_ROOT, "");
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_DIRECTORY, "foo");
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_DIRECTORY, "bar");
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_FILE, "baz.txt");

    /* Build the path, release the original structure, and make sure
     * final path is correct. */
    libpath_path_compile(new_path, buffer, 1024);
    libpath_path_free(new_path);
    assert(strcmp(buffer, "/foo/bar/baz.txt") == 0);

    /* Now.. do we get the same result if we REMOVE drive? What this is
     * testing is if the behavior is somehow linked to the presence of the
     * drive. */
    new_path = libpath_path_init();

    libpath_path_add_component(new_path, LIBPATH_COMPONENT_ROOT, "");
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_DIRECTORY, "foo");
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_DIRECTORY, "bar");
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_FILE, "baz.txt");

    libpath_path_compile(new_path, buffer, 1024);
    libpath_path_free(new_path);
    assert(strcmp(buffer, "/foo/bar/baz.txt") == 0);

    /* Awesome. So far so god. That being said, paths on UNIX do not
     * need a root directory inside of them. Paths without a root directory
     * in them will actually be treated as if they are appended to the
     * current directory, essentially acting as a shorthand for a relative
     * path. If we remove the root directory, it should be the same, except
     * without a root directory. */
    new_path = libpath_path_init();

    libpath_path_add_component(new_path, LIBPATH_COMPONENT_DIRECTORY, "foo");
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_DIRECTORY, "bar");
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_FILE, "baz.txt");

    libpath_path_compile(new_path, buffer, 1024);
    libpath_path_free(new_path);
    assert(strcmp(buffer, "foo/bar/baz.txt") == 0);

    /* Now.. how about referencing a directory ONLY? This will test whether
     * or not the compiler produces a '/' on the last directory path. */
    new_path = libpath_path_init();

    libpath_path_add_component(new_path, LIBPATH_COMPONENT_DIRECTORY, "foo");
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_DIRECTORY, "bar");

    libpath_path_compile(new_path, buffer, 1024);
    libpath_path_free(new_path);
    assert(strcmp(buffer, "foo/bar") == 0);

    /* Referencing literally only a single directory? */
    new_path = libpath_path_init();

    libpath_path_add_component(new_path, LIBPATH_COMPONENT_DIRECTORY, "foo");

    libpath_path_compile(new_path, buffer, 1024);
    libpath_path_free(new_path);
    assert(strcmp(buffer, "foo") == 0);

    /* How about only referencing a file? */
    new_path = libpath_path_init();

    libpath_path_add_component(new_path, LIBPATH_COMPONENT_FILE, "baz.txt");

    libpath_path_compile(new_path, buffer, 1024);
    libpath_path_free(new_path);
    assert(strcmp(buffer, "baz.txt") == 0);

    /* Root and a file? */
    new_path = libpath_path_init();

    libpath_path_add_component(new_path, LIBPATH_COMPONENT_ROOT, "");
    libpath_path_add_component(new_path, LIBPATH_COMPONENT_FILE, "baz.txt");

    libpath_path_compile(new_path, buffer, 1024);
    libpath_path_free(new_path);
    assert(strcmp(buffer, "/baz.txt") == 0);

    return 0;
}
