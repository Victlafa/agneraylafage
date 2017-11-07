/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Engine.h"

namespace engine
{
    Engine::Engine(){
        currentCommands = std::map<int,std::unique_ptr<Command>>();
    }
    
    Engine::~Engine (){}
    const state::State& Engine::getState () const {return state;}
    void Engine::setState(const state::State& state) {this->state = state;}
    void Engine::addPassiveCommands () {}
    void Engine::addCommand (int priority, Command* cmd) {
        // On ajoute une commande :
        currentCommands.emplace(priority,std::unique_ptr(cmd));
        // la map trie automatiquement les clés dans l'ordre croissant (en principe, à vérifier)
        
    }
    void Engine::update (){
        for (std::unique_ptr<Command> commande : currentCommands)
            commande->execute(state);
    }
}