/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Engine.h"
#include "../engine.h"
#include "../shared/state.h"
#include "../client/render.h"
#include <iostream>
using namespace state;
using namespace render;

namespace engine
{
    Engine::Engine(CreaturesID typePl1) : currentState(typePl1) { 
        tour = 1;
    }
    
    Engine::~Engine (){}
    
    state::State& Engine::getState () {return this->currentState;}
    
    const std::unique_ptr<state::Player>& Engine::getPlayer (int num) const 
    {
        if (num == 1)
            return currentState.getPlayer(1);
        else if (num == 2)
            return currentState.getPlayer(2);
        else
            throw std::runtime_error("Engine::getPlayer - Vous avez entré un mauvais numéro en argument !\n");
            return NULL;
    }
    
    void Engine::addPassiveCommands () {
//        Command* lastCommand = currentCommands.end()->second.get();
//        
//        // Si la derniere commande ajoutee est de type MOVECHAR et si la case de destination est occupee
//        if (lastCommand->getTypeID() == CommandTypeID::MOVECHAR)
//        {
//            // On recupere cette commande
//            MoveCharCommand lastCom = (MoveCharCommand)*(currentCommands.end()->second);
//            // Si la case de destination est occupee PAR l'adversaire
//            if (lastCom->isOccupied(currentState))
//                // On ajoute une commande de combat à la liste des commandes
//                addCommand(currentCommands.end()->first + 1, new FightCommand(lastCom->getCreatures()[0],lastCom->getCreatures()[1],lastCom->getNewI(),lastCom->getNewJ()));
//        }
//            
    }
    
    void Engine::addCommand (int priority, Command* cmd) {
        // On ajoute une commande :
        currentCommands.emplace(priority,std::unique_ptr<Command>(cmd));
        // la map trie automatiquement les clés dans l'ordre croissant (en principe, à vérifier)
        // Ajout de commandes automatiques
        //addPassiveCommands();
        
    }
    
    void Engine::update (){
        // On execute les commandes par ordre de priorite 
        for (std::map<int,std::unique_ptr<Command> >::iterator mapIt = currentCommands.begin(); mapIt != currentCommands.end(); mapIt ++)
            mapIt->second->execute(pileAction,currentState);
        currentCommands.clear();
    }
    
    void Engine::poisonCell(bool poison,int i_cell, int j_cell){
        currentState.getGrid()->poisonCell(poison,i_cell,j_cell);
    }
    
    void Engine::increaseTour ()
    {
        tour += 1;
    }
    
    int Engine::getTour () {return tour; }
    
    const std::stack<std::shared_ptr<Action> >& Engine::getPileAction() const {return pileAction;}
    
    void Engine::setPileAction(const std::stack<std::shared_ptr<Action> >& pileAction) {this->pileAction = pileAction;}
    
}