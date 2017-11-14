#include "State.h"
#include "Player.h"
#include "ElementTab.h"
#include "Cell.h"
#include "CreaturesGroup.h"
#include <iostream>

namespace state
{

    State::State(){
        //std::cout << "Appel constructeur de State" << std::endl;
        totalCellNbr = 29;
        grid.reset(new ElementTab(TypeID::CELL));
        characters.reset(new ElementTab(TypeID::CREATURESGROUP));
        player1.reset(new Player());
        player2.reset(new Player());
    }
    
    State::~State (){ 
        //std::cout << "Appel destructeur de State" << std::endl;
    }
    
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
    
    void State::reset()
    {
        grid.reset(new ElementTab(TypeID::CELL));
        characters.reset(new ElementTab(TypeID::CREATURESGROUP));
        player1.reset(new Player());
        player2.reset(new Player());
    }
    
    void State::poisonCell(bool poison, int i, int j)
    {
        if (poison)
        {
            ((Cell)*grid->get(i,j).get()).setCellState(CellState::POISONED);
            std::cout << "etat de la cellule : " << ((Cell)*grid->get(i,j).get()).getCellState() << std::endl;
            std::cout << "La case (" << i << "," << j << ") a ete empoisonnee\n" << std::endl;
        }
        else
            ((Cell)*grid->get(i,j).get()).setCellState(CellState::NORMAL);
    }
    
};