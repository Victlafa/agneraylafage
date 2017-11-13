/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PoisonCommand.h"
#include "state/Cell.h"
#include <iostream>

using namespace state;

namespace engine
{
    PoisonCommand::PoisonCommand (int cell, int creatures) : cell(cell), creatures(creatures) {}
    
    bool PoisonCommand::isPoisoned (state::State& state){
        CellState etatCell = ((Cell)*state.getGrid()->getByNumber(cell)).getCellState();
        if (etatCell == CellState::POISONED)
            return true;
        else
            return false;
    }
    
    void PoisonCommand::killCreatures (state::State& state){
        srand(time(NULL));
        int nbCreaTuees = 0;
        
        if (isPoisoned(state))
        {
            int tirageJeu = rand()%6 + 1;
            int nbCrea = state.getCharacters()->getByNumber(creatures)->getCreaturesNbr();
            for (int i = 0; i < nbCrea; i++)
            {
                if (tirageJeu > rand()%6 + 1)
                    nbCreaTuees += 1;
            }
            
            state.getCharacters()->getByNumber(creatures)->setCreaturesNbr(nbCrea - nbCreaTuees);
        }
        
        else
            std::cout << "La cellule n'est pas empoisonnee, pas d'effet" << std::endl;
        
        
    }
    
    CommandTypeID PoisonCommand::getTypeID () const {return CommandTypeID::POISON;}
    void PoisonCommand::execute (state::State& state){
        killCreatures(state);
    }
    // Setters and Getters
    int PoisonCommand::getCell() const{return cell;}
    void PoisonCommand::setCell(int cell){this->cell = cell;}
    int PoisonCommand::getCreatures() const{return creatures;}
    void PoisonCommand::setCreatures(int creatures){this->creatures = creatures;}
}
