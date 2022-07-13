#!/bin/sh
# Load documentation and Makefiles. Requires docgen and makegen
# as dependencies. Although, this realistically should not be
# ran by end users, and should instead be ran by developers.

docgen project ./src/libpath.h --section cware  \
                               --format manpage \
                               --title 'C-Ware Manuals' \
                               --date "`date +'%B %d, %Y'`"

docgen functions ./src/libpath.h --section cware  \
                                 --format manpage \
                                 --title 'C-Ware Manuals' \
                                 --date "`date +'%B %d, %Y'`"

makegen library unix --name libpath \
                     --cflags '\-fpic' > Makefile

makegen library unix --name libpath \
                     --ldlibs '\-lm' --cflags '\-fpic -Wall -Wextra -Wpedantic -Wshadow -ansi -g -Wno-unused-parameter -Wno-type-limits -Wno-sign-compare' > Makefile.dev

m4 ./template/Makefile.dos > ./Makefile.dos
