// Generated by dia2code
#ifndef RENDER__CHARSTILESET__H
#define RENDER__CHARSTILESET__H

#include <vector>
#include <string>

namespace render {
  class Tile;
  class TileSet;
}

#include "Tile.h"
#include "TileSet.h"

namespace render {

  /// class CharsTileSet - 
  class CharsTileSet : public render::TileSet {
    // Attributes
  private:
    std::vector<Tile> creaturesPlayer1;
    std::vector<Tile> creaturesPlayer2;
    // Operations
  public:
    CharsTileSet ();
    int getCellWidth () const;
    int getCellHeight () const;
    const std::string getImageFile () const;
    const Tile& getTile (const state::ElementTab& elemTab) const;
    // Setters and Getters
  };

};

#endif