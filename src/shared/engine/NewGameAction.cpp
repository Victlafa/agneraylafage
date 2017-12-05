/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "NewGameAction.h"
#include "../shared/state/CreaturesID.h"
#include <iostream>

using namespace state;

namespace engine
{
    NewGameAction::NewGameAction () {}
    void NewGameAction::apply (state::State& state)
    {
        int type;
        std::cout << "Quel type de creatures souhaitez-vous jouer ?\n" << std::endl;
        std::cout << "Cuisinier : 1\nForgeron : 2\nBûcheron : 3\nMineur : 4\n" << std::endl;
        std::cin >> type;
        state.reset((CreaturesID)type);
    }
    void NewGameAction::undo (state::State& etat)
    {
        
    }
}