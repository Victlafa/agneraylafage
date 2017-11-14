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
    NewGameCommand::NewGameCommand () {}
    CommandTypeID NewGameCommand::getTypeID () const{
        return CommandTypeID::NEWGAME;
    }
    void NewGameCommand::execute (state::State& state){
        int type;
        std::cout << "Quel type de creatures souhaitez-vous jouer ?\n" << std::endl;
        std::cout << "Cuisinier : 1\nForgeron : 2\nBûcheron : 3\nMineur : 4\n" << std::endl;
        std::cin >> type;
        state.reset((CreaturesID)type);
    }
}
