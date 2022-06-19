/*
 * Test globbing logic
*/

#include "common.h"

int main(void) {
    struct LibpathFiles globbed_files_a = libpath_glob("tests/assets", "*.h");
    struct LibpathFiles globbed_files_b = libpath_glob("tests/assets", "*.*");
    struct LibpathFiles globbed_files_c = libpath_glob("tests/assets", "*.c");

    assert(globbed_files_a.length == 3);
    assert(globbed_files_b.length == 6);

    /* There are three files with the cpp prefix. Make sure globbing
     * does not count them even though they might match PART prefix */
    assert(globbed_files_c.length == 0);

    libpath_free_glob(globbed_files_a);
    libpath_free_glob(globbed_files_b);
    libpath_free_glob(globbed_files_c);

    return 0;
}
