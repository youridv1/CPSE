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
SOURCES += note.cpp

HEADERS += melody.hpp
HEADERS += note_player.hpp
HEADERS += fur_elise.hpp
HEADERS += noteprinter.hpp

HEADERS += note_player_gpio.hpp
SOURCES += note_player_gpio.cpp

HEADERS += rtttl_player.hpp
SOURCES += rtttl_player.cpp

HEADERS += melody_to_cpp.hpp
SOURCES += melody_to_cpp.cpp

# other places to look for files for this project
SEARCH  :=

# set REATIVE to the next higher directory
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../../v2cpse1-examples/
include $(RELATIVE)Makefile.native
