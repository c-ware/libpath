/*
 * C-Ware License
 * 
 * Copyright (c) 2022, C-Ware
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Redistributions of modified source code must append a copyright notice in
 *    the form of 'Copyright <YEAR> <NAME>' to each modified source file's
 *    copyright notice, and the standalone license file if one exists.
 *
 * A "redistribution" can be constituted as any version of the source code
 * that is intended to comprise some other derivative work of this code. A
 * fork created for the purpose of contributing to any version of the source
 * does not constitute a truly "derivative work" and does not require listing.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * Implementations of the libpath functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* MS-DOS has a header specifically for it that contains
 * system calls for reading files */
#if defined(_MSDOS)
#include <dos.h>
#endif

/* Inclusions for the stat system call, or any equivalent
 * of it */
#if defined(_MSDOS) || defined(_WIN32) || defined(__unix__)
#include <sys/stat.h>
#endif

/* Inclusions for file system operations like making and
 * removing directories */
#if defined(_MSDOS)
#include <direct.h>
#endif

#if defined(__unix__) || defined(_WIN32)
#include <unistd.h>
#endif

#include "libpath.h"
#include "libpath_internal.h"

int libpath_join_path(char *buffer, int length, ...) {
    char *path = NULL;
    size_t written = 0;
    va_list paths = {0};
    int buffer_cursor = 0;

    liberror_is_null(libpath_join_path, buffer);
    liberror_is_negative(libpath_join_path, length);

    va_start(paths, length);

    /* Get each path component */
    while((path = va_arg(paths, char*)) != NULL) {
        int path_cursor = 0;

        if(buffer_cursor == length) {
            written = length + 1;

            break;

        }

        /* Write the path */
        for(path_cursor = 0; path[path_cursor] != '\0'; path_cursor++) {
            if(buffer_cursor == length)
                break;

            buffer[buffer_cursor] = path[path_cursor];
            buffer_cursor++;
            written++;
        }
    }

    va_end(paths);
    buffer[buffer_cursor] = '\0';

    return written;
}

int libpath_exists(const char *path) {
    struct stat stat_buffer;

    liberror_is_null(libpath_exists, path);

    if(stat(path, &stat_buffer) == -1)
        return 0;

    return 1;
}

int libpath_rmdir(const char *path) {
    return rmdir(path);
}

int libpath_mkdir(const char *path, int mode) {
#if defined(_MSDOS)
    return mkdir(path);
#endif

#if defined(__WATCOMC__)
    return mkdir(path);
#endif

#if defined(__unix__)
    return mkdir(path, mode);
#endif
}

/*
 * GLOBBING LOGIC
*/

/*
 * Honestly, this function is likely to be the most complex function in 
 * libpath, so it deserves a lot of explanation. This function determines 
 * whether or not a given path will 'match' a glob. Currently, this function
 * supports the following syntax:
 *
 * * - Match an arbitrary number of characters until the character after it
 *     is found.
 *
 *     EXAMPLE:
 *        *.txt - Match any character until a period
 *        *.*   - Match any character until a period, then any character until the
 *                NUL byte.
 *        foo*  - Match 'foo' then stop at the NUL byte
*/
static int matches_glob(const char *name, const char *pattern) {
    int name_cursor = 0;
    int pattern_cursor = 0;

    while(name[name_cursor] != '\0') {
        int stop_char = '\0';

        /* Match characters in the pattern until a wildcard
         * character is found. */
        while(pattern[pattern_cursor] != '*') {
            if(pattern[pattern_cursor] == '\0' || name[name_cursor] == '\0')
                break;

            if(pattern[pattern_cursor] == name[name_cursor]) {
                name_cursor++;
                pattern_cursor++;

                continue;
            }

            /* Match not valid! */
            return 0;
        }

        /* Now, unless the glob is a flat match, e.g ('foo' and not 'foo*'),
         * then pattern[pattern_cursor] should be an asterisk, which implies
         * a wild card. */
        if(pattern[pattern_cursor] == '*') {
            stop_char = pattern[pattern_cursor + 1]; /* Can be a NUL byte */
            pattern_cursor++;
        }

        /* Keep matching until the stop_char is found. In situations
         * where this is a flat match, this will just immediately stop,
         * as name[name_cursor] will be on the NUL byte. This section
         * will essentially just exhaust the wildcard.
        */
        while(name[name_cursor] != stop_char)
            name_cursor++;

        /* Name exhausted before the path */
        if(name[name_cursor] == '\0' && pattern[pattern_cursor] != '\0')
            return 0;
    }

    return 1;
}

#if defined(__unix__)
struct LibpathFiles *libpath_glob(const char *path, const char *pattern) {
    DIR *directory = NULL;
    struct dirent *entry = NULL;
    struct LibpathFiles *globbed_files = NULL;
 
    directory = opendir(path);
    globbed_files = carray_init(globbed_files, FILE);

    /* Iterate through the contents of this directory. */
    while((entry = readdir(directory)) != NULL) {
        struct LibpathFile new_path;

        /* This path does not match the glob pattern-- ignore it */
        if(libpath_matches_glob(entry->d_name, pattern) == 0)
            continue;

        /* Replace this with libpath_join_path eventually.. */
        sprintf(new_path.path, "%s/%s", path, entry->d_name);

        carray_append(globbed_files, new_path, FILE);
    }


    closedir(directory);

    return globbed_files;
}

#endif
