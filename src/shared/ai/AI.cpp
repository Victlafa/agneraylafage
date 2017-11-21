/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AI.h"
#include "../shared/engine/Command.h"

namespace ai{
    AI::AI () : listCommands() {}
    // Setters and Getters
    const std::vector<std::shared_ptr<engine::Command> >& AI::getListCommands() const { return listCommands; }
    void AI::setListCommands(const std::vector<std::shared_ptr<engine::Command> >& listCommands) { this->listCommands = listCommands; }
}
