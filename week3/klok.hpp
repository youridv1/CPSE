#include "hwlib.hpp"
#include <array>
#include <math.h>

#define PI 3.14159265

//=============================================================================

void minuutophogen( int & minuut, int & uur ){
  minuut++;
  if( minuut == 60 ){
    minuut = 0;
    uur += 5;
    if( uur == 60 ){ uur = 0; }
  }
}

//=============================================================================

void uurophogen( int & uur ){
  uur += 5;
  if( uur == 60 ){ uur = 0; }
}

//=============================================================================
constexpr const hwlib::xy berekenpositie(const int tijd, const int lengte){ // returns coordinates in the form of hwlib::xy
  int degrees = 6 * tijd + 90; // calculate the amount of degrees for any given minute, given there's 60 minutes in one hour and the 12 o'clock point is at 90 degrees.
  float radians = PI * degrees / 180; // convert degrees to radians
  int x = lengte * cos(radians) + 64; // add the calculated offset coordinate to the midpoint of the clock for X.
  int y = lengte * sin(radians) + 32; // do the same for Y.
  return hwlib::xy ( x , y ); //return the coordinates for the endpoint of the hand for the given time out of 60.
}
//=============================================================================

constexpr const std::array<hwlib::xy, 60> vultabel(const int lengte){ // fill an std::array with the 60 possible endpoint coordinates for the hands of the clock.
  std::array<hwlib::xy, 60> tabel; // initialize a table to later return.
  for(int i = 0; i < 60; i++){ // use berekenpositie to calculate all 60 values.
    tabel[i] = berekenpositie(i, lengte); // put these in the array in the appropriate order
  }
  return tabel;
}

//=============================================================================
class drawable { // abstract class which forms the basis for all drawable objects used to make a clock
protected:

  hwlib::glcd_oled & oled; // variable which points to the desired display to draw on
  hwlib::xy location; // coordinates for the location of the object
  hwlib::xy size; // size of the object in two dimensions

public:

  drawable ( hwlib::glcd_oled & oled, hwlib::xy location, hwlib::xy size): //constructor, creates object
    oled( oled ),
    location( location ),
    size( size )
  {}

  virtual void draw() = 0; // virtual functions to later override with actual uses.
  virtual void update(){}

};

// ============================================================================

class line : public drawable { // a line, based on drawable.
protected:

  hwlib::xy end; // coordinates of the endpoint of the line

public:

  line( hwlib::glcd_oled & oled, hwlib::xy location, hwlib::xy end ): //constructor, constructs a line out of given parameters
    drawable( oled, location, end - location ), //uses the drawable constructor for parameters not specific to a line. Calculates size by subtracting the location from the endpoint
    end( end ) // saves the given end parameter in the protected variable initialized for that.
  {}

  void draw() override { // create a hwlib::line object based on the known location and endpoint coordinates
    hwlib::line x(location, end); //construct the object
    x.draw( oled ); //draw on the oled using the objects methods.
  }

  void setEnd(hwlib::xy nieuw) { //change the endpoint of the line in order to essentially "move" the hand to the next position on the clock.
    end = nieuw;
  }
};

// ============================================================================
