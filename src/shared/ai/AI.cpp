/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AI.h"
#include "../shared/engine/Command.h"
#include "../shared/state.h"
#include <time.h>

using namespace state;

namespace ai{
    AI::AI () : listCommands() {}
    // Setters and Getters
    const std::vector<std::shared_ptr<engine::Command> >& AI::getListCommands() const { return listCommands; }
    void AI::setListCommands(const std::vector<std::shared_ptr<engine::Command> >& listCommands) { this->listCommands = listCommands; }
    
    // On initialise les parametres de base de l'IA
    void AI::initIA (engine::Engine& moteur)
    {
        CreaturesID typeJoueur1 = moteur.getPlayer(1)->getClanName();
        Player* player_ia = moteur.getPlayer(2).get();
        CreaturesID tirage = typeJoueur1;
        
        // On tire au sort un type de creature qu'on associe à l'IA (on s'arrange pour qu'il soit different de celui du joueur) :
        while (tirage == typeJoueur1)
        {
            tirage = (CreaturesID)(rand()%4 + 1);
        }
        
        player_ia->setClanName(tirage);
        player_ia->setCellNbr(3);
    }
}
