/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PoisonAction.h"
#include "state/Cell.h"
#include "state/CreaturesGroup.h"
#include <iostream>

using namespace state;

namespace engine
{
    PoisonAction::PoisonAction (int i_cell, int j_cell, state::ID typeCreatures, int player) : cell(2) {
        cell[0] = i_cell;
        cell[1] = j_cell;
        nbrCreaBegin = -1;
        typeCreaBegin = typeCreatures;
        playerBegin = player;
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
        
        nbrCreaBegin = state.getCharacters()->get(cell[0], cell[1])->getCreaturesNbr();
        typeCreaBegin = state.getCharacters()->get(cell[0], cell[1])->getElemType();
        
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
    
    void PoisonAction::undo (state::State& state)
    {
        if(state.getCharacters()->get(cell[0], cell[1])->getCreaturesNbr()==0){
           std::unique_ptr<state::Element> crea(new CreaturesGroup(this->typeCreaBegin, this->nbrCreaBegin, state.getCharacters()->get(cell[0],cell[1])->getPlayer()));
           state.getCharacters()->set(crea.get(),cell[0],cell[1]);
        }
        else
            state.getCharacters()->get(cell[0], cell[1])->setCreaturesNbr(nbrCreaBegin);
    }
    
    // Setters and Getters
    const std::vector<int>& PoisonAction::getCell() const{return cell;}
    void PoisonAction::setCell(const std::vector<int>& cell){this->cell = cell;}
}
