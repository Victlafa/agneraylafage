/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PlaceCommand.h"
#include <iostream>
#include "../shared/state/CreaturesTab.h"
#include "PlaceAction.h"

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
    
    void PlaceCommand::execute (std::stack<std::shared_ptr<Action> >& pile, state::State& state){
        std::shared_ptr<Action> action(new PlaceAction(finalPos[0], finalPos[1], player, creaType));
        if(!state.getCharacters()->isOccupiedByOpp(finalPos[0],finalPos[1],state.getPlayer(player).get())){
            pile.push(action);
            action->apply(state);
        }
        else
            throw std::runtime_error("PlaceCommand::execute - La case de destination choisie appartient à l'adversaire !");
    }
    
    // Setters and Getters
    const std::vector<int>& PlaceCommand::getFinalPos() const {return finalPos;}
    void PlaceCommand::setFinalPos(const std::vector<int>& pos) {this->finalPos = pos;}
    state::ID PlaceCommand::getCreaType() const {return creaType;}
    void PlaceCommand::setCreaType(state::ID creaType) {this->creaType = creaType;}
}