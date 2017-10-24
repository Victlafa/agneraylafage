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
    
    const Tile& CharsTileSet::getTile (int index, int player = 1) const
    {
        if (player == 1)
            return this->creaturesPlayer1[index];
        else if (player == 2)
            return this->creaturesPlayer2[index];
        else
            return *(new Tile());
            
    }
}

