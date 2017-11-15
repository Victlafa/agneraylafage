#include "State.h"
#include "Player.h"
#include "ElementTab.h"
#include "Cell.h"
#include "CreaturesGroup.h"
#include <iostream>

namespace state
{

    State::State(){
        this->totalCellNbr = 29;
        this->grid.init(TypeID::CELL);
        this->characters.init(TypeID::CREATURESGROUP);
        this->player1.reset(new Player());
        this->player2.reset(new Player());
    }
    
    State::~State (){ 
        std::cout << "Appel destructeur de State" << std::endl;
    }
    
    // Setters and Getters
   /* const ElementTab& State::getGrid() const{
        return grid;
    }*/
    
    ElementTab& State::getGrid() {
        return grid;
    }
    
    /*const ElementTab& State::getCharacters () const{
        return characters;
    }*/
    
    ElementTab& State::getCharacters () {
        return characters;
    }
    
    int State::getCellNbr () const{
        return totalCellNbr;
    }
    
    const std::unique_ptr<Player>& State::getPlayer(int number) const{
        if (number == 2)
            return player2;
        else
            return player1;
    }
    
};