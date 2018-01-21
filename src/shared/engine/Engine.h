// Generated by dia2code
#ifndef ENGINE__ENGINE__H
#define ENGINE__ENGINE__H

#include <map>
#include <memory>
#include <stack>
#include <json/json.h>

namespace state {
  class State;
};
namespace engine {
  class Command;
  class Action;
};
namespace state {
  class Player;
}

#include "state/State.h"
#include "state/CreaturesID.h"
#include "Command.h"
#include "Action.h"
#include "state/Player.h"

namespace engine {

  /// class Engine - 
  class Engine {
    // Associations
    // Attributes
  public:
    std::map<int,std::shared_ptr<Command> > currentCommands;
    int nbrLastCommands;
  private:
    state::State currentState;
    int tour;
    std::stack<std::shared_ptr<Action> > pileAction;
    Json::Value record;
    // Operations
  public:
    Engine (state::CreaturesID CreaPl1, state::CreaturesID CreaPl2);
    ~Engine ();
    void addPassiveCommands ();
    virtual void addCommand (int priority, std::shared_ptr<Command> cmd);
    void update ();
    state::State& getState ();
    const std::unique_ptr<state::Player>& getPlayer (int num) const;
    void poisonCell (bool poison, int i_cell, int j_cell);
    void increaseTour ();
    int getTour ();
    void addAction (std::shared_ptr<Action> action);
    void undo ();
    std::stack<std::shared_ptr<Action> >& getPileAction ();
    Json::Value getRecord () const;
    void setRecord (Json::Value record);
    // Setters and Getters
  };

};

#endif
