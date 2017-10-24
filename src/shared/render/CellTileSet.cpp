/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "state.h"
#include "CellTileSet.h"
//#include "state/ElementTab.h"


namespace render
{
    CellTileSet::CellTileSet () { cells = std::vector<Tile>(); }
    
    CellTileSet::~CellTileSet()
    {
        
    }
    
    // Renvoie l'épaisseur d'une cellule si la liste est non vide. Renvoie -1 si la liste est vide.
    int CellTileSet::getCellWidth () const
    {
        if (cells.size() != 0)
            return this->cells[0].getWidth();
        else
            return -1;
    }
    
    // Renvoie la hauteur d'une cellule si la liste est non vide. Renvoie -1 si la liste est vide.
    int CellTileSet::getCellHeight () const
    {
        if (cells.size() != 0)
            return this->cells[0].getHeight();
        else
            return -1;
    }
    
    const std::string CellTileSet::getImageFile () const
    {
        return "./res/hexa.png";
    }
    
    const Tile& CellTileSet::getTile (const state::ElementTab& elemTab) const
    {
        Tile tuile;
        
        if (elemTab.getTabType() == state::TypeID::CELL) {
            tuile = Tile(0,0,102,122);
        } else
            tuile = Tile();
        
        return tuile;
    }
}


