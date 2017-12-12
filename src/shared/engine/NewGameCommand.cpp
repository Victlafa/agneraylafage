/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "NewGameCommand.h"
#include <iostream>
using namespace state;

namespace engine
{
    NewGameCommand::NewGameCommand () 
    {
        type = CommandTypeID::NEWGAME;
    }
    
    void NewGameCommand::execute (std::stack<std::shared_ptr<Action>>& pile, state::State& state){
        
    }
    
    void NewGameCommand::serialize (Json::Value& out, int nTour) const{
        
    }
    
    NewGameCommand* NewGameCommand::deserialize (const Json::Value& in){
        return new NewGameCommand();
    }
}
