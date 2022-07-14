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
 * API for portable path construction. The way that libpath handles the
 * construction of paths in a portable way is by using a sort of format
 * independent version of the paths, where the programmer gives a tag that
 * describes what the component is. The component is then compiled into
 * the platform's path format.
 *
 * This is a critical part of libpath, as it allows us to more easily
 * future-proof the library for operating systems which have esoteric path
 * formats, and or features of their paths that another does not. For example,
 * a Windows path CAN have a drive in it, while on a UNIX system, drivers are
 * not baked into paths themselves. They are just mounted under an arbitrary
 * directory.
*/

#include "path.h"
#include "../libpath.h"
#include "../lp_inter.h"

struct LibpathPath *libpath_path_init(void) {
    struct LibpathPath *new_path = carray_init(new_path, PATH_COMPONENT);

    return new_path;
}

void libpath_path_free(struct LibpathPath *path) {
    carray_free(path, PATH_COMPONENT);
}

void libpath_path_add_component(struct LibpathPath *path, int component, const char *name) {
    struct LibpathPathComponent new_component;

    liberror_is_null(libpath_path_add_component, path);
    liberror_is_null(libpath_path_add_component, name);
    liberror_is_negative(libpath_path_add_component, component);

    INIT_VARIABLE(new_component);
    new_component.type = component;
    new_component.component = name;

    carray_append(path, new_component, PATH_COMPONENT);
}

int libpath_path_compile(struct LibpathPath *path, char *buffer, int length) {
    int written = 0;

    /* Error checking on this path. To anyone modifying
     * this segment of the code, please remember that the
     * order that these functions are called in DOES matter.
     * Some error checking will rely on previous error
     * checking to have been done. */
    _libpath_drive_location(path);
    _libpath_file_location(path);
    _libpath_root_location(path);
    _libpath_root_count(path);

    written = _libpath_path_backend_unix(path, buffer, length);

    return written;
}
