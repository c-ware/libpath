include(src/m4stack.m4)

M4STACK_DECLARE(IntStack, int);
M4STACK_DECLARE(StringStack, char *);

define(`STRING_STACK_TYPE', `char *')
define(`STRING_STACK_FREE', `free($1)')
define(`STRING_STACK_NAME', `struct StringStack')

define(`INT_STACK_TYPE', `int')
define(`INT_STACK_FREE', `')
define(`INT_STACK_NAME', `struct IntStack')
