/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Engine.h"
#include "../shared/state.h"

namespace engine
{
    Engine::Engine() : currentCommands() {
    }
    
    Engine::~Engine (){}
    const state::State& Engine::getState () const {return currentState;}
    void Engine::addPassiveCommands () {}
    void Engine::addCommand (int priority, Command* cmd) {
        // On ajoute une commande :
        currentCommands.emplace(priority,std::unique_ptr<Command>(cmd));
        // la map trie automatiquement les clés dans l'ordre croissant (en principe, à vérifier)
        
    }
    void Engine::update (){
        // On execute les commandes par ordre de priorite 
        for (std::map<int,std::unique_ptr<Command> >::iterator mapIt = currentCommands.begin(); mapIt != currentCommands.end(); mapIt ++)
            mapIt->second->execute(currentState);
        currentCommands.clear();
    }
}