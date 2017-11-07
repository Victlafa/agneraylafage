/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "NewGameCommand.h"
using namespace state;

namespace engine
{
    NewGameCommand ( ) {}
    CommandTypeID getTypeID () const{
        return CommandTypeID::NEWGAME;
    }
    void execute (state::State& state){
        state.getCharacters().reset(new ElementTab(TypeID::CREATURESGROUP));
        state.getGrid().reset(new ElementTab(TypeID::CELL));
        state.getPlayer(1).reset(new Player());
        state.getPlayer(2).reset(new Player());
    }
}
