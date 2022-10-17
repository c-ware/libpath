/*
 * C-Ware License
 * 
 * Copyright (c) 2022, C-Ware
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
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
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/



#include <stdio.h>
#include <assert.h>
#include <string.h>































#ifndef CWARE_LIBPATH_OBJECT_PATH
#define CWARE_LIBPATH_OBJECT_PATH

#include "compat.h"


    struct LibpathPath {
        int used;
        int length;
        int capacity;

        struct LibpathPathComponent *contents;
    }
;

#define LIBPATH_PATH_VALIDATE(item)                         \
    LIBERROR_IS_NULL(item, "value");                        \
    LIBERROR_IS_NEGATIVE(item->used, "value->used");        \
    LIBERROR_IS_NULL(item->contents, "value->contents");    \
    LIBERROR_IS_NEGATIVE(item->length, "value->length");    \
    LIBERROR_IS_NEGATIVE(item->capacity, "value->capacity")

/*
 * @docgen_start
 * @type: function
 * @name: libpath_path_init
 * @brief: initialize a new path array
 *
 * @include: libpath.h
 *
 * @description
 * @Initializes a new path array, which will be used to compile a system
 * @dependent path.
 * @description
 *
 * @return_value
 * @An array of path components
 * @return_value
 *
 * @type: struct LibpathPath
 *
 * @reference: libpath(cware)
 * @reference: cware(cware)
 * 
 * @docgen_end
*/
struct LibpathPath *libpath_path_init();

/*
 * @docgen_start
 * @type: function
 * @name: libpath_path_free
 * @brief: release a path array
 *
 * @include: libpath.h
 *
 * @description
 * @Releases a path array from memory.
 * @description
 *
 * @fparam: path
 * @type: struct LibpathPath *
 * @brief: the path to release from memory
 *
 * @reference: libpath(cware)
 * @reference: cware(cware)
 *
 * @docgen_end
*/
#if defined(CWUTILS_ANCIENT)
void libpath_path_free();
#else
void libpath_path_free(struct LibpathPath *path);
#endif

#endif
