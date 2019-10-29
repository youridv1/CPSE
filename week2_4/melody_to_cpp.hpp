#include "hwlib.hpp"
#include "note_player.hpp"
#include <iostream>

class MelodyToCPP : public note_player {
private:
  std::ostream& ostream;

public:
  MelodyToCPP(std::ostream& ostream);
  void start();
  void end();
  void play(const note& note) override;
};
