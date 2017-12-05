/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MoveAction.h"
#include <iostream>

namespace engine{
    
    MoveAction::MoveAction() {}
    MoveAction::MoveAction (int init_i, int init_j, int final_i, int final_j, int player) : initPos(2), finalPos(2) {
        initPos[0] = init_i;
        initPos[1] = init_j;
        finalPos[0] = final_i;
        finalPos[1] = final_j;
        this->player = player;
        fight.reset(new Fight(init_i,init_j,final_i,final_j,player));
        
    }
    
    void MoveAction::apply (state::State& state) {

        // Si la case de destination est occupée par l'adversaire, on engage un combat
        if (state.getCharacters()->isOccupiedByOpp(finalPos[0], finalPos[1], state.getPlayer(player).get())) {
            std::cout << "MoveAction::apply - Un combat commence !" << std::endl;
            fight->apply(state);
            state.getCharacters()->moveElement(initPos[0], initPos[1], finalPos[0], finalPos[1], fight->getWinner());
        } 
        else
        {
            std::cout << "MoveAction::execute - Il y a déplacement sans combat !" << std::endl;
            // S'il n'y a pas combat on procede directement au deplacement
            state.getCharacters()->moveElement(initPos[0], initPos[1], finalPos[0], finalPos[1], 0);
        }


        // On associe la case d'arrivée au joueur gagnant
        if (fight->getWinner() == 1 || fight->getWinner() == 2) {
            //std::cout << "MoveCommand::execute - Joueur gagnant : " << state.getPlayer(fight->getWinner()).get() << std::endl;
            std::cout << "MoveAction::execute - Joueur gagnant du combat : " << fight->getWinner() << std::endl;
            state.getCharacters()->get(finalPos[0], finalPos[1])->setPlayer(state.getPlayer(fight->getWinner()).get());
        }
            
    }
    
    
    void undo (state::State& etat){};
    
    
    // Setters and Getters
    const std::shared_ptr<Fight>& MoveAction::getFight() const {return fight;}
    void MoveAction::setFight(const std::shared_ptr<Fight>& fight) {this->fight = fight;}
    const std::vector<int>& MoveAction::getInitPos() const {return initPos;}
    void MoveAction::setInitPos(const std::vector<int>& initPos) {this->initPos = initPos;}
    const std::vector<int>& MoveAction::getFinalPos() const {return finalPos;}
    void MoveAction::setFinalPos(const std::vector<int>& finalPos) {this->finalPos = finalPos;}
    int MoveAction::getPlayer() const {return player;}
    void MoveAction::setPlayer(int player) {this->player = player;}
    
}
