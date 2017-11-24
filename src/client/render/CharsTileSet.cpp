#include "state.h"
#include "CharsTileSet.h"
#include <iostream>


namespace render
{
    CharsTileSet::CharsTileSet (){
        
        creatures = new Tile*[5];
        
        for (int i = 0; i < 5; i++)
        {
            creatures[i] = new Tile[5];
            
            for (int j = 0; j < 5; j++)
            {
                creatures[i][j] = Tile(50*(2*i+1),50*(2*j+1),100,100);
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
        //std::cout << "charstileset gettile getelemtype : " << elem.getElemType() << std::endl;
        switch(elem.getElemType()){
            case state::ID::COOKER :
                return creatures[0][elem.getCreaturesNbr()-1];
                break;
            case state::ID::BLACKSMITH :
                return creatures[1][elem.getCreaturesNbr()-1];
                break;
            case state::ID::LUMBERJACK :
                return creatures[2][elem.getCreaturesNbr()-1];
                break;
            case state::ID::MINER :
                return creatures[3][elem.getCreaturesNbr()-1];
                break;
            default :
                return creatures[4][0];
                //return *(new Tile(-1,-1,-1,-1));
                //std::cout << "erreur attribution CharsTileSet" << std::endl;
                break;
        }
        /*
        if (elem.getElemType() == state::TypeID::CREATURESGROUP)
        {
            state::CreaturesGroup group = (const state::CreaturesGroup)elem;
            
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
        */
        
    }

    const Tile& CharsTileSet::getTile (const std::unique_ptr<state::Element>& elem) const
    {
        //if(elem==NULL) std::cout << "charstileset gettile gettypeID : NULL" << std::endl;
        //std::cout << "charstileset gettile getelemtype : " << elem->getElemType() << std::endl;
        switch(elem->getElemType()){
            case state::ID::COOKER :
                return creatures[0][elem->getCreaturesNbr()-1];
                break;
            case state::ID::BLACKSMITH :
                return creatures[1][elem->getCreaturesNbr()-1];
                break;
            case state::ID::LUMBERJACK :
                return creatures[2][elem->getCreaturesNbr()-1];
                break;
            case state::ID::MINER :
                return creatures[3][elem->getCreaturesNbr()-1];
                break;
            default :
                return creatures[4][4];
                //return *(new Tile(-1,-1,-1,-1));
                std::cout << "erreur attribution CharsTileSet" << std::endl;
                break;
        }
        /*
        if (elem->getElemType() == state::TypeID::CREATURESGROUP)
        {
            
            switch(( (const state::CreaturesGroup)(*elem) ).getCreaturesType()){
                case state::CreaturesID::BLACKSMITH :
                    return this->creatures[0][elem->getCreaturesNbr()];
                   break;
                case state::CreaturesID::COOKER :
                    return this->creatures[1][elem->getCreaturesNbr()];
                    break;
                case state::CreaturesID::LUMBERJACK :
                    return this->creatures[2][elem->getCreaturesNbr()];
                    break;
                case state::CreaturesID::MINER :
                    return this->creatures[3][elem->getCreaturesNbr()];
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
            std::cout << "bug2" << std::endl;
        }*/
    }
}

