#!/bin/sh
# Run checks

echo Running test tests/path/init
$1 tests/path/init
echo Ran test tests/path/init

echo Running test tests/path/free
$1 tests/path/free
echo Ran test tests/path/free

echo Running test tests/path/add_root
$1 tests/path/add_root
echo Ran test tests/path/add_root
