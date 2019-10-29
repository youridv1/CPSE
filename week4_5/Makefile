#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
#
#############################################################################

# source & header files in this project (main.cpp is automatically assumed)

SOURCES += compressed.asm
SOURCES += decompress.asm
HEADERS += compressor.hpp
HEADERS += match.hpp

# other places to look for files for this project
SEARCH  :=

# set REATIVE to the next higher directory
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../../v2cpse1-examples/


.PHONY: clean


lzcompressortoasm:
	g++ generator.cpp *.hpp -o lzcompressortoasm

compressed.asm: lzcompressortoasm
	./lzcompressortoasm
include $(RELATIVE)Makefile.due


schoon: clean
	rm lzcompressortoasm compressed.asm *.o *.map *.ld *.c
