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

#ifndef CWARE_LIBPATH_PATH_H
#define CWARE_LIBPATH_PATH_H

/*
 * @docgen: macro_function
 * @brief: perform all error checks on a path
 * 
 * @include: libpath.h
 *
 * @description
 * @This macro function is fairly simple. All it does is run all of the 
 * @error checking functions on a path. Useful when you are directly
 * @invoking the backends for path compilation, so you can still do runtime
 * @error checking.
 * @description
 * 
 * @param path: the path to perform error checks on
*/
#define LIBPATH_ERROR_CHECK(path)   \
    _libpath_drive_location(path);  \
    _libpath_file_location(path);   \
    _libpath_root_location(path);   \
    _libpath_root_count(path);

struct LibpathPath;

int _libpath_path_backend_unix(struct LibpathPath *path, char *buffer, int length);

/* Error checking operations */

/*
 * @docgen: function
 * @brief: assert that the location of the drive is at the start
 * @name: _libpath_drive_location
 *
 * @description
 * @This function will take a path that, if it contains a drive at any
 * @location other than the start, will produce an error. This function
 * @also doubles as verifying that there are not more than one drive in a
 * @path.
 * @description
 *
 * @error: path is NULL
 * @error: a drive is found that is not at the start
 *
 * @param path: the path to check
 * @type: struct LibpathPath
*/
void _libpath_drive_location(struct LibpathPath *path);

/*
 * @docgen: function
 * @brief: assert that the root is at the start, or followed by a drive
 * @name: _libpath_root_location
 *
 * @description
 * @This function will take a path that, if it contains a root at any
 * @point in its contents, will assert that the root is either at the
 * @start of the path, or is immediately before a drive.
 * @description
 *
 * @notes
 * @This function relies on the assertion of the drive's location by the
 * @_libpath_drive_location(cware) function, so it must be called before it.
 * @notes
 *
 * @error: path is NULL
 * @error: root is not at the start, or not preceeded by a drive.
 *
 * @param path: the path to check
 * @type: struct LibpathPath
*/
void _libpath_root_location(struct LibpathPath *path);

/*
 * @docgen: function
 * @brief: assert that there is only 1, or 0 roots
 * @name:_libpath_root_count
 *
 * @description
 * @This function will take a path, and assert that its contents contains a
 * @maximum of a single root component.
 * @description
 *
 * @error: path is NULL
 * @error: there is more than one root in a path
 *
 * @param path: the path to check
 * @type: struct LibpathPath
*/
void _libpath_root_count(struct LibpathPath *path);

/*
 * @docgen: function
 * @brief: assert that the location of a file is appropriate
 * @name: _libpath_file_location
 *
 * @description
 * @This function will take a path that, and verify that if it has a file,
 * @the file in the path is in an appropriate location in the path. An
 * @appropriate location would be anywhere after the last directory if there
 * @is a directory found.
 * @description
 *
 * @notes
 * @This function relies on the prior execution of _libpath_drive_location(cware),
 * @as if a file appears before the location of a directory (if one exists in
 * @the path), then it will be caught in that function.
 * @notes
 *
 * @error: path is NULL
 * @error: a file is found in an inappropriate location
 *
 * @param path: the path to check
 * @type: struct LibpathPath
*/
void _libpath_file_location(struct LibpathPath *path);

#endif
