// Generated by dia2code
#ifndef ENGINE__NEWGAMEACTION__H
#define ENGINE__NEWGAMEACTION__H


namespace state {
  class State;
};
namespace engine {
  class Action;
}

#include "Action.h"

namespace engine {

  /// class NewGameAction - 
  class NewGameAction : public engine::Action {
    // Operations
  public:
    NewGameAction ( );
    void apply (state::State& state);
    void undo (state::State& etat);
    // Setters and Getters
  };

};

#endif
