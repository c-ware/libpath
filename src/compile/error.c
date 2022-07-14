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
 * This file contains logic for performing error checking on a path before
 * it is compiled. These functions are called by the compile function.
*/

#include <stdio.h>

#include "path.h"
#include "../libpath.h"
#include "../lp_inter.h"

void _libpath_drive_location(struct LibpathPath *path) {
    int index = 0;

    liberror_is_null(_libpath_drive_location, path);

    /* Start at 1, because we do not care if there is a drive
     * at the start or not, all we care about is that it does not
     * appear past the first */
    for(index = 1; index < carray_length(path); index++) {
        if(path->contents[index].type != LIBPATH_COMPONENT_DRIVE)
            continue;

        fprintf(stderr, "_libpath_drive_location: drive component not at index %i, not at 0\n", index);
        exit(EXIT_FAILURE);
    }
}

void _libpath_root_location(struct LibpathPath *path) {
    int index = 0;
    int root_location = -1;

    /* Determine where the root is, if anywhere. */
    for(index = 0; index < carray_length(path); index++) {
        if(path->contents[index].type != LIBPATH_COMPONENT_ROOT)
            continue;

        root_location = index;

        break;
    }

    /* No root here */
    if(root_location == -1)
        return;

    /* Root exists. path->contents[root_location - 1] should either be
     * out of bounds ((root - location) < 0), which implies the path
     * starts with root, or be a drive. For case where the drive is followed
     * by a root component, but both are not at the start, the _libpath_drive_location
     * function will handle this by asserting that the drive must be at the
     * syart if it exists. */

    /* Root is the first component-- move on. */
    if(root_location == 0)
        return;

    /* Root is already after a drive, which is OK and expected. */
    if(path->contents[root_location - 1].type == LIBPATH_COMPONENT_DRIVE)
        return;

    fprintf(stderr, "%s", "_libpath_root_location: root component not at the "
            "start of the path, or does not immediately follow a drive.\n");
    exit(EXIT_FAILURE);
}

void _libpath_root_count(struct LibpathPath *path) {
    int index = 0;
    int count = 0;

    /* Count the number of roots */
    for(index = 0; index < carray_length(path); index++) {
        if(path->contents[index].type != LIBPATH_COMPONENT_ROOT)
            continue;

        count++;
    }

    /* More than 1 count is illegal, but 1 or 0 is OK. */
    if(count <= 1)
        return;

    fprintf(stderr, "%s", "_libpath_root_count: multiple root components "
            " detected in the path\n");
    exit(EXIT_FAILURE);
}

void _libpath_file_location(struct LibpathPath *path) {
    int index = 0;
    int found_file = 0;

    liberror_is_null(_libpath_drive_location, path);

    /* Record whether or not a directory component appears AFTER a
     * file component. */
    for(index = 0; index < carray_length(path); index++) {
        struct LibpathPathComponent component = path->contents[index];

        if(component.type == LIBPATH_COMPONENT_FILE) {
            found_file = 1;

            continue;
        }

        if(component.type != LIBPATH_COMPONENT_DIRECTORY)
            continue;

        /* No file has been found yet, so this directory is does not
         * appear after one. We are OK. */
        if(found_file == 0)
            continue;

        fprintf(stderr, "_libpath_file_location: directory '%s' appears after file\n", component.component);
        exit(EXIT_FAILURE);
    }
}

