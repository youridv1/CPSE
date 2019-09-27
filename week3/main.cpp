#include "klok.hpp"

int main( void ){
   namespace target = hwlib::target;

   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );

   auto uurknop = target::pin_in( 0, 15 );
   auto minuutknop = target::pin_in( 3, 1 );

   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

   auto display = hwlib::glcd_oled( i2c_bus, 0x3c );

   constexpr std::array<hwlib::xy, 60> table = vultabel(20);
   constexpr std::array<hwlib::xy, 60> urentable = vultabel(12);

   line uurwijzer( display, hwlib::xy( 64, 32), urentable[0] );
   line minuutwijzer( display, hwlib::xy( 64, 32), table[30] );

   line uur12 ( display, table[ 0], table[ 0] + hwlib::xy(1, 1) );
   line uur11 ( display, table[55], table[55] + hwlib::xy(1, 1) );
   line uur10 ( display, table[50], table[50] + hwlib::xy(1, 1) );
   line uur9  ( display, table[45], table[45] + hwlib::xy(1, 1) );
   line uur8  ( display, table[40], table[40] + hwlib::xy(1, 1) );
   line uur7  ( display, table[35], table[35] + hwlib::xy(1, 1) );
   line uur6  ( display, table[30], table[30] + hwlib::xy(1, 1) );
   line uur5  ( display, table[25], table[25] + hwlib::xy(1, 1) );
   line uur4  ( display, table[20], table[20] + hwlib::xy(1, 1) );
   line uur3  ( display, table[15], table[15] + hwlib::xy(1, 1) );
   line uur2  ( display, table[10], table[10] + hwlib::xy(1, 1) );
   line uur1  ( display, table[ 5], table[ 5] + hwlib::xy(1, 1) );

   std::array< drawable *, 14 > objects = { &uurwijzer, &minuutwijzer, &uur12, &uur11, &uur10, &uur9, &uur8, &uur7, &uur6, &uur5, &uur4, &uur3, &uur2, &uur1 };

   auto starttime = hwlib::now_us();
   auto currenttime = hwlib::now_us();
   int minuut = 0;
   int uur = 0;

   uurwijzer.setEnd(table[uur]);
   minuutwijzer.setEnd(urentable[minuut]);
   display.clear();
   for( auto & p : objects ){
       p->draw();
   }
   display.flush();

   for(;;){
     uurknop.refresh();
     minuutknop.refresh();
     if( !uurknop.read() ){
       uurophogen( uur );
       uurwijzer.setEnd(urentable[uur]);
       display.clear();
       for( auto & p : objects ){
           p->draw();
       }
       display.flush();
     }
     if( !minuutknop.read() ){
       minuutophogen( minuut, uur);
       uurwijzer.setEnd(urentable[uur]);
       minuutwijzer.setEnd(table[minuut]);
       display.clear();
       for( auto & p : objects ){
           p->draw();
       }
       display.flush();
     }
     currenttime = hwlib::now_us();
     if(currenttime - starttime > (1 * 1000000)){
       starttime = hwlib::now_us();
       minuutophogen( minuut, uur);
       uurwijzer.setEnd(urentable[uur]);
       minuutwijzer.setEnd(table[minuut]);
       display.clear();
       for( auto & p : objects ){
           p->draw();
       }
       display.flush();
     }
   }
 }
