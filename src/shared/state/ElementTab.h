// Generated by dia2code
#ifndef STATE__ELEMENTTAB__H
#define STATE__ELEMENTTAB__H

#include <stdlib.h>
#include <vector>
#include <memory>

namespace state {
  class Element;
}

#include "TypeID.h"
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
    const std::unique_ptr<Element>& getByNumber (int number) const;
    void set (Element* elem, int i, int j = 0);
    Element& operator ( )  (int i, int j = 0) const;
    void init ();
    void initCells ();
    void initCreatures ();
    // Setters and Getters
    TypeID getTabType() const;
    void setTabType(TypeID tabType);
  };

};

#endif
