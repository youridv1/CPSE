#include "klok.hpp"

int main( void ){
   namespace target = hwlib::target;

   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );

   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

   auto display = hwlib::glcd_oled( i2c_bus, 0x3c );

   constexpr const hwlib::xy table[60] = {
     berekenpositie(  0 ),
     berekenpositie(  1 ),
     berekenpositie(  2 ),
     berekenpositie(  3 ),
     berekenpositie(  4 ),
     berekenpositie(  5 ),
     berekenpositie(  6 ),
     berekenpositie(  7 ),
     berekenpositie(  8 ),
     berekenpositie(  9 ),
     berekenpositie( 10 ),
     berekenpositie( 11 ),
     berekenpositie( 12 ),
     berekenpositie( 13 ),
     berekenpositie( 14 ),
     berekenpositie( 15 ),
     berekenpositie( 16 ),
     berekenpositie( 17 ),
     berekenpositie( 18 ),
     berekenpositie( 19 ),
     berekenpositie( 20 ),
     berekenpositie( 21 ),
     berekenpositie( 22 ),
     berekenpositie( 23 ),
     berekenpositie( 24 ),
     berekenpositie( 25 ),
     berekenpositie( 26 ),
     berekenpositie( 27 ),
     berekenpositie( 28 ),
     berekenpositie( 29 ),
     berekenpositie( 30 ),
     berekenpositie( 31 ),
     berekenpositie( 32 ),
     berekenpositie( 33 ),
     berekenpositie( 34 ),
     berekenpositie( 35 ),
     berekenpositie( 36 ),
     berekenpositie( 37 ),
     berekenpositie( 38 ),
     berekenpositie( 39 ),
     berekenpositie( 40 ),
     berekenpositie( 41 ),
     berekenpositie( 42 ),
     berekenpositie( 43 ),
     berekenpositie( 44 ),
     berekenpositie( 45 ),
     berekenpositie( 46 ),
     berekenpositie( 47 ),
     berekenpositie( 48 ),
     berekenpositie( 49 ),
     berekenpositie( 50 ),
     berekenpositie( 51 ),
     berekenpositie( 52 ),
     berekenpositie( 53 ),
     berekenpositie( 54 ),
     berekenpositie( 55 ),
     berekenpositie( 56 ),
     berekenpositie( 57 ),
     berekenpositie( 58 ),
     berekenpositie( 59 ),
   };


   line uurwijzer( display, hwlib::xy( 64, 32), table[0] );
   line minuutwijzer( display, hwlib::xy( 64, 32), table[30] );

   std::array< drawable *, 2 > objects = { &uurwijzer, &minuutwijzer };
   int minuut = 0;
   int uur = 0;
   for(;;){
     if(minuut == 59)
     {
       minuut = 0;
       uur += 5;
     }
     else
     {minuut++;}
     if( uur == 60 ){ uur = 0; }
      display.clear();
      for( auto & p : objects ){
         p->draw();
      }
      display.flush();
      hwlib::wait_ms( 20 );
      uurwijzer.setEnd(table[uur]);
      minuutwijzer.setEnd(table[minuut]);
      }
    }
