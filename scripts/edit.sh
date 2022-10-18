#!/bin/sh
# Bring up all files to edit when a new source file is added,
# test is added, etc.

VIM=vim

$VIM scripts/load.sh
$VIM template/Makefile.cc
$VIM template/Makefile.vcc
$VIM template/Makefile.wat
