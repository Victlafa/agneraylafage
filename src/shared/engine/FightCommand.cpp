/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "FightCommand.h"
#include "../state/State.h"
#include "../state/CreaturesGroup.h"
#include <time.h>
#include <iostream>
using namespace state;

namespace engine
{
    FightCommand::FightCommand (int i_crea1, int j_crea1, int i_crea2, int j_crea2) : creaPl1(2), creaPl2(2) {
        creaPl1[0] = i_crea1;
        creaPl1[1] = j_crea1;
        creaPl2[0] = i_crea2;
        creaPl2[1] = j_crea2;
    }
    
    // Renvoie true si c'est le joueur 1 qui remporte le combat, sinon renvoie false
    bool FightCommand::fightProcess (state::State& state)
    {
        int nbCrea1 = state.getCharacters()->get(creaPl1[0],creaPl1[1])->getCreaturesNbr();
        int nbCrea2 = state.getCharacters()->get(creaPl2[0],creaPl2[1])->getCreaturesNbr();
        
        int totalPlayer1 = 0;
        int totalPlayer2 = 0;
        
        for (int i = 0 ; i < nbCrea1 ; i ++)
            totalPlayer1 += rand()%6 + 1;
        for (int j = 0 ; j < nbCrea2 ; j ++)
            totalPlayer2 += rand()%6 + 1;
                    
        if (totalPlayer1 > totalPlayer2)
            return true;
        else
            return false;
        
    }
    
    void FightCommand::gainConquest (state::State& state)
    {
        // Si le joueur 1 comme attaquant gagne le combat, il remporte un point de conquete
        if (state.getPlayer(1)->getIsStriker() && fightProcess(state))
            state.getPlayer(1)->setConquestPoints(state.getPlayer(1)->getConquestPoints() + 1);
        // Si le joueur 2 comme attaquant gagne le combat, il remporte un point de conquete
        else if (state.getPlayer(2)->getIsStriker() && !fightProcess(state))
            state.getPlayer(2)->setConquestPoints(state.getPlayer(2)->getConquestPoints() + 1);
        else
        {
            if (!state.getPlayer(1)->getIsStriker() && !state.getPlayer(2)->getIsStriker())
                throw std::runtime_error("Aucun des joueurs n'a été défini comme attaquant !");
            else
                std::cout << "Il y a égalité !" << std::endl;
        }
        
    }
    
    CommandTypeID FightCommand::getTypeID () const { return CommandTypeID::FIGHT; }
    
    void FightCommand::execute (state::State& state)
    {
        //std::cout << "Debut du combat" << std::endl;
        gainConquest(state);
        //std::cout << "Fin du combat" << std::endl;
        
    }
    
    // Setters and Getters
    const std::vector<int>& FightCommand::getCreaPl1() const { return creaPl1; }
    void FightCommand::setCreaPl1(const std::vector<int>& creaPl1) { this-> creaPl1 = creaPl1; }
    const std::vector<int>& FightCommand::getCreaPl2() const { return creaPl2; }
    void FightCommand::setCreaPl2(const std::vector<int>& creaPl2) { this-> creaPl2 = creaPl2; }
}