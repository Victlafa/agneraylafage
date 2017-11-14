/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AI.h"

namespace ai{
    AI::AI () {}
    AI::AI (const engine::Engine& moteur) : moteur(moteur) {}
    // Setters and Getters
    const engine::Engine& AI::getMoteur() const { return moteur; }
    void AI::setMoteur(const engine::Engine& moteur) { this->moteur = moteur; }
    const std::vector<std::unique_ptr<engine::Command> >& AI::getListCommands() const { return listCommands; }
    void AI::setListCommands(const std::vector<std::unique_ptr<engine::Command> >& listCommands) { this->listCommands = listCommands; }
}
