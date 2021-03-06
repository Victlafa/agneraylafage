// Generated by dia2code
#ifndef STATE__CELLTAB__H
#define STATE__CELLTAB__H

#include <stdlib.h>

namespace state {
  class Player;
  class ElementTab;
}

#include "ID.h"
#include "ElementTab.h"
#include "Player.h"

namespace state {

  /// class CellTab - 
  class CellTab : public state::ElementTab {
    // Operations
  public:
    CellTab (size_t width, size_t height);
    ~CellTab ();
    void initCells ();
    void assignSpecialCell (Player* winner, Player* loser, ID type);
    bool isSpecial (int i, int j);
    // Setters and Getters
  };

};

#endif
