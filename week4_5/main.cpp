#include "hwlib.hpp"

extern "C" void compressed();
extern "C" void print(char c){
    hwlib::cout << c;
}

int main( void ){
   hwlib::wait_ms( 2000 );
   compressed();
}
