## Macros used in the documentation generation.

define(`LIBPATH_HEADER', `
.TH "CWARE_MANUAL_NAME" "cware" "March 28th, 2022" "" \
    "C-Ware Manual"
')

## $1: the name of the macro
define(`LIBPATH_EXAMPLE_COMMENT', `
/*
 * This example showcases how to use the
.B $1
function.
.br
*/
')

## Dump the inclusions used by the library
define(`LIBPATH_INCLUSIONS', `
.B #include <stdlib.h>
.br
.B #include <cware/libpath/libpath.h>
.br
')

## Format a parameter description
## $1: the name of the parameter
## $2: the description of the parameter
define(`LIBPATH_PARAMETER', `.I $1
will be $2
.br')

define(`LIBPATH_SEE_ALSO', `
.BR cware (cware),
.BR libpath (cware)
')

## Error list macros

define(`LIBPATH_ERROR_LIST_START', `
This macro will print an error message to the stderr, and exit the program when
any of the following conditions are met:
.RS
')

## Define a possible error condition
## $1: the error condition
define(`LIBPATH_ERROR_COND', `
.IP o 0.4i
$1
.br
')

define(`LIBPATH_ERROR_LIST_END', `
.RE
')
