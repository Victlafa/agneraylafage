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
    PlaceCommand::PlaceCommand (int i_final, int j_final, int player, state::ID type) : pos(2) {
        pos[0] = i_final;
        pos[1] = j_final;
        this->player = player;
        this->creaType = type;
    }
    CommandTypeID PlaceCommand::getTypeID () const { return CommandTypeID::PLACE; }
    
    void PlaceCommand::execute (std::stack<std::shared_ptr<Action> >& pile, state::State& state){
        PlaceAction action(pos[0], pos[1], player, creaType);
        action.apply(state);
    }
    
    // Setters and Getters
    const std::vector<int> PlaceCommand::getPos() const {return pos;}
    void PlaceCommand::setPos(const std::vector<int> pos) {this->pos = pos;}
    state::ID PlaceCommand::getCreaType() const {return creaType;}
    void PlaceCommand::setCreaType(state::ID creaType) {this->creaType = creaType;}
}