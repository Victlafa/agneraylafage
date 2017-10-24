/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "state.h"
#include "CharsTileSet.h"


namespace render
{
    CharsTileSet::CharsTileSet (){}
    
    int CharsTileSet::getCellWidth () const
    {
        if (this->creaturesPlayer1.size() != 0)
            return this->creaturesPlayer1[0].getWidth();
        else
            return -1;
    }
    
    int CharsTileSet::getCellHeight () const
    {
        if (this->creaturesPlayer1.size() != 0)
            return this->creaturesPlayer1[0].getHeight();
        else
            return -1;
    }
    
    const std::string CharsTileSet::getImageFile () const{
        return "./res/groupes.png";
    }
    
    const Tile& CharsTileSet::getTile (const state::ElementTab& elemTab) const
    {
        Tile tuile;
        
        if (elemTab.getTabType() == state::TypeID::CREATURESGROUP) {
            tuile = Tile(0,0,100,100);
        } else
            tuile = Tile();
        
        return tuile;
    }
}

