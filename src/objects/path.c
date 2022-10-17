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





































#define LIBPATH_INTERNAL

#include "compat.h"
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

    LIBERROR_MALLOC_FAILURE(new_path, "new_path");

    return new_path;
}

#if defined(CWUTILS_ANCIENT)
void libpath_path_free(path)
    struct LibpathPath *path; {
#else
void libpath_path_free(struct LibpathPath *path) {
#endif
    LIBPATH_PATH_VALIDATE(path);

    
    
    LIBERROR_IS_NULL((path), "(path)");
    LIBERROR_IS_NULL((path)->contents, "(path)->contents");
    LIBERROR_IS_NEGATIVE((path)->used, "(path)->used");
    LIBERROR_IS_NEGATIVE((path)->length, "(path)->length");
    LIBERROR_IS_NEGATIVE((path)->capacity, "(path)->capacity")
;

	do {
		int __M4_INDEX = 0;

		while(__M4_INDEX < (path)->length) {
            LIBERROR_IS_OOB(__M4_INDEX, (path)->length);
			;
			__M4_INDEX++;
		}

		free((path)->contents);
		free((path));
	} while(0)
;
}
