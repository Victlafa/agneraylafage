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
        
    }
    
    CommandTypeID MoveCommand::getTypeID () const { return CommandTypeID::MOVE; }
    
    void MoveCommand::execute (state::State& state) {
        
        // On verifie si la case de destination est adjacente à celle de depart
        bool verif1 = ((finalPos[0] == initPos[0] - 1) && finalPos[1] == initPos[1]);
        bool verif2 = ((finalPos[0] == initPos[0] - 1) && (finalPos[1] == initPos[1] + 1));
        bool verif3 = (finalPos[0] == initPos[0] && (finalPos[1] == initPos[1] + 1));
        bool verif4 = ((finalPos[0] == initPos[0] + 1) && finalPos[1] == initPos[1]);
        bool verif5 = ((finalPos[0] == initPos[0] + 1) && (finalPos[1] == initPos[1] - 1));
        bool verif6 = (finalPos[0] == initPos[0] && (finalPos[1] == initPos[1] - 1));
        
        if (verif1 || verif2 || verif3 || verif4 || verif5 || verif6)
        {
            
        }
        else
            throw std::runtime_error("La case de destination doit etre adjacente à celle de depart !");
        
            
    }
    
    
    // Setters and Getters
    int getInitPos() const {return initPos;}
    void setInitPos(int initPos) {this->initPos = initPos};
    int getFinalPos() const {return finalPos;}
    void setFinalPos(int finalPos) {this->initPos = initPos};
    
}
