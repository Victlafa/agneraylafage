/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ProtectedAction.h"
#include "../state.h"
#include <iostream>

using namespace state;

namespace engine
{
    ProtectedAction::ProtectedAction (int i_cell, int j_cell) : cell(2) {
        cell[0] = i_cell;
        cell[1] = j_cell;
    };
    
    bool ProtectedAction::isProtected(state::State& state){
        CellState etatCell = ((Cell)*state.getGrid()->get(cell[0],cell[1])).getCellState();
        std::cout << "etat de la cellule : " << etatCell << std::endl;
        if (etatCell == CellState::PROTECTED)
            return true;
        else
            return false;
    }
    
    void ProtectedAction::protectProcess (state::State& state)
    {
        
    }
    
    void ProtectedAction::apply (state::State& state)
    {
        protectProcess(state);
    }
    
    void ProtectedAction::undo (state::State& etat)
    {
        
    }
    
    // Setters and Getters
    const std::vector<int>& ProtectedAction::getCell() const{return cell;}
    void ProtectedAction::setCell(const std::vector<int>& cell) {this->cell = cell;}
}
