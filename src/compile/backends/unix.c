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
 * The backend for producing UNIX paths.
 *
 * So to note, UNIX's path structure has NO concept of a 'drive' unlike
 * MS-DOS, OS/2, Windows, and VMS. Because of this, these components are
 * quite literally ignored.
 *
 * UNIX paths are probably the simplest of all of them, as on their own they
 * are fairly barebones. This allows us to do what is essentially a blind
 * pass translation without having to check what the next or previous component
 * in the list is. Mostly, at least.
*/

#include <stdio.h>
#include <string.h>

#include "../path.h"
#include "../../libpath.h"
#include "../../lp_inter.h"

int _libpath_path_backend_unix(struct LibpathPath *path, char *buffer, int length) {
    int index = 0;
    int written = 0;

    liberror_is_null(_libpath_path_backend_unix, path);
    liberror_is_null(_libpath_path_backend_unix, buffer);
    liberror_is_negative(_libpath_path_backend_unix, length);

    LIBPATH_ERROR_CHECK(path);

    /* Reset the buffer so strncat does not try adding onto the end
     * of a potentially old or an uninitialized buffer (grumble grumble). */
    buffer[0] = '\0';

    for(index = 0; index < carray_length(path); index++) {
        int component_length = 0;
        struct LibpathPathComponent component = path->contents[index];

        /* Remember: UNIX paths have no clue what a 'drive' is! Drives are
         * mounted in-tree. */
        if(component.type == LIBPATH_COMPONENT_DRIVE)
            continue;

        /* Determine the length of the component and make sure the path
         * will not go out of bounds with it added..
         *
         * Remember, length in this context does not include the NUL byte.
         * We should also remember that the + 1 for directories is for that
         * path separator, which is only added if we are not at the end of
         * the path. */
        switch(component.type) {
            case LIBPATH_COMPONENT_ROOT:
                component_length = 1; break;

            case LIBPATH_COMPONENT_DIRECTORY:
                component_length = strlen(component.component);

                /* Make sure to include a '/' in the final path
                 * if we are not at the end of the path! */
                if((index + 1) == carray_length(path))
                    component_length += 1;

                break;

            case LIBPATH_COMPONENT_FILE:
                component_length = strlen(component.component);
                break;
        }

        if((written + component_length) > length)
            return written;

        /* Determine what to write!! */
        switch(component.type) {
            case LIBPATH_COMPONENT_ROOT:
                strncat(buffer, "/", length - written);

                written += 1;

                break;

            case LIBPATH_COMPONENT_DIRECTORY:
                strncat(buffer, component.component, length - written);

                /* Make sure to include a '/' in the final path
                 * if we are not at the end of the path! */
                if((index + 1) < carray_length(path)) {
                    strncat(buffer, "/", length - written - 1);

                    written += 1;
                }


                written += component_length;

                break;

            case LIBPATH_COMPONENT_FILE:
                strncat(buffer, component.component, length - written);

                written += component_length;

                break;
        }
    }

    buffer[written] = '\0';

    return written;
}
