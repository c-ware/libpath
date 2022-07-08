/*
 * Test globbing logic
*/

#include "common.h"

void dump_match(const char *pattern, struct LibpathFiles files) {
    int index = 0;

    printf("'%s' globbed: \n", pattern);

    for(index = 0; index < files.length; index++) {
        printf("\t%s\n", files.contents[index].path);
    }

    printf("%c", '\n');
}

void assert_matched(const char *path, const char *pattern, int length) {
    struct LibpathFiles globbed_files = libpath_glob(path, pattern);

    printf("Files globbed: %i\n", globbed_files.length);
    assert(globbed_files.length == length);

    libpath_free_glob(globbed_files);
}

int main(void) {
    printf("%s", "_\n");
    assert_matched("tests" LIBPATH_SEPARATOR "assets", "*.h", 3);
    printf("%s", "A\n");

    assert_matched("tests" LIBPATH_SEPARATOR "assets", "*.*", 10);
    printf("%s", "B\n");

    /* There are three files with the cpp prefix. Make sure globbing
     * does not count them even though they might match PART prefix */
    assert_matched("tests" LIBPATH_SEPARATOR "assets", "*.c", 0);
    printf("%s", "C\n");

    /* Should match both cxx and cpp files */
    assert_matched("tests" LIBPATH_SEPARATOR "assets", "*.c*", 7);

    /* Should match both cxx and cpp files */
    assert_matched("tests" LIBPATH_SEPARATOR "assets", "foo.*", 3);

    assert_matched("tests" LIBPATH_SEPARATOR "assets", "*a*.*", 7);
    assert_matched("tests" LIBPATH_SEPARATOR "assets", "*ar*.*", 4);

    return 0;
}
