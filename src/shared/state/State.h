// Generated by dia2code
#ifndef STATE__STATE__H
#define STATE__STATE__H

#include <memory>

namespace state {
  class CellTab;
  class CreaturesTab;
  class Player;
  class ElementTab;
}

#include "CellTab.h"
#include "CreaturesTab.h"
#include "Player.h"
#include "CreaturesID.h"
#include "ElementTab.h"

namespace state {

  /// class State - 
  class State {
    // Associations
    // Attributes
  private:
    std::unique_ptr<CellTab> grid;
    std::unique_ptr<CreaturesTab> characters;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    int totalCellNbr;
    int freeCellNbr;
    // Operations
  public:
    State (CreaturesID typePl1);
    ~State ();
    const std::unique_ptr<CellTab>& getGrid () const;
    const std::unique_ptr<CreaturesTab>& getCharacters () const;
    int getCellNbr () const;
    int getFreeCellNbr () const;
    const std::unique_ptr<Player>& getPlayer (int number) const;
    void reset (CreaturesID typeCreatures);
    void initCreatures ();
    // Setters and Getters
  };

};

#endif
