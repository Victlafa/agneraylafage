/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MoveCommand.h"
#include <iostream>

namespace engine{
    
    MoveCommand::MoveCommand() {}
    MoveCommand::MoveCommand (int init_i, int init_j, int final_i, int final_j, int player) : initPos(2), finalPos(2) {
        initPos[0] = init_i;
        initPos[1] = init_j;
        finalPos[0] = final_i;
        finalPos[1] = final_j;
        this->player = player;
        fight.reset(new Fight(init_i,init_j,final_i,final_j,player));
        
    }
    
    CommandTypeID MoveCommand::getTypeID () const { return CommandTypeID::MOVE; }
    
    void MoveCommand::execute (state::State& state) {
        
        // On verifie si la case de destination est adjacente à celle de depart
        if (verifyProximity())
        {
            // Si la case de destination est occupée par l'adversaire, on engage un combat
            if (state.getCharacters()->isOccupiedByOpp(finalPos[0], finalPos[1], state.getPlayer(player).get())) {
                std::cout << "MoveCommand::execute - Un combat commence !" << std::endl;
                fight->execute(state);
                state.getCharacters()->moveElement(initPos[0], initPos[1], finalPos[0], finalPos[1], fight->getWinner());
            } 
            else
            {
                std::cout << "MoveCommand::execute - Il y a déplacement sans combat !" << std::endl;
                // S'il n'y a pas combat on procede directement au deplacement
                state.getCharacters()->moveElement(initPos[0], initPos[1], finalPos[0], finalPos[1], 0);
            }
                

            // On associe la case d'arrivée au joueur gagnant
            if (fight->getWinner() == 1 || fight->getWinner() == 2) {
                //std::cout << "MoveCommand::execute - Joueur gagnant : " << state.getPlayer(fight->getWinner()).get() << std::endl;
                std::cout << "MoveCommand::execute - Joueur gagnant du combat : " << fight->getWinner() << std::endl;
                state.getCharacters()->get(finalPos[0], finalPos[1])->setPlayer(state.getPlayer(fight->getWinner()).get());
            }
        }
        else
            throw std::runtime_error("La case de destination doit etre adjacente à celle de depart !");
        
            
    }
    
    bool MoveCommand::verifyProximity ()
    {
        bool verif1 = ((finalPos[0] == initPos[0] - 1) && finalPos[1] == initPos[1]);
        bool verif2 = ((finalPos[0] == initPos[0] - 1) && (finalPos[1] == initPos[1] + 1));
        bool verif3 = (finalPos[0] == initPos[0] && (finalPos[1] == initPos[1] + 1));
        bool verif4 = ((finalPos[0] == initPos[0] + 1) && finalPos[1] == initPos[1]);
        bool verif5 = ((finalPos[0] == initPos[0] + 1) && (finalPos[1] == initPos[1] - 1));
        bool verif6 = (finalPos[0] == initPos[0] && (finalPos[1] == initPos[1] - 1));
        
        if (verif1 || verif2 || verif3 || verif4 || verif5 || verif6)
            return true;
        else
            return false;
    }
    
    // Setters and Getters
    const std::shared_ptr<Fight>& MoveCommand::getFight() const {return fight;}
    void MoveCommand::setFight(const std::shared_ptr<Fight>& fight) {this->fight = fight;}
    const std::vector<int>& MoveCommand::getInitPos() const {return initPos;}
    void MoveCommand::setInitPos(const std::vector<int>& initPos) {this->initPos = initPos;}
    const std::vector<int>& MoveCommand::getFinalPos() const {return finalPos;}
    void MoveCommand::setFinalPos(const std::vector<int>& finalPos) {this->finalPos = finalPos;}
    int MoveCommand::getPlayer() const {return player;}
    void MoveCommand::setPlayer(int player) {this->player = player;}
    
}
