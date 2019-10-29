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

HEADERS += note.hpp
HEADERS += melody.hpp
HEADERS += note_player.hpp
HEADERS += fur_elise.hpp

HEADERS += note_player_gpio.hpp
SOURCES += note_player_gpio.cpp

HEADERS += rtttl_player.hpp
SOURCES += rtttl_player.cpp

SOURCES += my_melody.cpp

# other places to look for files for this project
SEARCH  :=

# set REATIVE to the next higher directory
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../../v2cpse1-examples/
include $(RELATIVE)Makefile.due

.PHONY: all clean

all: my_melody.cpp

clean:
	rm -f generator my_melody.cpp *.o bmptk* *.ld *.elf

generator: generator.cpp rtttl_player.cpp melody_to_cpp.cpp
	g++ -std=c++17 generator.cpp rtttl_player.cpp melody_to_cpp.cpp -o generator

my_melody.cpp: generator
	./generator my_melody.cpp
