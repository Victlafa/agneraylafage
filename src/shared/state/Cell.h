// Generated by dia2code
#ifndef STATE__CELL__H
#define STATE__CELL__H

#include <string>

namespace state {
  class Element;
}

#include "TypeID.h"
#include "Element.h"
#include "CellTypeID.h"
#include "CellState.h"

namespace state {

  /// class Cell - 
  class Cell : public state::Element {
    // Associations
    state::CellTypeID cellType;
    state::CellState cellState;
    // Attributes
  protected:
    std::string resType;
    int resNbr;
    bool occupied     = false;
    // Operations
  public:
    Cell ();
    ~Cell ();
    virtual const TypeID getTypeID () = 0;
    // Setters and Getters
    CellTypeID getCellType() const;
    void setCellType(CellTypeID cellType);
    CellState getCellState() const;
    void setCellState(CellState cellState);
    const std::string& getResType() const;
    void setResType(const std::string& resType);
    int getResNbr() const;
    void setResNbr(int resNbr);
    bool getOccupied() const;
    void setOccupied(bool occupied);
  };

};

#endif
