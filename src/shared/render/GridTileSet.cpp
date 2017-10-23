/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GridTileSet.h"
#include "state/ElementTab.h"

namespace render
{
    GridTileSet::GridTileSet () { cells = std::vector<Tile>(); }
    
    // Renvoie l'épaisseur d'une cellule si la liste est non vide. Renvoie -1 si la liste est vide.
    int GridTileSet::getCellWidth () const
    {
        if (cells.size() != 0)
            return this->cells[0].getWidth();
        else
            return -1;
    }
    
    // Renvoie la hauteur d'une cellule si la liste est non vide. Renvoie -1 si la liste est vide.
    int GridTileSet::getCellHeight () const
    {
        if (cells.size() != 0)
            return this->cells[0].getHeight();
        else
            return -1;
    }
    
    const std::string GridTileSet::getImageFile () const
    {
        return "./res/hexa.png";
    }
    
    const Tile& GridTileSet::getTile (const state::ElementTab& elemTab) const
    {
        if (elemTab.getTabType() == state::TypeID::CELL)
        {
            Tile tuile();
            return tuile;
        }
        else
            return NULL;
    }
}


