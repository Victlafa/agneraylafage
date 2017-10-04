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
    size_t width;
    size_t height;
    std::vector<std::unique_ptr<Element>> list;
    // Operations
  public:
    ElementTab (size_t width = 0, size_t height = 1);
    ~ElementTab ();
    size_t const getWidth ();
    size_t const getHeight ();
    size_t add (Element* elem);
    void resize (size_t width, size_t height);
    Element* const get (int i, int j = 0);
    void set (int i, int j = 0);
    const Element& operator ( )  (int i, int j = 0);
    // Setters and Getters
    TypeID getTabType() const;
    void setTabType(TypeID tabType);
  };

};

#endif
