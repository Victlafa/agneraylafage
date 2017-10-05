// Generated by dia2code
#ifndef STATE__CREATURESGROUP__H
#define STATE__CREATURESGROUP__H


namespace state {
  class Element;
}

#include "CreaturesID.h"
#include "Element.h"

namespace state {

  /// class CreaturesGroup - 
  class CreaturesGroup : public state::Element {
    // Associations
    state::CreaturesID creaturesType;
    // Attributes
  public:
    static int stolenResourceNbr;
  private:
    bool placed;
    // Operations
  public:
    CreaturesGroup (CreaturesID type);
    ~CreaturesGroup ();
    bool getPlaced ();
    void toPlace (int x, int y);
    // Setters and Getters
    CreaturesID getCreaturesType() const;
    void setCreaturesType(CreaturesID creaturesType);
  };

};

#endif
