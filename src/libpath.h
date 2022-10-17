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

/* 
 * The header for libpath. To access internal header declarations, define the
 * LIBPATH_INTERNAL macro before including this header.
*/



#include <stdio.h>
#include <assert.h>
#include <string.h>































#ifndef CWARE_LIBPATH_H
#define CWARE_LIBPATH_H

/* Library components */
#include "path.h"

/* Internal headers and declarations */
#if defined(LIBPATH_INTERNAL)

/* System headers */
#include <stdio.h>

#if !defined(__QuasiBSD__)
#   include <stdlib.h>
#endif

/* Global dependencies */
#include "liberror.h"

/*
 * @docgen_start
 * @type: structure
 * @name: LibpathPathComponent
 * @brief: a component in a path that should be compiled
 *
 * @embed: LibpathPathComponent
 * @show_brief: 1
 *
 * @field: type
 * @type: int
 * @brief: the type of component (drive, extension, directory, ...)
 *
 * @field: text
 * @type: const char *
 * @brief: the textual component of the path (e.g directory name)
 * 
 * @docgen_end
*/
struct LibpathPathComponent {
    int type;
    CWUTILS_CONST char *text;   
};

#endif

#endif
