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
        //std::cout << "getTile" << std::endl;
        
        switch(elem.getElemType()){
            case state::ID::BARBECUE :
                return this->cells[3];
                break;
            case state::ID::CANDY :
                return this->cells[6];
                break;
            case state::ID::DIRT :
                return this->cells[2];
                break;
            case state::ID::GRASS :
                return this->cells[1];
                break;
            case state::ID::POOL :
                return this->cells[5];
                break;
            case state::ID::SAND :
                return this->cells[0];
                break;
            case state::ID::SKY :
                return this->cells[4];
                break;
            default :
                return *(new Tile(-1,-1,-1,-1));
                std::cout << "erreur attribution CellTileSet" << std::endl;
                break;
        }
        
    }

    const Tile& CellTileSet::getTile (const std::unique_ptr<state::Element>& elem) const
    {
        // Erreur de segmentation quand on appelle getElemType !
        //std::cout << "getTilebis";
        
        switch(elem->getElemType()){
            case state::ID::BARBECUE :
                return this->cells[3];
                break;
            case state::ID::CANDY :
                return this->cells[6];
                break;
            case state::ID::DIRT :
                return this->cells[2];
                break;
            case state::ID::GRASS :
                return this->cells[1];
                break;
            case state::ID::POOL :
                return this->cells[5];
                break;
            case state::ID::SAND :
                return this->cells[0];
                break;
            case state::ID::SKY :
                return this->cells[4];
                break;
            default :
                return *(new Tile(-1,-1,-1,-1));
                std::cout << "erreur attribution CellTileSet" << std::endl;
                break;
        }
        
    }
}


