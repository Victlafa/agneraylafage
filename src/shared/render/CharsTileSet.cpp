/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "state.h"
#include "CharsTileSet.h"


namespace render
{
    CharsTileSet::CharsTileSet (){
        
        creatures = new Tile*[5];
        
        for (int i = 0; i < 5; i++)
        {
            creatures[i] = new Tile[5];
            
            for (int j = 0; j < 5; j++)
            {
                creatures[i][j] = Tile(50*(i+1),50*(j+1),100,100);
            }
        }
    }
    
    int CharsTileSet::getCellWidth () const
    {
        return this->creatures[0][0].getWidth();
    }
    
    int CharsTileSet::getCellHeight () const
    {
        return this->creatures[0][0].getHeight();
    }
    
    const std::string CharsTileSet::getImageFile () const{
        return "./res/groupes.png";
    }
    
    const Tile& CharsTileSet::getTile (const state::Element& elem) const
    {
        
        if (elem.getElemType() == state::TypeID::CREATURESGROUP)
        {
            const state::CreaturesGroup group = (const state::CreaturesGroup)elem;
            
            if (group.getCreaturesType() == state::CreaturesID::COOKER)
                return creatures[0][group.getCreaturesNbr()];
            else if (group.getCreaturesType() == state::CreaturesID::BLACKSMITH)
                return creatures[1][group.getCreaturesNbr()];
            else if (group.getCreaturesType() == state::CreaturesID::LUMBERJACK)
                return creatures[2][group.getCreaturesNbr()];
            else if (group.getCreaturesType() == state::CreaturesID::MINER)
                return creatures[3][group.getCreaturesNbr()];
            else
                return *(new Tile(-1,-1,-1,-1));
                
        }
        
        else
            return *(new Tile(-1,-1,-1,-1));
        
    }
}

