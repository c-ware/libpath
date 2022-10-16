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
 * The path object. This contains all the operations on a path object,
 * like initialization, adding components, and freeing.
*/



#include <stdio.h>
#include <assert.h>
#include <string.h>


#if defined(__ULTRIX__) || defined(__QuasiBSD__)
#   if !defined(CWUTILS_GENERIC)
#       define CWUTILS_GENERIC char *
#   endif
#   if !defined(CWUTILS_NULL)
#       define CWUTILS_NULL    ((char *) 0)
#   endif
#else
#   if !defined(CWUTILS_GENERIC)
#      define CWUTILS_GENERIC void *
#   endif
#   if !defined(CWUTILS_NULL)
#      define CWUTILS_NULL    ((void *) 0)
#   endif
#endif





































#define LIBPATH_INTERNAL

#include "libpath.h"
#include "path.h"

struct LibpathPath *libpath_path_init() {
    struct LibpathPath *new_path = (struct LibpathPath *) CWUTILS_NULL;

    
    CWUTILS_NULL;

	(new_path) = (struct LibpathPath *) malloc(sizeof(*(new_path)));
	(new_path)->used = 0;
	(new_path)->length = 0;

    LIBERROR_IS_NULL((new_path), "(new_path)");
    LIBERROR_IS_NEGATIVE((new_path)->used, "(new_path)->used");
    LIBERROR_IS_NEGATIVE((new_path)->length, "(new_path)->length");

	(new_path)->capacity = 3;
	(new_path)->contents = (struct LibpathPathComponent *) malloc(sizeof(struct LibpathPathComponent) * 3);

    
    LIBERROR_IS_NULL((new_path), "(new_path)");
    LIBERROR_IS_NULL((new_path)->contents, "(new_path)->contents");
    LIBERROR_IS_NEGATIVE((new_path)->used, "(new_path)->used");
    LIBERROR_IS_NEGATIVE((new_path)->length, "(new_path)->length");
    LIBERROR_IS_NEGATIVE((new_path)->capacity, "(new_path)->capacity")

;

    return new_path;
}
