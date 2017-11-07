/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "FightCommand.h"
#include "../state/State.h"
#include "../state/CreaturesGroup.h"
#include <time.h>

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
        
        state::CreaturesGroup group1 = state->getPlayer()->getOneCreatures(creaPl1);
        state::CreaturesGroup group2 = state->getPlayer()->getOneCreatures(creaPl2);
        int totalPlayer1 = 0;
        int totalPlayer2 = 0;
        
        for (int i = 0 ; i < group1.getCreaturesNbr() ; i ++)
            totalPlayer1 += rand()%6 + 1;
        for (int i = 0 ; i < group2.getCreaturesNbr() ; i ++)
            totalPlayer2 += rand()%6 + 1;
                    
        if (totalPlayer1 > totalPlayer2)
            return true;
        else
            return false;
        
    }
    
    void FightCommand::gainConquest (state::State& state)
    {
        // Si le joueur 1 gagne le combat, il remporte un point de conquete
        if 
        // Sinon, c'est le joueur 2 qui le gagne
        
    }
    
    CommandTypeID FightCommand::getTypeID () const;
    void FightCommand::execute (state::State& state);
    // Setters and Getters
    int FightCommand::getCreaPl1() const;
    void FightCommand::setCreaPl1(int creaPl1);
    int FightCommand::getCreaPl2() const;
    void FightCommand::setCreaPl2(int creaPl2);
    int FightCommand::getCell() const;
    void FightCommand::setCell(int cell);
}