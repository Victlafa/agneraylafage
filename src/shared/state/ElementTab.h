// Generated by dia2code
#ifndef STATE__ELEMENTTAB__H
#define STATE__ELEMENTTAB__H

#include <stdlib.h>
#include <vector>
#include <memory>

namespace state {
  class Element;
  class Player;
}

#include "TypeID.h"
#include "ID.h"
#include "Element.h"

namespace state {

  /// class ElementTab - 
  class ElementTab {
    // Associations
    state::TypeID tabType;
    // Attributes
  private:
    size_t width     = 7;
    size_t height     = 5;
    std::vector<std::unique_ptr<Element> > list;
    // Operations
  public:
    ElementTab (TypeID type, size_t width = 7, size_t height = 5);
    ~ElementTab ();
    size_t getWidth () const;
    size_t getHeight () const;
    void resize (size_t width, size_t height);
    const std::unique_ptr<Element>& get (int i, int j = 0) const;
    const std::unique_ptr<Element>& operator ( )  (int i, int j = 0) const;
    const std::unique_ptr<Element>& getByNumber (int number) const;
    void set (Element* elem, int i, int j = 0);
    void init ();
    void initCells ();
    bool verifUnicite (std::vector<int> listeTmp, int i, int j);
    bool verifValiditeCase (unsigned int i, unsigned int j);
    void poisonCell (bool poison, int i, int j);
    bool isPoisoned (int i, int j);
    bool isOccupiedByOpp (int i, int j, Player* joueur);
    void moveElement (int i_elem, int j_elem, int new_i_elem, int new_j_elem, int fight);
    void placeElement (int new_i_elem, int new_j_elem, ID creaType);
    void assignSpecialCell (Player* winner, Player* loser, ID type);
    bool isSpecial (int i, int j);
    // Setters and Getters
    TypeID getTabType() const;
    void setTabType(TypeID tabType);
  };

};

#endif
