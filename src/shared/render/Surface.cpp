/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Surface.h"

namespace render
{
    void Surface::loadTexture (const std::string& imgFile)
    {
        if(!this->texture.loadFromFile("./res/" + imgFile)) 
            std::cout<< "Erreur chargement texture de Surface ! \n"<< std::endl;
    }
    
    void Surface::setSpriteLocation (int index, int x, int y){ }
    void Surface::setSpriteTexture (int index, const Tile& tex){ }
    
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
