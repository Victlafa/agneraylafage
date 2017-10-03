// Generated by dia2code
#ifndef STATE__SIMPLECELL__H
#define STATE__SIMPLECELL__H

#include <vector>

namespace state {
  class Cell;
  class Zone;
}

#include "Cell.h"
#include "SimpleCellID.h"
#include "Zone.h"

namespace state {

  /// class SimpleCell - 
  class SimpleCell : public state::Cell {
    // Associations
    state::SimpleCellID SimpleCell_type;
    state::Zone Cells_in_zone;
    // Attributes
  private:
    std::vector<string> genResType;
    std::vector<int> genResNbr;
    // Operations
  public:
    std::vector<string> getResType ();
    std::vector<int> getResNbr ();
    void addResType (string resType);
    void addResNbr (int resNbr);
    // Setters and Getters
    SimpleCellID getSimplCell_type() const;
    void setSimpleCell_type(SimpleCellID SimpleCell_type);
    const Zone& getCells_in_zone() const;
    void setCells_in_zone(const Zone& Cells_in_zone);
  };

};

#endif