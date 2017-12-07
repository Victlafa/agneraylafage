// Generated by dia2code
#ifndef ENGINE__POISONCOMMAND__H
#define ENGINE__POISONCOMMAND__H

#include <vector>
#include <stack>
#include <memory>

namespace engine {
  class Action;
};
namespace state {
  class State;
};
namespace engine {
  class Command;
}

#include "state/ID.h"
#include "Action.h"
#include "CommandTypeID.h"
#include "Command.h"
#include "state/State.h"

namespace engine {

  /// class PoisonCommand - 
  class PoisonCommand : public engine::Command {
    // Attributes
  protected:
    std::vector<int> targetCell;
    state::ID type;
    // Operations
  public:
    PoisonCommand (int i, int j, state::ID id, int player);
    void execute (std::stack<std::shared_ptr<Action>>& pile, state::State& state);
    CommandTypeID getTypeID () const;
    // Setters and Getters
    const std::vector<int>& getTargetCell() const;
    void setTargetCell(const std::vector<int>& targetCell);
    state::ID getType() const;
    void setType(state::ID type);
  };

};

#endif
