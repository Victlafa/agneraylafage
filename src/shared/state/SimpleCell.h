// Generated by dia2code
#ifndef STATE__SIMPLECELL__H
#define STATE__SIMPLECELL__H

#include <string>

namespace state {
  class Cell;
}

#include "SimpleCellID.h"
#include "Cell.h"

namespace state {

  /// class SimpleCell - 
  class SimpleCell : public state::Cell {
    // Associations
    state::SimpleCellID simpleCellType;
    // Operations
  public:
    SimpleCell (SimpleCellID type, std::string resType, int resNbr, int x, int y);
    ~SimpleCell ();
<<<<<<< HEAD
    const SimpleCellID getSimpleCellID ();
=======
>>>>>>> d389eee71b7f454716d13305b15d369de371b63e
    // Setters and Getters
    SimpleCellID getSimpleCellType() const;
    void setSimpleCellType(SimpleCellID simpleCellType);
  };

};

#endif
