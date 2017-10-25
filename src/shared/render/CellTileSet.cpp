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
    CellTileSet::CellTileSet () 
    { 
        cells = std::vector<Tile>(7); 
        for (int i = 0; i < 7; i++)
        {
            cells.push_back(Tile(71,81,102,122));
        }
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
    
    const Tile& CellTileSet::getTile (const state::Element& elem) const
    {
//        if (elem.getElemType() == state::TypeID::CELL)
//        {
//            state::Cell cellule = dynamic_cast<const state::Cell&>(elem);
//            
//            if (cellule.getCellType() == state::CellTypeID::SIMPLE)
//            {
//                state::SimpleCell simpleCellule = dynamic_cast<const state::SimpleCell&>(cellule);
//                
//                if (simpleCellule.getSimpleCellType() == state::SimpleCellID::SAND)
//                    return *(new Tile(71,81,102,122));
//                else
//                    return *(new Tile(-1,-1,-1,-1));
//            }
//            
//            else
//                return *(new Tile(-1,-1,-1,-1));
//        }
        
        return *(new Tile(71,81,102,122));
        
        
    }
}


