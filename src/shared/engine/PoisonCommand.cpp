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
    PoisonCommand::PoisonCommand (int i_cell, int j_cell) : target(2) {
        target[0] = i_cell;
        target[1] = j_cell;
    }
    
    CommandTypeID PoisonCommand::getTypeID () const {return CommandTypeID::POISON;}
    
    void PoisonCommand::execute (std::stack<std::shared_ptr<Action>>& pile, state::State& state){
        PoisonAction action;
        action.apply(state);
    }
    // Setters and Getters
    const std::vector<int>& PoisonCommand::getTarget() const{return target;}
    void PoisonCommand::setTarget(const std::vector<int>& cell){this->target = target;}
}
