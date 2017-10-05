#include "State.h"
#include "Player.h"
#include "ElementTab.h"
#include "Cell.h"
#include "CreaturesGroup.h"

namespace state
{

    State::State (){
        this->totalCellNbr = 7*7;
        this->grid = new Cell[totalCellNbr];
        this->characters = new CreaturesGroup[totalCellNbr];
        int cpt;
        for(cpt=0; cpt<totalCellNbr; cpt++){
            characters[cpt] = NULL;
            if(cpt!=0 && cpt!=1 && cpt!=7 && cpt!=41 && cpt!=47 && cpt!=49){
                grid[cpt] = new Cell();
            }else{
                grid[cpt] = NULL;
            }
        }
        this->player = NULL;
    }
    
    State::~State (){
        delete this;
    }
    
    // Setters and Getters
    ElementTab* State::getGrid (){
        return grid;
    }
    
    ElementTab* State::getCharacters (){
        return characters;
    }
    
    int State::getCellNbr (){
        return totalCellNbr;
    }
    
    const Player& State::getPlayer() const{
        return player;
    }
    
    void State::setPlayer(const Player& player){
        this->player = player;
    }
    
};