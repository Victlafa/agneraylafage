/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "StateTileSet.h"

namespace render
{
    StateTileSet::StateTileSet () 
    { this->chars = std::vector<Tile>(); }
    
    int StateTileSet::getCellWidth () const
    {
        if (chars.size() != 0)
            return this->chars[0].getWidth();
        else
            return -1;
    }
    
    int StateTileSet::getCellHeight () const
    {
        if (chars.size() != 0)
            return this->chars[0].getHeight();
        else
            return -1;
    }
    
    const std::string StateTileSet::getImageFile () const
    {
        // PENSER A DEFINIR UNE IMAGE POUR LES ETATS !!
    }
    
    const Tile& StateTileSet::getCharTile (char c) const
    {
        // PENSER A DEFINIR UNE IMAGE POUR LES ETATS !!
    }
}