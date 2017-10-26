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
        
        cells.push_back(Tile(71,81,102,122));
        cells.push_back(Tile(191,81,102,122));
        cells.push_back(Tile(311,81,102,122));
        cells.push_back(Tile(71,221,102,122));
        cells.push_back(Tile(191,221,102,122));
        cells.push_back(Tile(311,221,102,122));
        cells.push_back(Tile(431,221,102,122));
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
        // Erreur de segementation quand on appelle getElemType !
        if (elem.getElemType() == state::TypeID::CELL)
        {
            const state::Cell cellule = (const state::Cell)elem;
            //const state::Cell cellule = (const state::Cell)elem;

            if (cellule.getCellType() == state::CellTypeID::SIMPLE)
            {
                const state::SimpleCell simpleCellule = (const state::SimpleCell)cellule;
                
                if (simpleCellule.getSimpleCellType() == state::SimpleCellID::SAND)
                    return this->cells[0];
                else if (simpleCellule.getSimpleCellType() == state::SimpleCellID::GRASS)
                    return this->cells[1];
                else if (simpleCellule.getSimpleCellType() == state::SimpleCellID::DIRT)
                    return this->cells[2];
                else
                    return *(new Tile(-1,-1,-1,-1));
            }
            
            else if (cellule.getCellType() == state::CellTypeID::SPECIAL)
            {
                const state::SpecialCell specialCellule = (const state::SpecialCell)cellule;
                
                if (specialCellule.getSpecialCellType() == state::SpecialCellID::BARBECUE)
                    return this->cells[3];
                else if (specialCellule.getSpecialCellType() == state::SpecialCellID::SKY)
                    return this->cells[4];
                else if (specialCellule.getSpecialCellType() == state::SpecialCellID::POOL)
                    return this->cells[5];
                else if (specialCellule.getSpecialCellType() == state::SpecialCellID::CANDY)
                    return this->cells[6];
                else
                    return *(new Tile(-1,-1,-1,-1));
            }
            
            else
                return *(new Tile(-1,-1,-1,-1));
        }
        
        else
            return *(new Tile(-1,-1,-1,-1));
        
        
    }
}


