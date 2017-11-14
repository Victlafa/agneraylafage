/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MoveCharCommand.h"
#include "../shared/state/CreaturesGroup.h"
using namespace state;

namespace engine
{
    MoveCharCommand::MoveCharCommand (int i_crea, int j_crea, int newI, int newJ, int player) : fightCom(i_crea,j_crea,newI,newJ), creatures(2) {
        creatures[0] = i_crea;
        creatures[1] = j_crea;
        this->newI = newI;
        this->newJ = newJ;
        this->player = player;
    }
    
    CommandTypeID MoveCharCommand::getTypeID () const {return CommandTypeID::MOVECHAR;}
    
    void MoveCharCommand::execute (state::State& state)
    {
        state.getCharacters()->moveElement(creatures[0],creatures[1],newI,newJ);
    }
    
    bool MoveCharCommand::isOccupied(state::State& state){
        
        if (state.getCharacters()->get(newI,newJ) != NULL)
        {
            CreaturesGroup crea = (CreaturesGroup)*state.getCharacters()->get(newI,newJ).get();
            if (crea.getPlayer() != state.getPlayer(player).get())
                return true;
            else
                return false;
        }
            
        else
            return false;
    }
    
    // Setters and Getters
    const std::vector<int>& MoveCharCommand::getCreatures() const {return creatures;}
    void MoveCharCommand::setCreatures(const std::vector<int>& creatures) {this->creatures = creatures;}
    int MoveCharCommand::getNewI() const {return newI;}
    void MoveCharCommand::setNewI(int newI) {this->newI = newI;}
    int MoveCharCommand::getNewJ() const {return newJ;}
    void MoveCharCommand::setNewJ(int newJ) {this->newJ = newJ;}
}
