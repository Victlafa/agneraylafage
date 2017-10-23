/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Surface.h"

namespace render 
{
    void Surface::loadTexture (const std::string& imgFile);
    void Surface::setSpriteLocation (int index, int x, int y);
    void Surface::setSpriteTexture (int index, const Tile& tex);
    void Surface::draw (sf::RenderTarget& target, sf::RenderStates states) const;
    void Surface::initCells (int count);
    // Setters and Getters
    const CellDraw& Surface::getTraceCell() const;
    void Surface::setTraceCell(const CellDraw& traceCell);
}

