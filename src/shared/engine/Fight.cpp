/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Fight.h"
#include "../state/State.h"
#include "../state/CreaturesGroup.h"
#include <time.h>
#include <iostream>
using namespace state;

namespace engine
{
    Fight::Fight (int i_fighter, int j_fighter, int i_defender, int j_defender, int fighter) : fighterPos(2), defenderPos(2) {
        fighterPos[0] = i_fighter;
        fighterPos[1] = j_fighter;
        defenderPos[0] = i_defender;
        defenderPos[1] = j_defender;
        this->fighter = fighter;
    }
    
    // Renvoie true si c'est le joueur 1 qui remporte le combat, sinon renvoie false
    bool Fight::fightProcess (state::State& state)
    {
        int nbCrea1 = state.getCharacters()->get(fighterPos[0],fighterPos[1])->getCreaturesNbr();
        int nbCrea2 = state.getCharacters()->get(defenderPos[0],defenderPos[1])->getCreaturesNbr();
        
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
    
    void Fight::gainConquest (state::State& state)
    {
        // Si le joueur 1 comme attaquant gagne le combat, il remporte un point de conquete
        if (state.getPlayer(1)->getIsStriker() && fightProcess(state))
        {
            state.getPlayer(1)->setConquestPoints(state.getPlayer(1)->getConquestPoints() + 1);
            state.getPlayer(1)->setIsStriker(false);
        }
            
        // Si le joueur 2 comme attaquant gagne le combat, il remporte un point de conquete
        else if (state.getPlayer(2)->getIsStriker() && !fightProcess(state))
        {
            state.getPlayer(2)->setConquestPoints(state.getPlayer(2)->getConquestPoints() + 1);
            state.getPlayer(2)->setIsStriker(false);
        }
            
        else
        {
            if (!state.getPlayer(1)->getIsStriker() && !state.getPlayer(2)->getIsStriker())
                throw std::runtime_error("Aucun des joueurs n'a été défini comme attaquant !");
            else
                std::cout << "Il y a égalité !" << std::endl;
        }
        
    }
    
    void Fight::execute (state::State& state)
    {
        //std::cout << "Debut du combat" << std::endl;
        gainConquest(state);
        //std::cout << "Fin du combat" << std::endl;
        
    }
    
    // Setters and Getters
    const std::vector<int>& Fight::getFighterPos() const { return fighterPos; }
    void Fight::setFighterPos(const std::vector<int>& fighterPos) { this->fighterPos = fighterPos; }
    const std::vector<int>& Fight::getDefenderPos() const { return defenderPos; }
    void Fight::setDefenderPos(const std::vector<int>& defenderPos) {this->defenderPos = defenderPos; }
    int Fight::getFighter() const {return fighter;}
    void Fight::setFighter(int fighter) {this->fighter = fighter; }
}