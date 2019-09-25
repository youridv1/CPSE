#include "hwlib.hpp"
#include <array>
#include <math.h>

#define PI 3.14159265

//=============================================================================
constexpr const hwlib::xy berekenpositie(const int tijd){
  int degrees = 6 * tijd + 90;
  float radians = PI * degrees / 180;
  int x = 20 * cos(radians) + 64;
  int y = 20 * sin(radians) + 32;
  return hwlib::xy ( x , y );
}
//=============================================================================

class drawable {
protected:

  hwlib::glcd_oled & oled;
  hwlib::xy location;
  hwlib::xy size;

public:

  drawable ( hwlib::glcd_oled & oled, hwlib::xy location, hwlib::xy size):
    oled( oled ),
    location( location ),
    size( size )
  {}

  virtual void draw() = 0;
  virtual void update(){}

};

// ============================================================================

class line : public drawable {
protected:

  hwlib::xy end;

public:

  line( hwlib::glcd_oled & oled, hwlib::xy location, hwlib::xy end ):
    drawable( oled, location, end - location ),
    end( end )
  {}

  void draw() override {
    hwlib::line x(location, end);
    x.draw( oled );
  }

  void setEnd(hwlib::xy nieuw) {
    end = nieuw;
  }
};

// ============================================================================
