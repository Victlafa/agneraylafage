// Generated by dia2code
#ifndef RENDER__CREATURESSURFACE__H
#define RENDER__CREATURESSURFACE__H

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

namespace render {
  class Tile;
  class Surface;
}

#include "Surface.h"

namespace render {

  /// class CreaturesSurface - 
  class CreaturesSurface : public render::Surface {
    // Attributes
  private:
    std::vector<sf::VertexArray> quadsList;
    // Operations
  public:
    void loadTexture (const std::string& imgFile);
    void setSpriteLocation (int index, int x, int y);
    void setSpriteTexture (int index, const Tile& tex);
    void draw (sf::RenderTarget& target, sf::RenderStates states) const;
    void initQuads (int count);
    // Setters and Getters
  };

};

#endif