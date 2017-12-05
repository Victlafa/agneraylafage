/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PlaceCommand.h"
#include <iostream>
#include "../shared/state/CreaturesTab.h"

using namespace std;
using namespace state;

namespace engine{
    
    //PlaceCommand::PlaceCommand () {}
    PlaceCommand::PlaceCommand (int i_final, int j_final, int player, state::ID type) : finalPos(2) {
        finalPos[0] = i_final;
        finalPos[1] = j_final;
        this->player = player;
        this->creaType = type;
    }
    CommandTypeID PlaceCommand::getTypeID () const { return CommandTypeID::PLACE; }
    
    void PlaceCommand::execute (std::stack<std::shared_ptr<Action>>& pile, state::State& state) {
        
        
    }
    
    // Setters and Getters
    const std::vector<int>& PlaceCommand::getFinalPos() const { return finalPos; }
    void PlaceCommand::setFinalPos(const std::vector<int>& finalPos) { this->finalPos = finalPos; }
    state::ID PlaceCommand::getCreaType() const { return creaType; }
    void PlaceCommand::setCreaType(state::ID creaType) {this->creaType = creaType; }
}