#include "common.h"

int main(void) {
    char buffer_a[256 + 1];
    char buffer_b[12 + 1];
    char buffer_c[6 + 1];
    char buffer_d[1 + 1];
    char buffer_e[0 + 1];

    /* Should be filled properly */
    assert(libpath_join_path(buffer_a, 256, "foo", "bar", "baz", NULL) == 9);
    assert(strcmp(buffer_a, "foobarbaz") == 0);
    assert(buffer_a[9] == '\0');

    assert(libpath_join_path(buffer_b, 12, "foo", "bar", "baz", NULL) == 9);
    assert(strcmp(buffer_b, "foobarbaz") == 0);
    assert(buffer_b[9] == '\0');

    /* Should not be able to be filled */
    assert(libpath_join_path(buffer_c, 6, "foo", "bar", "baz", NULL) == 7);
    assert(strcmp(buffer_c, "foobar") == 0);
    assert(buffer_c[6] == '\0');

    assert(libpath_join_path(buffer_d, 1, "foo", "bar", "baz", NULL) == 2);
    assert(strcmp(buffer_d, "f") == 0);
    assert(buffer_d[1] == '\0');

    /* No bytes should be written */
    assert(libpath_join_path(buffer_e, 0, "foo", "bar", "baz", NULL) == 1);
    assert(strcmp(buffer_e, "") == 0);
    assert(buffer_e[0] == '\0');

    return EXIT_SUCCESS;
}
