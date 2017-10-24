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
    
    const Tile& CharsTileSet::getTile (const state::Element& elem) const
    {
        return *(new Tile(50,50,100,100));
        
//        if (elem.getElemType() == state::TypeID::CREATURESGROUP)
//        {
//            if (elem.getCreaturesNbr() == 1)
//                return *(new Tile(50,50,100,100));
//            else if (elem.getCreaturesNbr() == 2)
//                return *(new Tile(150,150,100,100));
//            else if (elem.getCreaturesNbr() == 3)
//                return *(new Tile(250,250,100,100));
//            else if (elem.getCreaturesNbr() == 4)
//                return *(new Tile(350,350,100,100));
//            else if (elem.getCreaturesNbr() == 5)
//                return *(new Tile(450,450,100,100));
//            else
//                return *(new Tile(-1,-1,-1,-1));
//                
//        }
//        
//        else
//            return *(new Tile(-1,-1,-1,-1));
    }
}

