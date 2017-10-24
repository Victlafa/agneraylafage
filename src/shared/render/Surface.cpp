/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Surface.h"
#include "Tile.h"

namespace render
{
    void Surface::loadTexture (const std::string& imgFile)
    {
        if(!this->texture.loadFromFile("./res/" + imgFile)) 
            std::cout<< "Erreur chargement texture de Surface ! \n"<< std::endl;
        
    }
    
    void Surface::setFinalLocation (int index, int x, int y, const Tile& tex)
    { 
        int halfHeight = tex.getHeight()/2;
        int halfWidth = tex.getWidth()/2;
        this->quadsList[index][0].position = sf::Vector2f(x - halfWidth, y + halfHeight);
        this->quadsList[index][1].position = sf::Vector2f(x + halfWidth, y + halfHeight);
        this->quadsList[index][2].position = sf::Vector2f(x - halfWidth, y - halfHeight);
        this->quadsList[index][3].position = sf::Vector2f(x + halfWidth, y - halfHeight);
    }
    
    void Surface::setTextureLocation (int index, const Tile& tex)
    { 
        int halfHeight = tex.getHeight()/2;
        int halfWidth = tex.getWidth()/2;
        int x = tex.getX();
        int y = tex.getY();
        
        this->quadsList[index][0].texCoords = sf::Vector2f(x - halfWidth, y + halfHeight);
        this->quadsList[index][1].texCoords = sf::Vector2f(x + halfWidth, y + halfHeight);
        this->quadsList[index][2].texCoords = sf::Vector2f(x - halfWidth, y - halfHeight);
        this->quadsList[index][3].texCoords = sf::Vector2f(x + halfWidth, y - halfHeight);
    }
    
    void Surface::draw (sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (auto elem : quadsList)
            target.draw(elem,states);
    }
    
    void Surface::initQuads (int count)
    {
        this->quadsList.reserve(count);
        for (int i = 0; i < count; i ++)
        {
            // Preparation de la première ligne d'hexagones  :
            this->quadsList.push_back(sf::VertexArray(sf::Quads,4));
        }
    }
//    // Setters and Getters
    const sf::Texture& Surface::getTexture() const
    {
        return this->texture;
    }
    void Surface::setTexture(const sf::Texture& texture)
    {
        this->texture = texture;
    }
    const std::vector<sf::VertexArray>& Surface::getQuadsList() const
    {
        return this->quadsList;
    }
    void Surface::setQuadsList(const std::vector<sf::VertexArray>& quadsList)
    {
        this->quadsList = quadsList;
    }
}
