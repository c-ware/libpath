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
 * A small collection of macros for performing tests in a convenient, and
 * K&R-friendly format.
*/

#if !defined(LIBASSERT_ERROR_STREAM)
#define LIBASSERT_ERROR_STREAM stderr
#endif

/*
 * ===============================
 * # String assertion operations #
 * ===============================
*/

#define ASSERT_STREQ(x, y)                                                                                                                 \
do {                                                                                                                                       \
    if(strcmp(x, y) != 0) {                                                                                                                \
        fprintf(LIBASSERT_ERROR_STREAM, "assertion failed; strings '%s' and '%s' are not equal! (%s:%i)\n", (x), (y), __FILE__, __LINE__); \
        abort();                                                                                                                           \
    }                                                                                                                                      \
} while(0)

#define ASSERT_STRNEQ(x, y)                                                                                                            \
do {                                                                                                                                   \
    if(strcmp(x, y) == 0) {                                                                                                            \
        fprintf(LIBASSERT_ERROR_STREAM, "assertion failed; strings '%s' and '%s' are equal! (%s:%i)\n", (x), (y), __FILE__, __LINE__); \
        abort();                                                                                                                       \
    }                                                                                                                                  \
} while(0)

/*
 * ================================
 * # Pointer assertion operations #
 * ================================
*/

#define ASSERT_PTREQ(x, y)                                                                                                                                                  \
do {                                                                                                                                                                        \
    if(((char *) x) != ((char *) y)) {                                                                                                                                      \
        fprintf(LIBASSERT_ERROR_STREAM, "assertion failed; pointers %p and %p are not equal! (%s:%i)\n", (CWUTILS_GENERIC) (x), (CWUTILS_GENERIC) (y), __FILE__, __LINE__); \
        abort();                                                                                                                                                            \
    }                                                                                                                                                                       \
} while(0)

#define ASSERT_PTRNEQ(x, y)                                                                                                                                             \
do {                                                                                                                                                                    \
    if(((char *) x) == ((char *) y)) {                                                                                                                                  \
        fprintf(LIBASSERT_ERROR_STREAM, "assertion failed; pointers %p and %p are equal! (%s:%i)\n", (CWUTILS_GENERIC) (x), (CWUTILS_GENERIC) (y), __FILE__, __LINE__); \
        abort();                                                                                                                                                        \
    }                                                                                                                                                                   \
} while(0)

/*
 * ===============================
 * # Number assertion operations #
 * ===============================
*/

#define ASSERT_NUMEQ(x, y)                                                                                               \
do {                                                                                                                     \
    if((x) != (y)) {                                                                                                     \
        fprintf(LIBASSERT_ERROR_STREAM, "assertion failed; input numbers are not equal! (%s:%i)\n", __FILE__, __LINE__); \
        abort();                                                                                                         \
    }                                                                                                                    \
} while(0)

#define ASSERT_NUMNEQ(x, y)                                                                                          \
do {                                                                                                                 \
    if((x) == (y)) {                                                                                                 \
        fprintf(LIBASSERT_ERROR_STREAM, "assertion failed; input numbers are equal! (%s:%i)\n", __FILE__, __LINE__); \
        abort();                                                                                                     \
    }                                                                                                                \
} while(0)
