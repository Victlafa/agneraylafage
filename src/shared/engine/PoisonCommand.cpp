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
    PoisonCommand::PoisonCommand (int i_cell, int j_cell) : cell(2) {
        cell[0] = i_cell;
        cell[1] = j_cell;
    }
    
    bool PoisonCommand::isPoisoned (state::State& state){
        CellState etatCell = ((Cell)*state.getGrid()->get(cell[0],cell[1])).getCellState();
        std::cout << "etat de la cellule : " << etatCell << std::endl;
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
            int nbCrea = state.getCharacters()->get(cell[0],cell[1])->getCreaturesNbr();
            for (int i = 0; i < nbCrea; i++)
            {
                if (tirageJeu > rand()%6 + 1)
                    nbCreaTuees += 1;
            }
            
            state.getCharacters()->get(cell[0],cell[1])->setCreaturesNbr(nbCrea - nbCreaTuees);
        }
        
        else
            std::cout << "La cellule n'est pas empoisonnee, pas d'effet" << std::endl;
        
        
    }
    
    CommandTypeID PoisonCommand::getTypeID () const {return CommandTypeID::POISON;}
    void PoisonCommand::execute (state::State& state){
        killCreatures(state);
    }
    // Setters and Getters
    const std::vector<int>& PoisonCommand::getCell() const{return cell;}
    void PoisonCommand::setCell(const std::vector<int>& cell){this->cell = cell;}
}
