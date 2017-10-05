#include "State.h"
#include "Player.h"
#include "ElementTab.h"
#include "Cell.h"
#include "CreaturesGroup.h"

namespace state
{

    State::State (){
        this->totalCellNbr = 7*7;
        this->grid = new ElementTab();
        this->characters = new ElementTab();
        this->player = *(new Player());
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