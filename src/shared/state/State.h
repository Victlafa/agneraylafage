// Generated by dia2code
#ifndef STATE__STATE__H
#define STATE__STATE__H


namespace state {
  class ElementTab;
  class Player;
}

#include "ElementTab.h"
#include "Player.h"

namespace state {

  /// class State - 
  class State {
    // Associations
    state::Player possess;
    // Attributes
  private:
    ElementTab grid;
    ElementTab characters;
    int totalCellNbr;
    // Operations
  public:
    State ();
    ~State ();
    ElementTab& getGrid ();
    ElementTab& getCharacters ();
    int getCellNbr ();
    // Setters and Getters
    const Player& getPossess() const;
    void setPossess(const Player& possess);
  };

};

#endif
