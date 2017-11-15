/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "state.h"
#include "StateTileSet.h"

namespace render
{
    StateTileSet::StateTileSet () 
    { 
        chars = std::vector<Tile>();
        
        //Les coordonnées suivantes ne correspondent à rien, elle sont là pour que ça compile
        chars.push_back(Tile(71,81,102,122));
        chars.push_back(Tile(191,81,102,122));
    }
    
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
        return "Definir une image pour les etats !";
    }
    
    const Tile& StateTileSet::getCharTile (char c) const
    {
        //arrangé pour compilation, ne signifie rien
        if (c=='c')
            return *(new Tile(0,0,100,100));
        else
            return *(new Tile());
    }
    
    const Tile& StateTileSet::getTile (const state::Element& elem) const
    {
        Tile* tuile = new Tile();
        return *tuile;
    }
    
    const Tile& StateTileSet::getTile (const std::unique_ptr<state::Element>& elem) const
    {
        Tile* tuile = new Tile();
        return *tuile;
    }
}