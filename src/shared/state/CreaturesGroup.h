// Generated by dia2code
#ifndef STATE__CREATURESGROUP__H
#define STATE__CREATURESGROUP__H


namespace state {
  class Player;
  class Element;
  class CreaturesGroup;
}

#include "CreaturesID.h"
#include "Element.h"
#include "Player.h"

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
    Player* joueur;
    // Operations
  public:
    CreaturesGroup (CreaturesID type, Player* joueur);
    CreaturesGroup (CreaturesID type, Player* joueur, const Element& elem);
    CreaturesGroup (const Element& elem);
    ~CreaturesGroup ();
    bool getPlaced () const;
    void toPlace (int x, int y);
    bool operator== (CreaturesGroup otherGroup);
    Player* getPlayer ();
    void setPlayer (Player* joueur);
    // Setters and Getters
    CreaturesID getCreaturesType() const;
    void setCreaturesType(CreaturesID creaturesType);
  };

};

#endif
