/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SpecialCellCommand.h"

namespace engine
{
    SpecialCellCommand::SpecialCellCommand (int init_i, int init_j, int final_i, int final_j, int player) : initPos(2), finalPos(2)
    {
        initPos[0] = init_i;
        initPos[1] = init_j;
        finalPos[0] = final_i;
        finalPos[1] = final_j;
        this->player = player;
        fight.reset(new Fight(init_i,init_j,final_i,final_j,player));
        
    }
    
    bool SpecialCellCommand::isSpecial (state::State& state)
    {
        // On verifie si la cellule est speciale ou pas
        int elemtype = (int)state.getGrid()->get(initPos[0],initPos[1])->getElemType();
        if (elemtype >= 8 && elemtype <= 11)
            return true;
        else
            return false;
    }
    
    CommandTypeID SpecialCellCommand::getTypeID () const { return CommandTypeID::SPECIAL; }
    
    void SpecialCellCommand::execute (state::State& state)
    {}
    
    // Setters and Getters
    const std::vector<int>& SpecialCellCommand::getInitPos() const { return initPos; }
    void SpecialCellCommand::setInitPos(const std::vector<int>& initPos) {
        this->initPos[0] = initPos[0];
        this->initPos[1] = initPos[1];
    }
    const std::vector<int>& SpecialCellCommand::getFinalPos() const { return finalPos; }
    void SpecialCellCommand::setFinalPos(const std::vector<int>& finalPos)
    {
        this->finalPos[0] = finalPos[0];
        this->finalPos[1] = finalPos[1];
    }
    int SpecialCellCommand::getPlayer() const { return player; }
    void SpecialCellCommand::setPlayer(int player) { this->player = player; }
    
    void SpecialCellCommand::skyPower ()
    {
        
    }
    
    void SpecialCellCommand::sugarPower () {}
    void SpecialCellCommand::bbqPoolPower () {}
}