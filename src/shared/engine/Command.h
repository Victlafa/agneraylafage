// Generated by dia2code
#ifndef ENGINE__COMMAND__H
#define ENGINE__COMMAND__H

#include <stack>
#include <memory>
#include <json/json.h>

namespace engine {
  class Action;
};
namespace state {
  class State;
};
namespace engine {
  class Command;
}

#include "CommandTypeID.h"
#include "Action.h"
#include "state/State.h"

namespace engine {

  /// class Command - 
  class Command {
    // Attributes
  protected:
    int player;
    // Operations
  public:
    virtual ~Command ();
    virtual CommandTypeID getTypeID () const = 0;
    virtual void execute (std::stack<std::shared_ptr<Action>>& pile, state::State& state) = 0;
    virtual void serialize (Json::Value& out) const = 0;
    Command* deserialize (const Json::Value& in);
    // Setters and Getters
    int getPlayer() const;
    void setPlayer(int player);
  };

};

#endif
