#include "State.h"
#include "Player.h"
#include "ElementTab.h"
#include "Cell.h"
#include "CreaturesGroup.h"

namespace state
{

    State::State (){
        this->totalCellNbr = 29;
        this->grid = new ElementTab();
        this->characters = new ElementTab();
        this->player = *(new Player());
    }
    
    State::~State (){
    }
    
    // Setters and Getters
    ElementTab* State::getGrid() const{
        return grid;
    }
    
    ElementTab* State::getCharacters () const{
        return characters;
    }
    
    int State::getCellNbr () const{
        return totalCellNbr;
    }
    
    const Player& State::getPlayer() const{
        return player;
    }
    
    void State::setPlayer(const Player& player){
        this->player = player;
    }
    
};