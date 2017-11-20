// Generated by dia2code
#ifndef STATE__ELEMENT__H
#define STATE__ELEMENT__H


namespace state {
  class Player;
  class Element;
}

#include "ID.h"
#include "CellState.h"

namespace state {

  /// class Element - 
  class Element {
    // Associations
    state::ID elemType;
    state::CellState cellState;
    // Attributes
  private:
    Player* player;
  protected:
    int x;
    int y;
    int creaturesNbr;
    // Operations
  public:
    Element ();
    Element (ID type, CellState state);
    virtual ~Element ();
    bool operator== (Element otherElement);
    Player* getPlayer () const;
    void setPlayer (Player* player);
    // Setters and Getters
    ID getElemType() const;
    void setElemType(ID elemType);
    CellState getCellState() const;
    void setCellState(CellState cellState);
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    int getCreaturesNbr() const;
    void setCreaturesNbr(int creaturesNbr);
  };

};

#endif
