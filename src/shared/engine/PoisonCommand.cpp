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
    PoisonCommand::PoisonCommand (int i_cell, int j_cell, state::ID id, int player) : targetCell(2) {
        targetCell[0] = i_cell;
        targetCell[1] = j_cell;
        this->typeCreatures = id;
        player = player;
        this->type = CommandTypeID::POISON;
    } 
    
    
    void PoisonCommand::execute (std::stack<std::shared_ptr<Action>>& pile, state::State& state){
        std::shared_ptr<Action> action(new PoisonAction(targetCell[0],targetCell[1], typeCreatures, player));
        std::cout << "avant le push" << pile.size() << std::endl;
        pile.push(action);
        std::cout << "après le push" << pile.size() << std::endl;
        action->apply(state);
    }
    
    void PoisonCommand::serialize (Json::Value& out, int nTour) const{
        Json::Value poisonCommand;
        poisonCommand["type"] = CommandTypeID::POISON;
        poisonCommand["targetCell[0]"] = targetCell[0];
        poisonCommand["targetCell[1]"] = targetCell[1];
        poisonCommand["stateType"] = type;
        poisonCommand["player"] = player;
        (out[nTour]).append(poisonCommand);
    }
    
    PoisonCommand* PoisonCommand::deserialize (const Json::Value& in){
        return nullptr;
    }
    
    // Setters and Getters
    const std::vector<int>& PoisonCommand::getTargetCell() const { return targetCell;}
    void PoisonCommand::setTargetCell(const std::vector<int>& targetCell) {this->targetCell = targetCell;}
    
}
