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
 * @docgen: project
 * @brief: portably handle file system paths and operations
 * @name: libpath
 *
 * @description
 * @A library for portably handling file system paths, and file system
 * @operations on multiple operating systems. It comes with pre-defined
 * @paths, and constants for operating system specific information like
 * @maximum path length.
 * @
 * @This library, while intended for portably handling file systems, is also
 * @about making sure code will work on other platforms rather than being
 * @entirely "correct" so to speak. For example, on platforms like MS-DOS,
 * @there is no 'user' directory like there is on Windows, Linux, and UNIX.
 * @However, the LIBPATH_USER_DIR constant will still have a defined value
 * @on MS-DOS. This is to make sure that the code can still compile and
 * @function, even if it is not "technically correct."
 * @description
 *
 * @reference: cware(cware)
*/

#ifndef CWARE_LIBCWPATH_H
#define CWARE_LIBCWPATH_H

#define CWARE_LIBCWPATH_VERSION  "1.0.2"

/* Limits */
#define LIBPATH_GLOB_PATH_LENGTH    256 + 1

/* 
 * The maximum path lengths of various operating systems
 * These values will contain at *least* the correct number of bytes
 * to contain a path. They may be rounded up to a power of two. The
 * actual path length should be LIBPATH_MAX_PATH + 1, where the + 1
 * is for the NUL byte.
*/
#if defined(_MSDOS)
#define LIBPATH_MAX_PATH    65
#endif

#if defined(_WIN32) || defined(__OS2__)
#define LIBPATH_MAX_PATH    260
#endif

#if defined(__linux__)
#define LIBPATH_MAX_PATH    4096
#endif

#if defined(ultrix) || defined(__FreeBSD__) || defined(__OpenBSD__) || \
    defined(__sun)  || defined(__APPLE__)   || defined(__CW_UNIXWARE__)
#define LIBPATH_MAX_PATH    1024
#endif

#if defined(__WATCOMC__)
#define LIBPATH_MAX_PATH    65
#endif

/*
 * Different types of path separators for different kinds of platforms.
 * Thankfully, most operating systems are either Windows, UNIX, or a
 * *NIX like, so its not that big of a deal.
*/
#if defined(__unix__) || defined(__APPLE__) || defined(__CW_UNIXWARE__)
#define LIBPATH_SEPARATOR   "/"
#endif

#if defined(_MSDOS) || defined(_WIN32) || defined(__OS2__)
#define LIBPATH_SEPARATOR   "\\"
#endif

/*
 * The constant that represents a 'failed' path operation. This exists
 * purely for the sake of future proofing, as another operating system
 * may not have the same return code.
*/
#if defined(__unix__) || defined(__CW_UNIXWARE__) || defined(__APPLE__) || \
    defined(_MSDOS)   || defined(_WIN32) || defined(__OS2__)
#define LIBPATH_FAILURE -1
#endif

/*
 * The constant that represents a 'successful' path operation. This exists
 * purely for the sake of future proofing, as another operating system
 * may not have the same return code.
*/
#if defined(__unix__) || defined(__CW_UNIXWARE__) || defined(__APPLE__) || \
    defined(_MSDOS)   || defined(_WIN32)          || defined(__OS2__)
#define LIBPATH_SUCCESS 0
#endif

/* Enumerations for the difference types of components. */
#define LIBPATH_COMPONENT_DRIVE     0
#define LIBPATH_COMPONENT_FILE      1
#define LIBPATH_COMPONENT_DIRECTORY 2
#define LIBPATH_COMPONENT_ROOT      3

/*
 * @docgen: structure
 * @brief: a file on the filesystem
 * @name: LibpathFile
 *
 * @field path: the path to the file
 * @type: char *
*/
struct LibpathFile {
    char path[LIBPATH_GLOB_PATH_LENGTH + 1];
};

/*
 * @docgen: structure
 * @brief: an array of files
 * @name: LibpathFiles
 *
 * @field length: the length of the array
 * @type: int
 *
 * @field capacity: the capacity of the array
 * @type: int
 *
 * @field contents: the files in the array
 * @type: struct LibpathFile
*/
struct LibpathFiles {
    int length;
    int capacity;
    struct LibpathFile *contents;
};

/*
 * @docgen: function
 * @brief: join a variable number of path segments into a single buffer
 * @name: libpath_join_path
 *
 * @include: libpath.h
 *
 * @description
 * @Join a variable number of path components into a single string. All
 * @path components will automatically have path segments put between
 * @them which match the corresponding path for the system it is running
 * @on. The final path parameter MUST be NULL, and the final string should
 * @be large enough to have a NUL byte written to it.
 * @description
 *
 * @example
 * @#include "libpath.h"
 * @
 * @int main(void) {
 * @    char buffer[1024 + 1];
 * @
 * @    libpath_join_path(buffer, 1024, LIBPATH_HOME_DIR, "config", NULL); 
 * @
 * @    return 0;
 * @}
 * @example
 *
 * @error: buffer is NULL
 * @error: length is negative
 * 
 * @param buffer: the buffer to write to
 * @type: char *
 *
 * @param length: the length of the buffer
 * @type: int
 *
 * @return: the number of bytes written
 * @type: int
*/
/*
#if defined(__GNUC__)
int libpath_join_path(char *buffer, int length, ...)
    __attribute__((sentinel(0)));
#else
*/
int libpath_join_path(char *buffer, int length, ...);
/*
#endif
*/

/*
 * @docgen: function
 * @brief: make a new directory at the provided path
 * @name: libpath_mkdir
 *
 * @include: libpath.h
 *
 * @description
 * @Creates a new directory at a given path and uses the provided mode for
 * @the directory permissions. That being said, some operating systems, like
 * @MS-DOS, do not have a directory permissions configuration method through
 * @their mkdir function. In cases like these, simply pass zero.
 * @description
 *
 * @example
 * @#include <stdio.h>
 * @#include <errno.h>
 * @#include <stdlib.h>
 * @#include <string.h>
 * @
 * @#include "libpath.h"
 * @
 * @int main(void) {
 * @    if(libpath_mkdir(LIBPATH_ROOT_DIR, "prog_config") == LIBPATH_FAILURE) {
 * @        fprintf(stderr, "prog: failed to make directory (%s)\n", strerror(errno));
 * @        exit(EXIT_FAILURE);
 * @    }
 * @
 * @    return 0;
 * @}
 * @example
 *
 * @error: path is NULL
 *
 * @param path: the path to make the directory at
 * @type: const char *
 *
 * @param mode: the file permissions
 * @type: int
 *
 * @return: LIBPATH_SUCCESS on success, and LIBPATH_FAILURE on failure
 * @type: int
*/
int libpath_mkdir(const char *path, int mode);

/*
 * @docgen: function
 * @brief: remove a directory
 * @name: libpath_rmdir
 *
 * @include: libpath.h
 *
 * @description
 * @Removes a directory at the path specified. Note that some operating
 * @systems may not allow you to remove a directory if it is not empty.
 * @description
 *
 * @example
 * @#include <stdio.h>
 * @#include <errno.h>
 * @#include <stdlib.h>
 * @#include <string.h>
 * @
 * @#include "libpath.h"
 * @
 * @int main(void) {
 * @    if(libpath_rmdir(LIBPATH_ROOT_DIR, "prog_config") == LIBPATH_FAILURE) {
 * @        fprintf(stderr, "prog: failed to remove directory (%s)\n", strerror(errno));
 * @        exit(EXIT_FAILURE);
 * @    }
 * @
 * @    return 0;
 * @}
 * @example
 *
 * @error: path is NULL
 *
 * @param path: the path of the directory to remove
 * @type: const char *
 *
 * @return: LIBPATH_SUCCESS on success, and LIBPATH_FAILURE on failure
 * @type: int
*/
int libpath_rmdir(const char *path);

/*
 * Determines whether or not the path provided exists or not.
 *
 * @param path: the path to check
 * @return: 1 if the path exists, 0 if it does not exist
*/

/*
 * @docgen: function
 * @brief: determine if a path exists on the file system
 * @name: libpath_exists
 *
 * @include: libpath.h
 * 
 * @description
 * @Determine if a path exists on the file system. This function is garunteed
 * @to work on all types of file system components. Specifically, files AND
 * @directories.
 * @description
 *
 * @example
 * @#include <stdio.h>
 * @#include <errno.h>
 * @#include <stdlib.h>
 * @#include <string.h>
 * @
 * @#include "libpath.h"
 * @
 * @int main(void) {
 * @    if(libpath_exists(LIBPATH_ROOT_DIR, "prog_config") == LIBPATH_FAILURE) {
 * @        fprintf(stderr, "%s", "prog: cannot make directory-- already exists\n");
 * @        exit(EXIT_FAILURE);
 * @    }
 * @
 * @    return 0;
 * @}
 * @example
 *
 * @error: path is NULL
 * 
 * @param path: the path to check
 * @type: const char *
 *
 * @return: 1 if the path exists, and 0 if it does not
 * @type: int
*/
int libpath_exists(const char *path);

/*
 * @docgen: function
 * @brief: extract files and directories from a path based off a pattern
 * @name: libpath_glob
 *
 * @include: libpath.h
 *
 * @description
 * @This function will extract all files and subdirectories inside of a
 * @directory based off a pattern. The pattern is similar (although fairly
 * @limited in comparison to) shell expansions.
 * @
 * @Currently, libpath_glob allows the following syntax:
 * @*
 * @    Wildcard-- match any character until the right-most character, or the NUL byte
 * @description
 *
 * @example
 * @#include <stdio.h>
 * @#include <errno.h>
 * @#include <stdlib.h>
 * @#include <string.h>
 * @
 * @#include "libpath.h"
 * @
 * @int main(void) {
 * @    int index = 0;
 * @    struct LibpathFiles globbed_files = libpath_glob("./",  "*.*");
 * @
 * @    // Display all globbed files
 * @    for(index = 0; index < globbed_files.length; index++) {
 * @        struct LibpathFile file = globbed_files.contents[index];
 * @
 * @        printf("Globbed file: '%s'\n", file.path);
 * @    }
 * @
 * @    return 0;
 * @}
 * @example
 *
 * @param path: the path to glob in
 * @type: const char *
 *
 * @param pattern: the pattern to glob
 * @type: const char *
 *
 * @return: an array of globbed paths
 * @type: struct LibpathFiles
*/
struct LibpathFiles libpath_glob(const char *path, const char *pattern);

/*
 * @docgen: function
 * @brief: release a glob from memory
 * @name: libpath_glob_free
 *
 * @include: libpath.h
 *
 * @description
 * @Releases an array of globbed files from memory.
 * @description
 *
 * @example
 * @#include <stdio.h>
 * @#include <errno.h>
 * @#include <stdlib.h>
 * @#include <string.h>
 * @
 * @#include "libpath.h"
 * @
 * @int main(void) {
 * @    int index = 0;
 * @    struct LibpathFiles globbed_files = libpath_glob("./",  "*.*");
 * @
 * @    // Display all globbed files
 * @    for(index = 0; index < globbed_files.length; index++) {
 * @        struct LibpathFile file = globbed_files.contents[index];
 * @
 * @        printf("Globbed file: '%s'\n", file.path);
 * @    }
 * @
 * @    libpath_glob_free(globbed_files);
 * @
 * @    return 0;
 * @}
 * @example
 *
 * @param files: the files to release
 * @type: struct LibpathFiles
*/
void libpath_glob_free(struct LibpathFiles files);

/*
 * PATH CREATION API
*/

/*
 * @docgen: structure
 * @brief: a component in a path
 * @name: LibpathPathComponent
 *
 * @field component: the component name
 * @type: const char *
 *
 * @field type: the type of component
 * @type: int
*/
struct LibpathPathComponent {
    const char *component;
    int type;
};

/*
 * @docgen: structure
 * @brief: platform independent path representation
 * @name: LibpathPath
 *
 * @field length: the length of the array
 * @type: int
 *
 * @field capacity: the capacity of the array
 * @type: int
 *
 * @field contents: the components in the array
 * @type: LibpathPathComponent *
*/
struct LibpathPath {
    int length;
    int capacity;
    struct LibpathPathComponent *contents;
};

/*
 * @docgen: function
 * @brief: initialize a new platform independent path
 * @name: libpath_path_init
 *
 * @include: libpath.h
 *
 * @description
 * @This function will initialize a new platform independent path that
 * @will be compiled into the platform's required path.
 * @description
 *
 * @example
 * @#include <stdio.h>
 * @#include <errno.h>
 * @#include <stdlib.h>
 * @#include <string.h>
 * @
 * @#include "libpath.h"
 * @
 * @int main(void) {
 * @    int index = 0;
 * @    struct LibpathPath *path = libpath_path_init();
 * @
 * @    libpath_path_free(path);
 * @
 * @    return 0;
 * @}
 * @example
 *
 * @return: a new path object
 * @type: struct LibpathPath *
*/
struct LibpathPath *libpath_path_init(void);

/*
 * @docgen: function
 * @brief: release a path structure
 * @name: libpath_path_free
 *
 * @include: libpath.h
 *
 * @description
 * @This function will release a path structure from memory
 * @description
 *
 * @example
 * @#include <stdio.h>
 * @#include <errno.h>
 * @#include <stdlib.h>
 * @#include <string.h>
 * @
 * @#include "libpath.h"
 * @
 * @int main(void) {
 * @    int index = 0;
 * @    struct LibpathPath *path = libpath_path_init();
 * @
 * @    libpath_path_free(path);
 * @
 * @    return 0;
 * @}
 * @example
 *
 * @error: path is NULL
 *
 * @return: a new path object
 * @type: struct LibpathPath
*/
void libpath_path_free(struct LibpathPath *path);

/*
 * @docgen: function
 * @brief: add a new component to the path
 * @name: libpath_path_add_component
 *
 * @include: libpath.h
 *
 * @description
 * @description
 *
 * @example
 * @#include "libpath.h"
 * @
 * @int main(void) {
 * @    char compiled_path[LIBPATH_MAX_PATH + 1] = "";
 * @    struct LibpathFiles *files = NULL;
 * @    struct LibpathPath *user_directory = libpath_path_init();
 * @
 * @    // MS-DOS and OS/2 are single-user, so this just expands to C:\
 * @    // On a *NIX, this expands to /home/getenv("USER")
 * @    // On NT, this expands to C:\Users\getenv("USERNAME")
 * @    libpath_path_add_component(user_directory, LIBPATH_HOME, NULL);
 * @
 * @    // Compile the path into this platform's native path
 * @    libpath_path_compile(user_directory, user_directory, LIBPATH_MAX_PATH);
 * @
 * @    // Glob all C source files
 * @    libpath_glob(
 * @
 * @    libpath_path_free(user_directory);
 * @}
 * @example
 *
 * @error: path is NULL
 * @error: name is NULL
 * @error: component is less than zero
 *
 * @param path: the path to add to
 * @type: struct LibpathPath *
 *
 * @param component: what type of path component is this
 * @type: int
 *
 * @param name: the path contents to add ("" if there is none, like root)
 * @type: const char *
*/
void libpath_path_add_component(struct LibpathPath *path, int component, const char *name);

/*
 * @docgen: function
 * @brief: add a new component to the path
 * @name: libpath_path_add_component
 *
 * @include: libpath.h
 *
 * @description
 * @This function will compile the given path into the native path
 * @representation of the current operating system. This is fundamentally
 * @just a front end to the error checking, and compiler backends.
 * @description
 *
 * @notes
 * @If the length of a component will exceed the maximum capacitty of the
 * @buffer when added, the component will not be added and the backend
 * @chosen will return the length of the buffer without the next component.
 * @notes
 *
 * @error: path is NULL
 * @error: buffer is NULL
 * @error: length is negative
 *
 * @param path: the path to compile
 * @type: struct LibpathPath
 *
 * @param buffer: the buffer to write the path into
 * @type: char *
 *
 * @param length: the maximum length of the buffer (without the NUL byte)
 * @type: int
 *
 * @return: the number of bytes written
 * @type: int
*/
int libpath_path_compile(struct LibpathPath *path, char *buffer, int length);









#endif
