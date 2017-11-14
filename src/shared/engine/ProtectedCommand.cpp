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
    ProtectedCommand::ProtectedCommand (int i_cell, int j_cell) : cell(2) {
        cell[0] = i_cell;
        cell[1] = j_cell;
    };
    
    bool ProtectedCommand::isProtected(state::State& state){
        CellState etatCell = ((Cell)*state.getGrid()->get(cell[0],cell[1])).getCellState();
        std::cout << "etat de la cellule : " << etatCell << std::endl;
        if (etatCell == CellState::PROTECTED)
            return true;
        else
            return false;
    }
    
    void ProtectedCommand::protectProcess (state::State& state)
    {
        
    }
    
    CommandTypeID ProtectedCommand::getTypeID () const {return CommandTypeID::PROTECTED; }
    void ProtectedCommand::execute (state::State& state)
    {
        protectProcess(state);
    }
    // Setters and Getters
    const std::vector<int>& ProtectedCommand::getCell() const{return cell;}
    void ProtectedCommand::setCell(const std::vector<int>& cell) {this->cell = cell;}
}
