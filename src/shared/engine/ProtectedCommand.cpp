/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ProtectedCommand.h"

namespace engine
{
    ProtectedCommand::ProtectedCommand (int cell) : cell(cell) {};
    
    void ProtectedCommand::protectProcess (state::State& state)
    {
        
    }
    
    CommandTypeID ProtectedCommand::getTypeID () const {return CommandTypeID::PROTECTED; }
    void ProtectedCommand::execute (state::State& state)
    {
        protectProcess(state);
    }
    // Setters and Getters
    int ProtectedCommand::getCell() const{return cell;}
    void ProtectedCommand::setCell(int cell) {this->cell = cell;}
}
