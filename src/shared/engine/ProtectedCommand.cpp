/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ProtectedCommand.h"
#include "../state.h"
#include <iostream>

using namespace state;

namespace engine
{
    ProtectedCommand::ProtectedCommand (int i_cell, int j_cell) : target(2) {
        target[0] = i_cell;
        target[1] = j_cell;
    };
    
    
    CommandTypeID ProtectedCommand::getTypeID () const {return CommandTypeID::PROTECTED; }
    
    void ProtectedCommand::execute (std::stack<std::shared_ptr<Action>>& pile, state::State& state)
    {
        
    }
    // Setters and Getters
    const std::vector<int>& ProtectedCommand::getTarget() const { return target; }
    void ProtectedCommand::setTarget(const std::vector<int>& target) { this->target = target; }
}
