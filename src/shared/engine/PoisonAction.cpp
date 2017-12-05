/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PoisonAction.h"
#include "state/Cell.h"
#include <iostream>

using namespace state;

namespace engine
{
    PoisonAction::PoisonAction (int i_cell, int j_cell) : cell(2) {
        cell[0] = i_cell;
        cell[1] = j_cell;
    }
    
    bool PoisonAction::isPoisoned (state::State& state){
        bool isPoison = state.getGrid()->isPoisoned(cell[0],cell[1]);
        if (isPoison)
            return true;
        else
            return false;
    }
    
    void PoisonAction::killCreatures (state::State& state){
        srand(time(NULL));
        int nbCreaTuees = 0;
        
        if (isPoisoned(state)) {
            int tirageJeu = rand() % 6 + 1;
            int nbCrea = state.getCharacters()->get(cell[0], cell[1])->getCreaturesNbr();
            for (int i = 0; i < nbCrea; i++) {
                if (tirageJeu > rand() % 6 + 1)
                    nbCreaTuees += 1;
            }

            state.getCharacters()->get(cell[0], cell[1])->setCreaturesNbr(nbCrea - nbCreaTuees);
        }
        else
            std::cout << "La cellule n'est pas empoisonnee, pas d'effet" << std::endl;
         
    }
    
    void PoisonAction::apply (state::State& state){
        killCreatures(state);
    }
    
    void PoisonAction::undo (state::State& etat)
    {
        
    }
    
    // Setters and Getters
    const std::vector<int>& PoisonAction::getCell() const{return cell;}
    void PoisonAction::setCell(const std::vector<int>& cell){this->cell = cell;}
}
