#include "mySet.hpp"

int main(){
    mySet<char, 3> example;
    example.add('j');
    example.add('a');

    std::cout << example.max() << std::endl;

    return 0;
}
