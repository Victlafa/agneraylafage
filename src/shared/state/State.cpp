#include "State.h"
#include "Player.h"
#include "ElementTab.h"
#include "Cell.h"
#include "CreaturesGroup.h"
#include <iostream>

namespace state
{

    State::State(){
        totalCellNbr = 29;
        grid.reset(new ElementTab(TypeID::CELL));
        characters.reset(new ElementTab(TypeID::CREATURESGROUP));
        player1.reset(new Player());
        player2.reset(new Player());
    }
    
    State::~State (){}
    
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
        if (number == 1)
            return player1;
        else if (number == 2)
            return player2;
        else
            return NULL;
    }
    
    void State::reset(CreaturesID typeCreatures)
    {
        grid.reset(new ElementTab(TypeID::CELL));
        characters.reset(new ElementTab(TypeID::CREATURESGROUP));
        player1.reset(new Player(typeCreatures));
        int creaEnnemi = rand()%4 + 1;
        player2.reset(new Player((CreaturesID)creaEnnemi));
        
    }
   
    
};