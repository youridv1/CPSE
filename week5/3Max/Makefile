# Created by Youri "youridv1" de Vor
# Licensed under the Pakken Wat Je Pakken Kan Public License

.PHONY: all run clean
all: test

test: main.cpp mySet.hpp
	g++ -std=c++17 main.cpp mySet.hpp -o test -I $(HOME)/Catch2/single_include/

run: all
	./test

clean:
	rm test
