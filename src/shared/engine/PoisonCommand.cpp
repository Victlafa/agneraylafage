/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PoisonCommand.h"
#include "state/Cell.h"
#include "PoisonAction.h"
#include <iostream>

using namespace state;

namespace engine
{
    PoisonCommand::PoisonCommand (int i_cell, int j_cell) : targetCell(2) {
        targetCell[0] = i_cell;
        targetCell[1] = j_cell;
    } 
    
    
    void PoisonCommand::execute (std::stack<std::shared_ptr<Action>>& pile, state::State& state){
        PoisonAction action(targetCell[0],targetCell[1]);
        action.apply(state);
    }
    
    
    // Setters and Getters
    CommandTypeID PoisonCommand::getTypeID () const {return CommandTypeID::POISON;}
    const std::vector<int>& PoisonCommand::getTargetCell() const { return targetCell;}
    void PoisonCommand::setTargetCell(const std::vector<int>& targetCell) {this->targetCell = targetCell;}
    
}
