// Generated by dia2code
#ifndef STATE__CELL__H
#define STATE__CELL__H

#include <string>

namespace state {
  class Element;
  class CreaturesGroup;
}

#include "Element.h"
#include "CellState.h"
#include "CreaturesGroup.h"

namespace state {

  /// class Cell - 
  class Cell : public state::Element {
    // Associations
    state::CellState cellState;
    // Attributes
  protected:
    std::string resType;
    int resNbr;
    // Operations
  public:
    Cell ();
    ~Cell ();
    //virtual TypeID const getTypeID () = 0;
    // Setters and Getters
    CellState getCellState() const;
    void setCellState(CellState cellState);
    const std::string& getResType() const;
    void setResType(const std::string& resType);
    int getResNbr() const;
    void setResNbr(int resNbr);
  };

};

#endif
