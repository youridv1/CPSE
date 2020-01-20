run: a.out main.cpp mySet.hpp
	./a.out

a.out: main.cpp mySet.hpp
	make build

clean:
	rm a.out *.gch

build: main.cpp mySet.hpp
	g++ main.cpp mySet.hpp 