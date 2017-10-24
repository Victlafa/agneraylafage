/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CellSurface.h"

namespace render
{
    void CellSurface::loadTexture (const std::string& imgFile)
    {
        if(!this->texture.loadFromFile("./res/" + imgFile)) 
            std::cout << "Erreur chargement texture de CellSurface" << std::endl;
    }
    void CellSurface::setSpriteLocation (int index, int x, int y)
    {
        
    }
    void CellSurface::setSpriteTexture (int index, const Tile& tex)
    {
        
    }
    void CellSurface::draw (sf::RenderTarget& target, sf::RenderStates states) const
    {
        
    }
    void CellSurface::initCells (int count)
    {
        
    }
}