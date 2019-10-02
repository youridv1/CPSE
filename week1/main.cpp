#include "hwlib.hpp"

extern "C" void uart_put_char( char c ){ // function to output a given char to the terminal session
   hwlib::cout << c;
}

extern "C" void print_asciz( const char * s ); // print a string one char at a time

extern "C" void application(); // implementation

extern "C" void toggle_case( char c ); // flips all letters

int main( void ){

   namespace target = hwlib::target;

      // wait for the PC console to start
   hwlib::wait_ms( 2000 );

   application();
}
