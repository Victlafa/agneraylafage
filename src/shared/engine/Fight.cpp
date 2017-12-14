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
        winner = -1;
        creasFighter = 0;
        creasDefender = 0;
    }
    
    // Renvoie true si c'est l'attaquant qui remporte le combat, sinon renvoie false
    bool Fight::fightProcess (state::State& state)
    {
        int nbCreaAtt = state.getCharacters()->get(fighterPos[0],fighterPos[1])->getCreaturesNbr();
        int nbCreaDef = state.getCharacters()->get(defenderPos[0],defenderPos[1])->getCreaturesNbr();
        creasFighter = nbCreaAtt;
        creasDefender = nbCreaDef;
        
        int totalFighter = 0;
        int totalDefender = 0;
        
        for (int i = 0 ; i < nbCreaAtt ; i ++)
            totalFighter += rand()%6 + 1;
        for (int j = 0 ; j < nbCreaDef ; j ++)
            totalDefender += rand()%6 + 1;
                    
        std::cout << "Fight::fightProcess - Total lancer de dés de l'attaquant : " << totalFighter << std::endl;
        std::cout << "Fight::fightProcess - Total lancer de dés du défenseur : " << totalDefender << std::endl;
        
        if (totalFighter > totalDefender)
            return true;
        else
            return false;
        
    }
    
    void Fight::gainConquest (state::State& state)
    {
        // Si le joueur 1 comme attaquant gagne le combat, il remporte un point de conquete 
        if (fighter == 1 && fightProcess(state))
        {
            state.getPlayer(1)->setConquestPoints(state.getPlayer(1)->getConquestPoints() + 1);
            winner = 1;
        }
            
        // Si le joueur 2 comme attaquant gagne le combat, il remporte un point de conquete
        else if (fighter == 2 && fightProcess(state))
        {
            state.getPlayer(2)->setConquestPoints(state.getPlayer(2)->getConquestPoints() + 1);
            winner = 2;
        }
            
        else
        {
            if (fighter != 1 && fighter != 2)
            {
                winner = 0;
                throw std::runtime_error("Fight::gainConquest - Erreur dans le choix de l'argument fighter du constructeur Fight::Fight, on doit entrer 1 ou 2");
            }
                
            else
            {
                std::cout << "Fight::gainConquest - Soit il y a egalite, soit le defenseur a remporte le combat !" << std::endl;
                winner = 3;
            }
                
        }
        
    }
    
    int Fight::getCreasFighter () const { return creasFighter; }
    int Fight::getCreasDefender () const { return creasDefender; }
    
    void Fight::apply (state::State& state)
    {
        //std::cout << "Debut du combat" << std::endl;
        gainConquest(state);
        //std::cout << "Fin du combat" << std::endl;
        
    }
    
    void Fight::undo (state::State& etat)
    {
        // On efface les points de victoire attribues selon victoire et defaite
        // On diminue le nbre de creatures restantes pour phase de renfort
        // S'il n'y avait pas eu egalite ou victoire du defenseur
        if (winner == 1 || winner == 2)
        {
            etat.getPlayer(winner)->setConquestPoints(etat.getPlayer(winner)->getConquestPoints() - 1);
//            etat.getPlayer(3-winner)->setCreaturesLeft(etat.getPlayer(3-winner)->getCreaturesLeft() + 1);
//            etat.getPlayer(winner)->decreaseCreaLeft();
        }
            
        
        // S'il y avait eu egalite ou victoire du defenseur, il n'y a pas de modifs à faire au niveau des points de victoire 
        
    }
    
    // Setters and Getters
    const std::vector<int>& Fight::getFighterPos() const { return fighterPos; }
    void Fight::setFighterPos(const std::vector<int>& fighterPos) { this->fighterPos = fighterPos; }
    const std::vector<int>& Fight::getDefenderPos() const { return defenderPos; }
    void Fight::setDefenderPos(const std::vector<int>& defenderPos) {this->defenderPos = defenderPos; }
    int Fight::getFighter() const {return fighter;}
    void Fight::setFighter(int fighter) {this->fighter = fighter; }
    int Fight::getWinner() const { return winner; }
    void Fight::setWinner(int winner) {this->winner = winner;}
}