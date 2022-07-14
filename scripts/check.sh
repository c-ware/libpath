#!/bin/sh
# Run tests in the tests/ directory, if one exists.
#
# $1: the debugger to run the file on

for test_file in `find tests/ -type f`; do
    if [ ! -x "$test_file" ] || [ -d "$test_file" ]; then
        continue
    fi

    printf "Test '%s' starting.\n" $test_file
    $1 ./$test_file
    printf "Test '%s' completed.\n" $test_file
done
