// Generated by dia2code
#ifndef RENDER__CELLTILESET__H
#define RENDER__CELLTILESET__H

#include <vector>
#include <string>

namespace render {
  class Tile;
  class TileSet;
}

#include "Tile.h"
#include "TileSet.h"

namespace render {

  /// class CellTileSet - 
  class CellTileSet : public render::TileSet {
    // Attributes
  private:
    std::vector<Tile> cells;
    // Operations
  public:
    CellTileSet ();
    int getCellWidth () const;
    int getCellHeight () const;
    const std::string getImageFile () const;
    const Tile& getTile (int index, int player = 1) const;
    // Setters and Getters
  };

};

#endif
