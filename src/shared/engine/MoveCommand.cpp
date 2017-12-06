/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MoveCommand.h"
#include <iostream>
#include "MoveAction.h"

namespace engine{
    
    MoveCommand::MoveCommand (int init_i, int init_j, int final_i, int final_j, int player) : initPos(2), finalPos(2) {
        initPos[0] = init_i;
        initPos[1] = init_j;
        finalPos[0] = final_i;
        finalPos[1] = final_j;
        this->player = player;
        
    }
    
    CommandTypeID MoveCommand::getTypeID () const { return CommandTypeID::MOVE; }
    
    void MoveCommand::execute (std::stack<std::shared_ptr<Action>>& pile, state::State& state) {
        
//        // On verifie si la case de destination est adjacente à celle de departs
//        bool verif1 = ((finalPos[0] == initPos[0] - 1) && finalPos[1] == initPos[1]);
//        bool verif2 = ((finalPos[0] == initPos[0] - 1) && (finalPos[1] == initPos[1] + 1));
//        bool verif3 = (finalPos[0] == initPos[0] && (finalPos[1] == initPos[1] + 1));
//        bool verif4 = ((finalPos[0] == initPos[0] + 1) && finalPos[1] == initPos[1]);
//        bool verif5 = ((finalPos[0] == initPos[0] + 1) && (finalPos[1] == initPos[1] - 1));
//        bool verif6 = (finalPos[0] == initPos[0] && (finalPos[1] == initPos[1] - 1));
//        
//        if (verif1 || verif2 || verif3 || verif4 || verif5 || verif6)
//        {
//            
//        }
//        else
//            throw std::runtime_error("La case de destination doit etre adjacente à celle de depart !");
        
        
            
    }
    
    // Setters and Getters
    const std::vector<int>& MoveCommand::getInitPos() const { return initPos; }
    void MoveCommand::setInitPos(const std::vector<int>& initPos) { this->initPos = initPos; }
    const std::vector<int>& MoveCommand::getFinalPos() const { return finalPos; }
    void MoveCommand::setFinalPos(const std::vector<int>& finalPos) {this->finalPos = finalPos; }
    
}
