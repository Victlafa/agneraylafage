// Generated by dia2code
#ifndef ENGINE__ENGINE__H
#define ENGINE__ENGINE__H

#include <map>
#include <memory>

namespace state {
  class State;
};
namespace engine {
  class Command;
}

#include "state/State.h"
#include "state/CreaturesID.h"
#include "Command.h"

namespace engine {

  /// class Engine - 
  class Engine {
    // Associations
    // Attributes
  private:
    state::State currentState;
    std::map<int,std::unique_ptr<Command> > currentCommands;
    // Operations
  public:
    Engine (state::CreaturesID typePl1);
    ~Engine ();
    void addPassiveCommands ();
    void addCommand (int priority, Command* cmd);
    void update ();
    state::State& getState ();
    const std::unique_ptr<state::Player>& getPlayer (int num) const;
    void poisonCell (bool poison, int i_cell, int j_cell);
    // Setters and Getters
  };

};

#endif
