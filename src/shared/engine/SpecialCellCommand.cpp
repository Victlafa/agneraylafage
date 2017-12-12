/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SpecialCellCommand.h"
#include <iostream>

namespace engine
{
    SpecialCellCommand::SpecialCellCommand (int init_i, int init_j, int final_i, int final_j, int player, SpecialTypeID type) : initPos(2), finalPos(2)
    {
        initPos[0] = init_i;
        initPos[1] = init_j;
        finalPos[0] = final_i;
        finalPos[1] = final_j;
        this->player = player;
        this->specialType = type;
        this->type = CommandTypeID::SPECIAL;
    }
    
    SpecialTypeID SpecialCellCommand::getSpecialType () const { return specialType; }
    void SpecialCellCommand::setSpecialType(SpecialTypeID specialType) { this->specialType = specialType; }
    
    void SpecialCellCommand::execute (std::stack<std::shared_ptr<Action>>& pile, state::State& state)
    {
        
    }
    
    void SpecialCellCommand::serialize (Json::Value& out, int nTour) const{
        Json::Value speCellCommand;
        speCellCommand["type"] = CommandTypeID::SPECIAL;
        speCellCommand["initPos[0]"] = initPos[0];
        speCellCommand["initPos[1]"] = initPos[1];
        speCellCommand["finalPos[0]"] = finalPos[0];
        speCellCommand["finalPos[1]"] = finalPos[1];
        speCellCommand["specialType"] = specialType;
        speCellCommand["player"] = player;
        (out[nTour]).append(speCellCommand);
    }
    
    SpecialCellCommand* SpecialCellCommand::deserialize (const Json::Value& in){
        return nullptr;
    }
    
    // Setters and Getters
    const std::vector<int>& SpecialCellCommand::getInitPos() const { return initPos; }
    void SpecialCellCommand::setInitPos(const std::vector<int>& initPos) {
        this->initPos[0] = initPos[0];
        this->initPos[1] = initPos[1];
    }
    const std::vector<int>& SpecialCellCommand::getFinalPos() const { return finalPos; }
    void SpecialCellCommand::setFinalPos(const std::vector<int>& finalPos)
    {
        this->finalPos[0] = finalPos[0];
        this->finalPos[1] = finalPos[1];
    }


}