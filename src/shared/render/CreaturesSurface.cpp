/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CreaturesSurface.h"

namespace render
{
    void CreaturesSurface::loadTexture (const std::string& imgFile){
        if(!this->texture.loadFromFile("./res/hexa.png")) cout<< " erreur chargement text1"<<endl;
    }
    void CreaturesSurface::setSpriteLocation (int index, int x, int y);
    void CreaturesSurface::setSpriteTexture (int index, const Tile& tex);
    void CreaturesSurface::draw (sf::RenderTarget& target, sf::RenderStates states) const;
    void CreaturesSurface::initQuads (int count);
}