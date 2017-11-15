// Generated by dia2code
#ifndef STATE__CREATURESGROUP__H
#define STATE__CREATURESGROUP__H


namespace state {
  class Element;
  class CreaturesGroup;
}

#include "ID.h"
#include "Element.h"

namespace state {

  /// class CreaturesGroup - 
  class CreaturesGroup : public state::Element {
    // Attributes
  public:
    static int stolenResourceNbr;
  private:
    bool placed;
    // Operations
  public:
    CreaturesGroup (ID type);
    CreaturesGroup (const Element& elem);
    ~CreaturesGroup ();
    bool getPlaced () const;
    void toPlace (int x, int y);
    bool operator== (CreaturesGroup otherGroup);
    // Setters and Getters
  };

};

#endif
