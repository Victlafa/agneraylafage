// Generated by dia2code
#ifndef STATE__PLAYER__H
#define STATE__PLAYER__H

#include <string>
#include <vector>

namespace state {
  class CreaturesGroup;
}

#include "CreaturesGroup.h"
#include "CreaturesID.h"

namespace state {

  /// class Player - 
  class Player {
    // Associations
    state::CreaturesID clanName;
    // Attributes
  private:
    int cellNbr;
    int zonesNbr;
    int conquestPoints;
    std::vector<std::string>* speCellsNames;
    int xLastCell     = 0;
    int yLastCell     = 0;
    std::vector<CreaturesGroup>* allCreatures;
    int creaturesLeft;
    // Operations
  public:
    Player ();
    ~Player ();
    int getCellsNbr () const;
    int getZonesNbr () const;
    int getConquestPoints () const;
    int getCreaturesLeft () const;
    std::vector<std::string>* getSpeCellsNames () const;
    int getXLastCell () const;
    int getYLastCell () const;
    std::vector<CreaturesGroup>* getAllCreatures () const;
    void setCellsNbr (int count);
    void setZonesNbr (int count);
    void setConquestPts (int count);
    void setCreaLeft (int count);
    void decreaseCreaLeft ();
    void modifySpeCellsNames (std::string name, bool add);
    void setXLastCell (int x);
    void setYLastCell (int y);
    void setAllCreatures (std::vector<CreaturesGroup>* creaList);
    void setAllCreatures (bool add, CreaturesGroup group);
    // Setters and Getters
    CreaturesID getClanName() const;
    void setClanName(CreaturesID clanName);
  };

};

#endif
