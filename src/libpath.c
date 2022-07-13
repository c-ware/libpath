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

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

/* Inclusions for traversing directories */

/* MS-DOS has a header specifically for it that contains
 * system calls for reading files */
#if defined(_MSDOS)
#include <dos.h>
#endif


/* Windows uses the FindFirstFile, and FindNextFile API
 * to do basic directory searching. */
#if defined(_WIN32)
#include <windows.h>
#endif

/* OS/2 uses the same interface as DOS. Literally. */
#if defined(__OS2__)
#include <dos.h>
#endif

#if defined(__unix__) || defined(__CW_UNIXWARE__) || defined(__APPLE__)
#include <dirent.h>
#endif

/* Inclusions for the stat system call, or any equivalent
 * of it */
#if defined(_MSDOS) || defined(_WIN32) || defined(__unix__) || defined(__CW_UNIXWARE__) || defined(__APPLE__) || defined(__OS2__)
#include <sys/stat.h>
#endif

/* Inclusions for file system operations like making and
 * removing directories */
#if defined(_MSDOS) || defined(_WIN32) || defined(__OS2__)
#include <direct.h>
#endif

#if defined(__unix__) || defined(__CW_UNIXWARE__) || defined(__APPLE__)
#include <unistd.h>
#endif


#include "libpath.h"
#include "lp_inter.h"

int libpath_join_path(char *buffer, int length, ...) {
    int written = 0;
    va_list path_segment;
    char *segment = NULL;

    INIT_VARIABLE(path_segment);
    va_start(path_segment, length);

    segment = va_arg(path_segment, char *);

    while(segment != NULL) {
        int cursor = 0;

        /* Write the path segment to the buffer */
        while(written < length && segment[cursor] != '\0') {
            buffer[written] = segment[cursor];
            cursor++;
            written++;
        }

        cursor = 0;
        segment = va_arg(path_segment, char *);

        if(segment == NULL)
            break;


        /* Write the path separator if the next one is not NULL */
        while(written < length && LIBPATH_SEPARATOR[cursor]) {
            buffer[written] = LIBPATH_SEPARATOR[cursor];
            cursor++;
            written++;
        }
    }

    buffer[written] = '\0';
    
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
#if defined(_MSDOS) || defined(__OS2__)
    return mkdir(path);
#endif

/* Microsoft is dumb and deprecated mkdir for _mkdir. See:
   https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/mkdir?view=msvc-169 */
#if defined(_WIN32)
    return _mkdir(path);
#endif

#if defined(__WATCOMC__)
    return mkdir(path);
#endif

#if defined(__unix__) || defined(__CW_UNIXWARE__) || defined(__APPLE__)
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
            if(pattern[pattern_cursor] == '\0' || name[name_cursor] == '\0') {
                /* Pattern exhausted before the name */
                if(pattern[pattern_cursor] == '\0' && name[name_cursor] != '\0')
                    return 0;

                break;
            }

#if defined(_MSDOS) || defined(__OS2__)
            if(toupper(pattern[pattern_cursor]) == toupper(name[name_cursor])) {
                name_cursor++;
                pattern_cursor++;

                continue;
            }
#else
            if(pattern[pattern_cursor] == name[name_cursor]) {
                name_cursor++;
                pattern_cursor++;

                continue;
            }
#endif

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
#if defined(_MSDOS) || defined(__OS2__)
        while(toupper(name[name_cursor]) != toupper(stop_char) && toupper(name[name_cursor]) != '\0')
            name_cursor++;
#else
        while(name[name_cursor] != stop_char && name[name_cursor] != '\0')
            name_cursor++;
#endif

        /* Name exhausted before the path */
#if defined(_MSDOS) || defined(__OS2__)
        if(toupper(name[name_cursor]) == '\0' && toupper(pattern[pattern_cursor]) != '\0')
            return 0;
#else
        if(name[name_cursor] == '\0' && pattern[pattern_cursor] != '\0')
            return 0;
#endif

    }

    return 1;
}

#if defined(__unix__) || defined(__CW_UNIXWARE__) || defined(__APPLE__)
struct LibpathFiles libpath_glob(const char *path, const char *pattern) {
    DIR *directory = NULL;
    struct dirent *entry = NULL;
    struct LibpathFiles globbed_files;
 
    INIT_VARIABLE(globbed_files);

    /* Rather than use the base carray initialization logic, we do
     * our own initialization because carray has no way to initialize
     * a stack structure but with a heap contents field. */
    globbed_files.length = 0;
    globbed_files.capacity = 5;
    globbed_files.contents = malloc(sizeof(struct LibpathFile) * 5);

    directory = opendir(path);

    /* Iterate through the contents of this directory. */
    while((entry = readdir(directory)) != NULL) {
        struct LibpathFile new_path;

        /* No thanks */
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        /* This path does not match the glob pattern-- ignore it */
        if(matches_glob(entry->d_name, pattern) == 0)
            continue;

        /* The path is too big. Yell at the user. */
        if(libpath_join_path(new_path.path, LIBPATH_GLOB_PATH_LENGTH, path,
                             entry->d_name, NULL) >= LIBPATH_GLOB_PATH_LENGTH) {
            liberror_unhandled(libpath_glob);
        }

        carray_append(&globbed_files, new_path, FILE);
    }

    closedir(directory);

    return globbed_files;
}
#endif

#if defined(_WIN32)
struct LibpathFiles libpath_glob(const char *path, const char *pattern) {
    struct LibpathFiles globbed_files;
    char glob_path[LIBPATH_GLOB_PATH_LENGTH + 1] = "";
    
    /* Windows API data for files (dumb typedefs @_@) */
    BOOL found_file = TRUE;
    WIN32_FIND_DATA file_data;
    HANDLE file_response = NULL;
 
    INIT_VARIABLE(file_data);
    INIT_VARIABLE(globbed_files);

    /* Rather than use the base carray initialization logic, we do
     * our own initialization because carray has no way to initialize
     * a stack structure but with a heap contents field. */
    globbed_files.length = 0;
    globbed_files.capacity = 5;
    globbed_files.contents = malloc(sizeof(struct LibpathFile) * 5);

    /* Build the path to the glob. */
    if(libpath_join_path(glob_path, LIBPATH_GLOB_PATH_LENGTH, path, "*.*",
                         NULL) >= LIBPATH_GLOB_PATH_LENGTH) {
        fprintf(stderr, "libpath_glob: could not glob path '%s': glob path full\n", glob_path);
        exit(EXIT_FAILURE);
    }

    /* Begin node iteration */
    file_response = FindFirstFile(glob_path, &file_data);

    /* If the response object still NULL, the file could not be found.
     * Otherwise, handle the got path, and get the next one until we
     * have exhausted everything. */
    if(file_response == NULL) {
        fprintf(stderr, "libpath_glob: failed to glob path '%s' (%s)\n", glob_path,
                strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* By default, if we get to this point, we know that the first
       file was found, so we assume it to be true that the first
       file was found (because it.. was found) */
    while(found_file == TRUE) {
        struct LibpathFile new_path;

        /* No thanks */
        if(strcmp(file_data.cFileName, ".") == 0 || strcmp(file_data.cFileName, "..") == 0) {
            found_file = FindNextFile(file_response, &file_data);

            continue;
        }

        /* This path does not match the glob pattern-- ignore it */
        if(matches_glob(file_data.cFileName, pattern) == 0)  {
            found_file = FindNextFile(file_response, &file_data);

            continue;
        }

        /* The path is too big. Yell at the user. */
        if(libpath_join_path(new_path.path, LIBPATH_GLOB_PATH_LENGTH, path,
                             file_data.cFileName, NULL) >= LIBPATH_GLOB_PATH_LENGTH)
            liberror_unhandled(libpath_glob);

        /* This is a valid file. Now, get the next. */
        carray_append(&globbed_files, new_path, FILE);
        found_file = FindNextFile(file_response, &file_data);
    }

    FindClose(file_response);

    return globbed_files;
}
#endif

#if defined(_MSDOS) || defined(__OS2__)
struct LibpathFiles libpath_glob(const char *path, const char *pattern) {
    int status = -1;
    struct _find_t node;
    struct LibpathFiles globbed_files;
    char glob_path[LIBPATH_GLOB_PATH_LENGTH + 1] = "";
 
    INIT_VARIABLE(node);
    INIT_VARIABLE(globbed_files);

    /* Rather than use the base carray initialization logic, we do
     * our own initialization because carray has no way to initialize
     * a stack structure but with a heap contents field. */
    globbed_files.length = 0;
    globbed_files.capacity = 5;
    globbed_files.contents = malloc(sizeof(struct LibpathFile) * 5);

    /* Build the path to the glob. */
    if(libpath_join_path(glob_path, LIBPATH_GLOB_PATH_LENGTH, path, "*.*",
                         NULL) >= LIBPATH_GLOB_PATH_LENGTH) {
        fprintf(stderr, "libpath_glob: could not glob path '%s': glob path full\n", glob_path);
        exit(EXIT_FAILURE);
    }

    /* Begin node iteration */
    status = _dos_findfirst(glob_path, _A_NORMAL | _A_SUBDIR, &node);

    /* Iterate through the contents of this node. */
    while(status == 0) {
        struct LibpathFile new_path;

        /* No thanks */
        if(strcmp(node.name, ".") == 0 || strcmp(node.name, "..") == 0) {
            status = _dos_findnext(&node);

            continue;
        }

        /* This path does not match the glob pattern-- ignore it */
        if(matches_glob(node.name, pattern) == 0)  {
            status = _dos_findnext(&node);

            continue;
        }

        if(libpath_join_path(new_path.path, LIBPATH_GLOB_PATH_LENGTH, path,
                             node.name, NULL) >= LIBPATH_GLOB_PATH_LENGTH) {
            liberror_unhandled(libpath_glob);
        }

        carray_append(&globbed_files, new_path, FILE);

        status = _dos_findnext(&node);
    }

    /* Handle errors */
    if(status == -1) {
        fprintf(stderr, "libpath_glob: failed to glob path '%s' (%s)\n", glob_path,
                strerror(errno));
        exit(EXIT_FAILURE);
    }

    return globbed_files;
}
#endif

void libpath_glob_free(struct LibpathFiles files) {
    free(files.contents);
}
