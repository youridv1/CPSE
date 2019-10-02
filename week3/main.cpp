#include "klok.hpp"

int main( void ){
   namespace target = hwlib::target; // create a namespace based on hwlib::target in order to save yourself typing hwlib:: everywhere where hwlib is needed

   auto scl = target::pin_oc( target::pins::scl ); // create SCL pin for i2c
   auto sda = target::pin_oc( target::pins::sda ); // create SDA pin for i2c

   auto uurknop = target::pin_in( 0, 15 ); // create a pin for the button used to skip hours
   auto minuutknop = target::pin_in( 3, 1 ); // create a pin for the button used to skip minutes

   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda ); // create a bus object to connect with the display

   auto display = hwlib::glcd_oled( i2c_bus, 0x3c ); // create a display object based on the hwlib oled class.

   constexpr std::array<hwlib::xy, 60> table = vultabel(20); // fill a table with polar coordinates for all 60 minutes in a clock at 20 pixels from the origin
   constexpr std::array<hwlib::xy, 60> urentable = vultabel(12); // same as above but at 12 pixels from the origin

   line uurwijzer( display, hwlib::xy( 64, 32), urentable[0] ); // define an hour hand with the inital position at 12 o'clock
   line minuutwijzer( display, hwlib::xy( 64, 32), table[30] ); // do the same for the minute hand but at 6 o'clock (so the hands don't overlap at startup for debugging purposes)

   line uur12 ( display, table[ 0], table[ 0] + hwlib::xy(1, 1) ); // define a circle of 12 dots to denote the 12 hours on an analog clock
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

   std::array< drawable *, 14 > objects = { &uurwijzer, &minuutwijzer, &uur12, &uur11, &uur10, &uur9, &uur8, &uur7, &uur6, &uur5, &uur4, &uur3, &uur2, &uur1 }; // create an array of all drawable objects

   auto starttime = hwlib::now_us(); // define the value of the starttime to base the number of elapsed microseconds on.
   auto currenttime = hwlib::now_us(); // initalize the variable of the currenttime to later use for timekeeping. (defined with the corresponding function so auto can be used)
   int minuut = 0; // start minutes at 0
   int uur = 0; // start hours at 0

   uurwijzer.setEnd(table[uur]); //update hourhand to position for hours = 0
   minuutwijzer.setEnd(urentable[minuut]); // update minute hand to position for minutes = 0
   display.clear(); // clear the display
   for( auto & p : objects ){ // update the display buffer
       p->draw();
   }
   display.flush(); // flush to the actual display

   for(;;){ // loop forever
     uurknop.refresh(); // refresh the state of the button used to skip hours
     minuutknop.refresh(); // same for minutes
     if( !uurknop.read() ){ // check whether the button is pressed and skip the hour hand one 5 minutes (or 1 hour) if so. Clear and redraw display as well
       uurophogen( uur );
       uurwijzer.setEnd(urentable[uur]);
       display.clear();
       for( auto & p : objects ){
           p->draw();
       }
       display.flush();
     }
     if( !minuutknop.read() ){ // check whether the button is pressed and skip the minute hand one minute if so. Clear en redraw the display as well
       minuutophogen( minuut, uur);
       uurwijzer.setEnd(urentable[uur]);
       minuutwijzer.setEnd(table[minuut]);
       display.clear();
       for( auto & p : objects ){
           p->draw();
       }
       display.flush();
     }
     currenttime = hwlib::now_us(); // update the current time
     if(currenttime - starttime > (60 * 1000000)){ // if it has been more than 60.000.000 microseconds since the last update of starttime, one minute has passed
       starttime = hwlib::now_us(); // update the starttime to now
       minuutophogen( minuut, uur); // update the minute hand to be positioned one minute forward from the last known position
       uurwijzer.setEnd(urentable[uur]); // update hourhand
       minuutwijzer.setEnd(table[minuut]); // update minute hand
       display.clear(); // clear display and draw everything. flush afterwards.
       for( auto & p : objects ){
           p->draw();
       }
       display.flush();
     }
   }
 }
