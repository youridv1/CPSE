#include "hwlib.hpp"

extern "C" void uart_put_char( char c ){
   hwlib::cout << c;
}

extern "C" void print_asciz( const char * s );//{
//   while( *s != '\0'){
//      uart_put_char( *s );
//      ++s;
//   }
//}

extern "C" void application();//{
   //print_asciz( "Hello world\n" );
//}


extern "C" void toggle_case( char c ){
  if( ( c >= 'A' && c <= 'Z') || ( c > 'a' && c < 'z' ) ){ // Check if the char represents a letter of the alphabet.
    c ^= 32; // Flip the 5th bit of the char which changes the case
  }
  uart_put_char( c );
}

int main( void ){

   namespace target = hwlib::target;

      // wait for the PC console to start
   hwlib::wait_ms( 2000 );

   application();
}
