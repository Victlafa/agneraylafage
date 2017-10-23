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
        if( !this->texture.loadFromFile("./res/" + imgFile) ) 
            std::cout << "Erreur chargement texture !\n" << std::endl;
    }
    
    void Surface::setSpriteLocation (int index, int x, int y)
    {
        
    }
    void Surface::setSpriteTexture (int index, const Tile& tex)
    {
        
    }
    
    void Surface::draw (sf::RenderTarget& target, sf::RenderStates states) const
    {
//        for (int i = 0; i < cellsList; i++)
//            target.draw(cellsList[i],states);
    }
    
    void Surface::initCells (int count)
    {
        //this->cellsList = std::vector<std::unique_ptr<CellDraw>>(count);
    }
}

