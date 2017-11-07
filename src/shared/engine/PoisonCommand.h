// Generated by dia2code
#ifndef ENGINE__POISONCOMMAND__H
#define ENGINE__POISONCOMMAND__H


namespace state {
  class State;
};
namespace engine {
  class Command;
}

#include "CommandTypeID.h"
#include "Command.h"

namespace engine {

  /// class PoisonCommand - 
  class PoisonCommand : public engine::Command {
    // Attributes
  protected:
    int cell;
    int creatures;
    // Operations
  public:
    PoisonCommand (int cell, int creatures);
    bool isPoisoned (state::State& state);
    killCreatures (state::State& state);
    CommandTypeID getTypeID () const;
    void execute (state::State& state);
    // Setters and Getters
    int getCell() const;
    void setCell(int cell);
    int getCreatures() const;
    void setCreatures(int creatures);
  };

};

#endif