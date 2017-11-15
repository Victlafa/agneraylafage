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
<<<<<<< HEAD
    const std::unique_ptr<ElementTab>& State::getGrid() const{
=======
   /* const ElementTab& State::getGrid() const{
>>>>>>> c836bcfb3b8edfe27cda0d2258311ea44d93de9c
        return grid;
    }*/
    
<<<<<<< HEAD
    const std::unique_ptr<ElementTab>& State::getCharacters () const{
=======
    ElementTab& State::getGrid() {
        return grid;
    }
    
    /*const ElementTab& State::getCharacters () const{
        return characters;
    }*/
    
    ElementTab& State::getCharacters () {
>>>>>>> c836bcfb3b8edfe27cda0d2258311ea44d93de9c
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