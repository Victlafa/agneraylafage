#include "State.h"
#include "Player.h"
#include "ElementTab.h"
#include "Cell.h"
#include "CreaturesGroup.h"

namespace state
{

    State::State (){
        this->totalCellNbr = 29;
        this->grid = std::unique_ptr<ElementTab>(new ElementTab(TypeID::CELL));
        this->characters = std::unique_ptr<ElementTab>(new ElementTab(TypeID::CREATURESGROUP));
        this->player1 = std::unique_ptr<Player>(new Player());
        this->player2 = std::unique_ptr<Player>(new Player());
    }
    
    State::~State (){ }
    
    // Setters and Getters
    const std::unique_ptr<ElementTab>& State::getGrid() const{
        return grid;
    }
    
    const std::unique_ptr<ElementTab>& State::getCharacters () const{
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