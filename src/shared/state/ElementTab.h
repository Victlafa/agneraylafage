// Generated by dia2code
#ifndef STATE__ELEMENTTAB__H
#define STATE__ELEMENTTAB__H

#include <stdlib.h>
#include <vector>
#include <memory>

namespace state {
  class Element;
}

#include "Element.h"
#include "TypeID.h"

namespace state {

  /// class ElementTab - 
  class ElementTab {
    // Associations
    state::TypeID tabType;
    // Attributes
  private:
    size_t width;
    size_t height;
    std::vector<std::unique_ptr<Element>>* list;
    // Operations
  public:
    ElementTab (size_t width = 0, size_t height = 1);
    ~ElementTab ();
    size_t getWidth ();
    size_t getHeight ();
    void resize (size_t width, size_t height);
    const Element& get (int i, int j = 0);
    void set (Element elem, int i, int j = 0);
    const Element& operator ( )  (int i, int j = 0);
    const TypeID getTypeID ();
    // Setters and Getters
    TypeID getTabType() const;
    void setTabType(TypeID tabType);
  };

};

#endif
