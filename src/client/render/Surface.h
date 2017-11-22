// Generated by dia2code
#ifndef RENDER__SURFACE__H
#define RENDER__SURFACE__H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace render {
  class Tile;
}

namespace render {

  /// class Surface - 
  class Surface {
    // Attributes
  protected:
    sf::Texture texture;
    std::vector<sf::VertexArray> quadsList;
    // Operations
  public:
    Surface ();
    void loadTexture (const std::string& imgFile);
    void setFinalLocation (int index, int shift, int x, int y, const Tile& tex);
    void setTextureLocation (int index, const Tile& tex);
    void draw (sf::RenderTarget& target, sf::RenderStates states) const;
    void initQuads ();
    // Setters and Getters
    const sf::Texture& getTexture() const;
    void setTexture(const sf::Texture& texture);
    const std::vector<sf::VertexArray>& getQuadsList() const;
    void setQuadsList(const std::vector<sf::VertexArray>& quadsList);
  };

};

#endif
