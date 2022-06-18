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

m4 ./template/Makefile.dos > ./Makefile.dos
