dnl C-Ware License
dnl 
dnl Copyright (c) 2022, C-Ware
dnl All rights reserved.
dnl 
dnl Redistribution and use in source and binary forms, with or without
dnl modification, are permitted provided that the following conditions are met:
dnl 
dnl 1. Redistributions of source code must retain the above copyright notice, this
dnl    list of conditions and the following disclaimer.
dnl 
dnl 2. Redistributions in binary form must reproduce the above copyright notice,
dnl    this list of conditions and the following disclaimer in the documentation
dnl    and/or other materials provided with the distribution.
dnl 
dnl 3. Redistributions of modified source code must append a copyright notice in
dnl    the form of 'Copyright <YEAR> <NAME>' to each modified source file's
dnl    copyright notice, and the standalone license file if one exists.
dnl 
dnl A "redistribution" can be constituted as any version of the source code
dnl that is intended to comprise some other derivative work of this code. A
dnl fork created for the purpose of contributing to any version of the source
dnl does not constitute a truly "derivative work" and does not require listing.
dnl 
dnl THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
dnl AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
dnl IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
dnl DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
dnl FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
dnl DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
dnl SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
dnl CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
dnl OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
dnl OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

dnl @docgen_start
dnl @type: project
dnl @name: m4array
dnl @brief: an implementation of a dynamic array in m4
dnl
dnl @include: m4array/m4array.m4
dnl
dnl @embed: M4ARRAY_FREE
dnl @show_brief: 0
dnl @embed: M4ARRAY_FIND
dnl @show_brief: 0
dnl @embed: M4ARRAY_POP
dnl @show_brief: 0
dnl @embed: M4ARRAY_INSERT
dnl @show_brief: 0
dnl @embed: M4ARRAY_APPEND
dnl @show_brief: 0
dnl @embed: M4ARRAY_INIT
dnl @show_brief: 0
dnl @embed: M4ARRAY_FOREACH
dnl @show_brief: 0
dnl @embed: M4ARRAY_MAP
dnl @show_brief: 0
dnl @embed: M4ARRAY_CLEAR
dnl @show_brief: 0
dnl @embed: M4ARRAY_FILTER
dnl @show_brief: 0
dnl @embed: @name: M4ARRAY_DECLARE
dnl @show_brief: 0
dnl
dnl @description
dnl @An implementation of a dynamic array in \Bm4\B(1). It is type safe, and provides
dnl @all of the basic necessities when it comes to a dynamic array, including insertion,
dnl @appending, searching, and more. This implmenetation is highly portable. It will compile
dnl @on each of the following operating systems without error (assuming code is preprocessed
dnl @with m4):
dnl @   - FreeBSD 13.1
dnl @   - NetBSD 9.3
dnl @   - OpenBSD 7.1
dnl @   - OpenSolaris 10
dnl @   - ULTRIX 4.5
dnl @   - QuasijarusBSD 4.3
dnl @   - OS/2 4.52 Warp
dnl @   - DragonflyBSD 6.2.1
dnl @   - NeXTSTEP 4.2
dnl @   - UNIXWare 7.1.4
dnl @
dnl @As stated above, it is recommended that you preprocess your \Bm4\B(1) into C files before shipping
dnl @the code. This makes your code much portable as not all systems have \Bm4\B(1). For a larger
dnl @introduction into how m4array works, and how to use it, please see \Bm4array-intro\B(cware).
dnl @
dnl @\T
dnl @\S ;
dnl @\H Manual;Description
dnl @\E M4ARRAY_INIT(cware);initialize a new array
dnl @\E M4ARRAY_APPEND(cware);append a value
dnl @\E M4ARRAY_INSERT(cware);insert a value at a specific index
dnl @\E M4ARRAY_POP(cware);pop a value out of an index
dnl @\E M4ARRAY_FIND(cware);find a value that matches a  predicate
dnl @\E M4ARRAY_FOREACH(cware);run an operaton for each element
dnl @\E M4ARRAY_MAP(cware);apply an operation in place
dnl @\E M4ARRAY_CLEAR(cware);free each element and set the length to 0
dnl @\E M4ARRAY_FILTER(cware);filter based off a predictate
dnl @\E M4ARRAY_DECLARE(cware);declare a new array structure
dnl @\T
dnl @description
dnl
dnl @examples
dnl @This is a table of documentation which holds example code, along with a
dnl @brief description of it, and the macros it involves.
dnl @
dnl @\T
dnl @\S ;
dnl @\H Manual;Description;Macros
dnl @\E m4array-examples-join(cware);joining strings;init,foreach,append,free
dnl @\T
dnl @examples
dnl
dnl @reference: m4array-intro(cware)
dnl
dnl @docgen_end

#include <stdio.h>
#include <assert.h>
#include <string.h>

dnl ==========================
dnl	# M4array utility macros #
dnl ==========================

dnl Verify that an array object is not in an
dnl invalid state.
define(`M4ARRAY_VERIFY', `
    LIBERROR_IS_NULL(($1), "($1)");
    LIBERROR_IS_NULL(($1)->contents, "($1)->contents");
    LIBERROR_IS_NEGATIVE(($1)->used, "($1)->used");
    LIBERROR_IS_NEGATIVE(($1)->length, "($1)->length");
    LIBERROR_IS_NEGATIVE(($1)->capacity, "($1)->capacity")
')

define(`M4ARRAY_INITIAL_LENGTH', `3')
define(`M4ARRAY_NEXT_SIZE', `(($1)->capacity * 2)')
define(`__M4ARRAY_RESIZE', `
M4ARRAY_VERIFY($1);

do {
	if((($1)->length == ($1)->capacity) && (($1)->used == ($1)->length)) {
		($1)->contents = ($2_TYPE *) realloc(($1)->contents, sizeof($2_TYPE) * M4ARRAY_NEXT_SIZE($1));
		($1)->capacity = M4ARRAY_NEXT_SIZE($1);

        LIBERROR_IS_NEGATIVE(($1)->capacity, "($1)->capacity");
        LIBERROR_MALLOC_FAILURE(($1)->contents, "($1)->contents");
	}
} while(0)
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4ARRAY_DECLARE
dnl @brief: declare a new array structure
dnl
dnl @include: m4array/m4array.m4
dnl 
dnl @description
dnl @This will declare a new array structure of a certain name.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4array\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: the name of the structure
dnl
dnl @param: 2
dnl @brief: the type of the array
dnl
dnl @reference: m4array(cware)
dnl
dnl @docgen_end
define(`M4ARRAY_DECLARE', `
    struct $1 {
        int used;
        int length;
        int capacity;

        $2 *contents;
    }
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4ARRAY_INIT
dnl @brief: initialize a new array
dnl
dnl @include: m4array/m4array.m4
dnl 
dnl @description
dnl @This will initialize a new array on the heap. The initial length will be judged
dnl @by M4ARRAY_INITIAL_LENGTH, and must be released from memory using \BM4ARRAY_FREE\B(cware)
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4array\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the array to initialize
dnl
dnl @param: 2
dnl @brief: namespace of the array
dnl
dnl @reference: m4array(cware)
dnl
dnl @docgen_end
define(`M4ARRAY_INIT', `
    CWUTILS_NULL;

	($1) = ($2_NAME *) malloc(sizeof(*($1)));
	($1)->used = 0;
	($1)->length = 0;

    LIBERROR_IS_NULL(($1), "($1)");
    LIBERROR_IS_NEGATIVE(($1)->used, "($1)->used");
    LIBERROR_IS_NEGATIVE(($1)->length, "($1)->length");

	($1)->capacity = M4ARRAY_INITIAL_LENGTH;
	($1)->contents = ($2_TYPE *) malloc(sizeof($2_TYPE) * M4ARRAY_INITIAL_LENGTH);

    M4ARRAY_VERIFY($1)
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4ARRAY_APPEND
dnl @brief: append to an array
dnl
dnl @include: m4array/m4array.m4
dnl
dnl @description
dnl @This macro will append a value to an array given, and resize the
dnl @array if needed using the M4ARRAY_NEXT_SIZE(cware) macro. If the
dnl @array namespace has memory reuse enabled, the unused slots in the
dnl @array, if there are any, will be used rather than extending the
dnl @array itself.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4array\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the array to append to
dnl
dnl @param: 2
dnl @brief: the value to append
dnl
dnl @param: 3
dnl @brief: the namespace of the array
dnl
dnl @reference: m4array(cware)
dnl
dnl @docgen_end
define(`M4ARRAY_APPEND', `
    __M4ARRAY_RESIZE($1, $3);

    M4ARRAY_VERIFY($1);

    /* If used < length, that means we have data in the array that
       is currently unused, but initialized. We can reuse it. Otherwise,
       we can just append like normal. */
    if(($1)->used < ($1)->length) {
        ifdef(`$3_REUSE', `$3_REUSE(($1)->contents[($1)->used], ($2));')
    } else {
	    ($1)->contents[($1)->length] = ($2);
	    ($1)->length++;
    }

    ($1)->used++;
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4ARRAY_INSERT
dnl @brief: insert a value into an array at an index
dnl
dnl @include: m4array/m4array.m4
dnl
dnl @description
dnl @This macro will take a value, and insert it into an array at a given
dnl @index. Everything after the index that is inserted into will be shifted
dnl @over by one slot to make room for the new element. If the array namespace
dnl @has memory reuse, then any unused slots will be used before extending the
dnl @array.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4array\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the array to insert into
dnl
dnl @param: 2
dnl @brief: the value to insert
dnl
dnl @param: 3
dnl @brief: the location to insert into
dnl
dnl @param: 4
dnl @brief: the namespace of the array
dnl
dnl @reference: m4array(cware)
dnl 
dnl @docgen_end
define(`M4ARRAY_INSERT', `
    __M4ARRAY_RESIZE($1, $4);

    M4ARRAY_VERIFY($1);

	do {
		int __M4_INDEX = ($1)->used - 1;
        $4_TYPE __M4_TEMP = ($1)->contents[($1)->used];

		/* Shift each element before ($3 - 1) over by 1. This WILL overwrite
           the first allocated, but unused slot in the array, but this is not
           an issue because in the case where we do care about memory reuse,
           we save the first reusable slot anyway. */
		while(__M4_INDEX != ($3) - 1) {
			($1)->contents[__M4_INDEX + 1] = ($1)->contents[__M4_INDEX];
			__M4_INDEX--;
		}

        if(($1)->used < ($1)->length) {
            ifdef(`$4_REUSE', `$4_REUSE(__M4_TEMP, $2);')

            /* We do not increase the length of the array because we do
               not actually increase the length of initialized data. */
		    ($1)->contents[$3] = __M4_TEMP;
		    ($1)->used++;
        } else {
		    ($1)->contents[$3] = $2;
		    ($1)->length++;
		    ($1)->used++;
        }
	} while(0)
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4ARRAY_POP
dnl @brief: pop a value out of an array at some index
dnl
dnl @include: m4array/m4array.m4
dnl
dnl @description
dnl @This macro will pop a value out of an index in the array, and write it to a
dnl @variable. Each value in the array after the index that is popped will be
dnl @shifted over by one slot. Unlike many of the other operations, this operation
dnl @will not make the popped index a reusable buffer, as the value inside of it
dnl @will be written to the variable-- thus it is unreusable.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4array\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the array to pop out of
dnl
dnl @param: 2
dnl @brief: the index to pop out
dnl
dnl @param: 3
dnl @brief: the variable to put the value in
dnl
dnl @param: 4
dnl @brief: the namespace of the array
dnl
dnl @reference: m4array(cware)
dnl
dnl @docgen_end
define(`M4ARRAY_POP', `
    M4ARRAY_VERIFY($1);

	($3) = ($1)->contents[$2];

	do {
		int __M4_INDEX = $2;

		($1)->used--;
		($1)->length--;

		/* Pull everything from index ($2), onwards, back by 1. This
           must also pull back any allocated, but unused sections of
           the array, too. */
		while(__M4_INDEX < ($1)->length) {
			($1)->contents[__M4_INDEX] = ($1)->contents[__M4_INDEX + 1];
			__M4_INDEX++;
		}
	} while(0)
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4ARRAY_FIND
dnl @brief: find the first occurrence of a value
dnl
dnl @include: m4array/m4array.m4
dnl
dnl @description
dnl @This macro will find the first occurrence of a value that matches
dnl @a predicate. The predicate must be an expression that evaluates to
dnl @either 1, or 0. If the value is never found, -1 is written to the
dnl @output variable. Otherwise, the index is written to it.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4array\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the array to search
dnl
dnl @param: 2
dnl @brief: the variable to put the index into
dnl
dnl @param: 3
dnl @brief: the macro body to execute
dnl
dnl @reference: m4array(cware)
dnl
dnl @docgen_end
define(`M4ARRAY_FIND', `
    M4ARRAY_VERIFY($1);

	($2) = -1;

	define(`M4ARRAY_LAMBDA', `$3')

	do {
		int __M4_INDEX = 0;

		while(__M4_INDEX < ($1)->used) {
            LIBERROR_IS_OOB(__M4_INDEX, ($1)->length);

			if((M4ARRAY_LAMBDA(($1)->contents[__M4_INDEX])) == 0) {
				__M4_INDEX++;
				continue;
			}

			($2) = __M4_INDEX;
			break;
		}
	} while(0)
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4ARRAY_MAP
dnl @brief: apply an operation to each element of an array
dnl
dnl @include: m4array/m4array.m4
dnl
dnl @description
dnl @This macro will apply an operation on each member of an array. The macro
dnl @is in-place, and will a[i] with the output of f(x), where a[i] is any
dnl @given array element, and f(x) is a macro which uses a[i].
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4array\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the array to map to
dnl
dnl @param: 2
dnl @brief: the macro body to execute
dnl
dnl @reference: m4array(cware)
dnl
dnl @docgen_end
define(`M4ARRAY_MAP', `
	define(`M4ARRAY_LAMBDA', `$2')
    M4ARRAY_VERIFY($1);

	do {
		int __M4_INDEX = 0;

		while(__M4_INDEX < ($1)->used) {
            LIBERROR_IS_OOB(__M4_INDEX, ($1)->length);
			($1)->contents[__M4_INDEX] = (M4ARRAY_LAMBDA(($1)->contents[__M4_INDEX]));
            __M4_INDEX++;
		}
	} while(0)
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4ARRAY_FILTER
dnl @brief: filter all elements which do not match a predicate
dnl
dnl @include: m4array/m4array.m4
dnl
dnl @description
dnl @This macro will evaluate a predicate for each element in the array, and
dnl @if that element does not match the predicate, it will be removed from
dnl @the array. Each value that does not pass the filter will be released
dnl @from memory unless the array namespace has memory reuse, in which case,
dnl @those values will be made reusable.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4array\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the array to filter to
dnl
dnl @param: 2
dnl @brief: the namespace of the array
dnl
dnl @param: 3
dnl @brief: the macro body to execute
dnl
dnl @reference: m4array(cware)
dnl
dnl @docgen_end
dnl
dnl The filter operation follows this general algorithom to allow for
dnl memory reuse.
dnl
dnl Let A be the array
dnl Let L be the number of elements that passed the predicate
dnl Let I be the index of an element in the array
dnl Let len(A) be the length of the array
dnl
dnl For each element A[I], if A[I] matches the predicate, store A[L]
dnl in a temporary variable X, and assign A[L] to A[I]. Finally, assign
dnl X to A[I]. For each element A[I] that matches the predicate, increment
dnl L.
dnl
dnl Once this has been completed, we now have a "sorted" array of elements
dnl that passed the filter, and elements that did not. If we are planning to
dnl reuse memory, we can keep it like this. However, if we are not, we should
dnl release each element that did not pass the filter from memory. Each element
dnl that passed the filter will be in the range [0, L), and each element that
dnl did not pass the filter will be from range [L, len(A))
define(`M4ARRAY_FILTER', `
	define(`M4ARRAY_LAMBDA', `$3')
    M4ARRAY_VERIFY($1);

	do {
		int __M4_INDEX = 0;
        int __M4_CURSOR = 0;

		while(__M4_INDEX < ($1)->used) {
            LIBERROR_IS_OOB(__M4_INDEX, ($1)->length);
            LIBERROR_IS_OOB(__M4_CURSOR, ($1)->length);

            /* A[I] matches the predicate-- swap A[I] and A[L]*/
            if((M4ARRAY_LAMBDA(($1)->contents[__M4_INDEX])) == 1) {
                $2_TYPE __M4_TEMP = ($1)->contents[__M4_CURSOR];

                ($1)->contents[__M4_CURSOR] = ($1)->contents[__M4_INDEX];
                ($1)->contents[__M4_INDEX] = __M4_TEMP;
                __M4_CURSOR++;
            }

            __M4_INDEX++;
		}

        /* If we are reusing memory, then we should leave the length alone.
           Otherwise, length should stay the same as the used count. Normally,
           at first thought, we should do x = (y + 1), but we do not have to,
           since y will be equal to the length of the array. */
        ifdef(`$2_REUSE', `($1)->used = __M4_CURSOR;')

        /* If we do not enforce memory reuse, everything after __M4_CURSOR
           must be freed, since it will not be reusable. Once this is done,
           we can set the length __M4_CURSOR */
        ifdef(`$2_REUSE', `', `
            __M4_INDEX = __M4_CURSOR;

            while(__M4_INDEX < ($1)->length) {
                LIBERROR_IS_OOB(__M4_INDEX, ($1)->length);

                $2_FREE(($1)->contents[__M4_INDEX]);
                __M4_INDEX++;
            }

            LIBERROR_IS_OOB(__M4_CURSOR, ($1)->length);

            ($1)->length = __M4_CURSOR;
            ($1)->used = __M4_CURSOR;
        ') 
	} while(0)
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4ARRAY_CLEAR
dnl @brief: release the contents of an array, without freeing the array
dnl
dnl @include: m4array/m4array.m4
dnl
dnl @description
dnl @This macro will "clear" the array by freeing each element of the array,
dnl @and setting the length of the array to zero. The individual elements of
dnl @the array will not be freed if memory reuse is enabled-- rather, they will
dnl @just be set to reusable.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4array\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the array to clear
dnl
dnl @param: 2
dnl @brief: the namespace of the array
dnl
dnl @reference: m4array(cware)
dnl
dnl @docgen_end
define(`M4ARRAY_CLEAR', `
    M4ARRAY_VERIFY($1);

	do {
        /* We only need to release the contents of the array if
           we do not want to reuse memory. If we do want to reuse
           memory, all we need to do is set the used length to zero
           to signal to adding functions that there is allocated,
           but unused slots in the array. */
        ifdef(`$2_REUSE', `', `
		    int __M4_INDEX = 0;

		    while(__M4_INDEX < ($1)->used) {
                LIBERROR_IS_OOB(__M4_INDEX, ($1)->used);

		    	$2_FREE(($1)->contents[__M4_INDEX]);
                __M4_INDEX++;
		    }
            
            ($1)->length = 0;
        ')

        /* Regardless of whether or not we reuse memory, this
           can be reset to zero. */
        ($1)->used = 0;

	} while(0)
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4ARRAY_FOREACH
dnl @brief: run code for each element in an array
dnl
dnl @include: m4array/m4array.m4
dnl
dnl @description
dnl @This macro will run an operation for each element in an array. The
dnl @operation will have the element of the array passed as the first
dnl @argument.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4array\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the array to loop over
dnl
dnl @param: 2
dnl @brief: the macro to execute for each element
dnl
dnl @reference: m4array(cware)
dnl 
dnl @docgen_end
define(`M4ARRAY_FOREACH', `
	define(`M4ARRAY_LAMBDA', `$2')
    M4ARRAY_VERIFY($1);

    do {
        int __M4_INDEX = 0;

        while(__M4_INDEX < ($1)->used) {
            LIBERROR_IS_OOB(__M4_INDEX, ($1)->length);
            M4ARRAY_LAMBDA(($1)->contents[__M4_INDEX]);

            __M4_INDEX++;
        }
    } while(0)
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4ARRAY_FREE
dnl @brief: release an array and its contents from memory
dnl 
dnl @include: m4array/m4array.m4
dnl
dnl @description
dnl @This macro will apply a free-macro for each element of the array, and 
dnl @release the array itself. The macro that will be called has the suffix
dnl @_FREE.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4array\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the array to release
dnl
dnl @param: 2
dnl @brief: the namespace of the array
dnl
dnl @reference: m4array(cware)
dnl
dnl @docgen_end
define(`M4ARRAY_FREE', `
    M4ARRAY_VERIFY($1);

	do {
		int __M4_INDEX = 0;

		while(__M4_INDEX < ($1)->length) {
            LIBERROR_IS_OOB(__M4_INDEX, ($1)->length);
			$2_FREE(($1)->contents[__M4_INDEX]);
			__M4_INDEX++;
		}

		free(($1)->contents);
		free(($1));
	} while(0)
')
