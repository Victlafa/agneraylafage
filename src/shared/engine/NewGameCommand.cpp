/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "NewGameCommand.h"
using namespace state;

namespace engine
{
    NewGameCommand::NewGameCommand () {}
    CommandTypeID NewGameCommand::getTypeID () const{
        return CommandTypeID::NEWGAME;
    }
    void NewGameCommand::execute (state::State& state){
        state.reset();
    }
}
