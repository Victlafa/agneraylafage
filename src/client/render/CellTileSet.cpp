/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include "state.h"
#include "CellTileSet.h"
#include <iostream>
//#include "state/ElementTab.h"


namespace render
{
    CellTileSet::CellTileSet () 
    { 
        cells = std::vector<Tile>(); 
        
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
        // Erreur de segmentation quand on appelle getElemType !
        std::cout << "getTile" << std::endl;
        if (elem.getElemType() == state::TypeID::CELL)
        {
            const state::Cell cellule = (const state::Cell)elem;
            
            std::cout << "Cell type : " << cellule.getCellType() << std::endl;
            
            if (cellule.getCellType() == state::CellTypeID::SIMPLE)
            {
                switch(((state::SimpleCell) cellule).getSimpleCellType()){
                    case state::SimpleCellID::SAND :
                        return this->cells[0];
                        break;
                    case state::SimpleCellID::GRASS :
                        return this->cells[1];
                        break;
                    case state::SimpleCellID::DIRT :
                        return this->cells[2];
                        break;
                    default :
                        return *(new Tile(-1,-1,-1,-1));
                        std::cout << "erreur attribution CellTileSet" << std::endl;
                        break;
                }

            }

            else if (cellule.getCellType() == state::CellTypeID::SPECIAL)
            {
                switch(((state::SpecialCell) cellule).getSpecialCellType()){
                    case state::SpecialCellID::BARBECUE :
                        return this->cells[3];
                        break;
                    case state::SpecialCellID::SKY :
                        return this->cells[4];
                        break;
                    case state::SpecialCellID::POOL :
                        return this->cells[5];
                        break;
                    case state::SpecialCellID::CANDY :
                        return this->cells[6];
                        break;
                    default :
                        return *(new Tile(-1,-1,-1,-1));
                        std::cout << "erreur attribution CellTileSet" << std::endl;
                        break;
                }
                
            }
            else
            {
                return *(new Tile(-1,-1,-1,-1));
                std::cout << "bug" << std::endl;
            }
        }
        else
        {
            return *(new Tile(-1,-1,-1,-1));
            std::cout << "bug2" << std::endl;
        }
    }

    const Tile& CellTileSet::getTile (const std::unique_ptr<state::Element>& elem) const
    {
        // Erreur de segmentation quand on appelle getElemType !
        std::cout << "getTilebis";
        
        if (elem->getElemType() == state::TypeID::CELL)
        {
            //const state::Cell cellule = (const state::Cell)elem;
            std::cout << " getCellType : " << ( (const state::Cell)(*elem) ).getCellType();
            
            if (( (const state::Cell)(*elem) ).getCellType() == state::CellTypeID::SIMPLE)
            {
                std::cout << " getSimpleCellType : " << ( (const state::SimpleCell)(*elem) ).getSimpleCellType() << std::endl;
                switch(( (state::SimpleCell)(*elem) ).getSimpleCellType()){
                    case state::SimpleCellID::SAND :
                        return this->cells[0];
                        break;
                    case state::SimpleCellID::GRASS :
                        return this->cells[1];
                        break;
                    case state::SimpleCellID::DIRT :
                        return this->cells[2];
                        break;
                    default :
                        return *(new Tile(-1,-1,-1,-1));
                        std::cout << "erreur attribution CellTileSet" << std::endl;
                        break;
                }

            }
            else if (( (const state::Cell)(*elem) ).getCellType() == state::CellTypeID::SPECIAL)
            {
                switch(( (state::SpecialCell)(*elem) ).getSpecialCellType()){
                    case state::SpecialCellID::BARBECUE :
                        return this->cells[3];
                        break;
                    case state::SpecialCellID::SKY :
                        return this->cells[4];
                        break;
                    case state::SpecialCellID::POOL :
                        return this->cells[5];
                        break;
                    case state::SpecialCellID::CANDY :
                        return this->cells[6];
                        break;
                    default :
                        return *(new Tile(-1,-1,-1,-1));
                        std::cout << "erreur attribution CellTileSet" << std::endl;
                        break;
                }
                
            }
            else
            {
                return *(new Tile(-1,-1,-1,-1));
                std::cout << "bug" << std::endl;
            }
        }
        
        else
        {
            return *(new Tile(-1,-1,-1,-1));
            std::cout << "bug2" << std::endl;
        }
    }
}


