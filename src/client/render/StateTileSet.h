// Generated by dia2code
#ifndef RENDER__STATETILESET__H
#define RENDER__STATETILESET__H

#include <vector>
#include <string>
#include <memory>

namespace render {
  class Tile;
};
namespace state {
  class Element;
};
namespace render {
  class TileSet;
}

#include "Tile.h"
#include "state/Element.h"
#include "TileSet.h"

namespace render {

  /// class StateTileSet - 
  class StateTileSet : public render::TileSet {
    // Attributes
  private:
    std::vector<Tile> chars;
    // Operations
  public:
    StateTileSet ();
    int getCellWidth () const;
    int getCellHeight () const;
    const std::string getImageFile () const;
    const Tile& getCharTile (char c) const;
    const Tile& getTile (const state::Element& elem) const;
    const Tile& getTile (const std::unique_ptr<state::Element>& elem) const;
    // Setters and Getters
  };

};

#endif
