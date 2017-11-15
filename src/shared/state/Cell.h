// Generated by dia2code
#ifndef STATE__CELL__H
#define STATE__CELL__H

#include <string>

namespace state {
  class Element;
}

#include "ID.h"
#include "Element.h"

namespace state {

  /// class Cell - 
  class Cell : public state::Element {
    // Attributes
  protected:
    std::string resType;
    int resNbr;
    bool occupied     = false;
    // Operations
  public:
    Cell ();
    Cell (ID type);
    Cell (const Element& elem);
    ~Cell ();
    // Setters and Getters
    const std::string& getResType() const;
    void setResType(const std::string& resType);
    int getResNbr() const;
    void setResNbr(int resNbr);
    bool getOccupied() const;
    void setOccupied(bool occupied);
  };

};

#endif
