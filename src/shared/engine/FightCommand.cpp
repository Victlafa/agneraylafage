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
    FightCommand::FightCommand (int creatures1, int creatures2, int cell){
        creaPl1 = creatures1;
        creaPl2 = creatures2;
        this->cell = cell;
    }
    
    // Renvoie true si c'est le joueur 1 qui remporte le combat, sinon renvoie false
    bool FightCommand::fightProcess (state::State& state)
    {
        srand(time(NULL));
        
        // ERREUR DE SEGMENTATION ICI !!!!
        // Considere que le pointeur de l'element à caster est null !
        
        //CreaturesGroup group1 = (state::CreaturesGroup)*state.getCharacters()->getByNumber(creaPl1);
        //CreaturesGroup group2 = (state::CreaturesGroup)*state.getCharacters()->getByNumber(creaPl2);
        //int nbCrea1 = (state::CreaturesGroup)*state.getCharacters()->getByNumber(creaPl1)->getCreaturesNbr();
        //int nbCrea2 = (state::CreaturesGroup)*state.getCharacters()->getByNumber(creaPl2)->getCreaturesNbr();
        int nbCrea1 = state.getCharacters()->getByNumber(creaPl1)->getCreaturesNbr();
        int nbCrea2 = state.getCharacters()->getByNumber(creaPl2)->getCreaturesNbr();
        
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
        // Si le joueur attaquant gagne le combat, il remporte un point de conquete
        if (state.getPlayer(1)->getIsStriker() && fightProcess(state))
            state.getPlayer(1)->setConquestPoints(state.getPlayer(1)->getConquestPoints() + 1);
        else if (state.getPlayer(2)->getIsStriker() && !fightProcess(state))
            state.getPlayer(2)->setConquestPoints(state.getPlayer(2)->getConquestPoints() + 1);
        else
            std::cout << "Aucun des joueurs n'a été défini comme attaquant ou le combat s'est mal deroule !" << std::endl;
        
    }
    
    CommandTypeID FightCommand::getTypeID () const { return CommandTypeID::FIGHT; }
    
    void FightCommand::execute (state::State& state)
    {
        std::cout << "Debut du combat" << std::endl;
        gainConquest(state);
        std::cout << "Fin du combat" << std::endl;
        
    }
    
    // Setters and Getters
    int FightCommand::getCreaPl1() const { return creaPl1; }
    void FightCommand::setCreaPl1(int creaPl1) { this-> creaPl1 = creaPl1; }
    int FightCommand::getCreaPl2() const { return creaPl2; }
    void FightCommand::setCreaPl2(int creaPl2) { this-> creaPl2 = creaPl2; }
    int FightCommand::getCell() const {return cell;}
    void FightCommand::setCell(int cell) {this->cell = cell;}
}