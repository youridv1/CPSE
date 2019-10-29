#include "note_player.hpp"
#include "hwlib.hpp"

class NotePrinter : public note_player {
public:
  void play(const note& note) override {
    hwlib::cout << note << hwlib::endl;
  }
};
