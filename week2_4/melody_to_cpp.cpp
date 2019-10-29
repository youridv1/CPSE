#include "melody_to_cpp.hpp"

MelodyToCPP::MelodyToCPP(std::ostream& ostream) : ostream( ostream ) {}

void MelodyToCPP::start(){
  ostream << R"(#pragma once

#include "melody.hpp"

class meldody : public melody {
public:
  void play(note_player& p) {)";
}

void MelodyToCPP::play(const note& note){
  ostream << "\n        p.play(note{" << note.frequency << ", " << note.duration << "});";
}

void MelodyToCPP::end() {
    ostream << R"(
    }
};)";
}
