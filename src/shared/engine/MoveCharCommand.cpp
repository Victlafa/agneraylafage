/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MoveCharCommand.h"

namespace engine
{
    MoveCharCommand::MoveCharCommand (int creatures, int newX, int newY){
        this->creatures = creatures;
        this->newX = newX;
        this->newY = newY;
    }
    
    CommandTypeID MoveCharCommand::getTypeID () const {return CommandTypeID::MOVECHAR;}
    
    void MoveCharCommand::execute (state::State& state)
    {
        (state::CreaturesGroup)*state.getCharacters()->getByNumber(creatures)->setX(newX);
        (state::CreaturesGroup)*state.getCharacters()->getByNumber(creatures)->setY(newY);
    }
    
    // Setters and Getters
    int MoveCharCommand::getCreatures() const {return creatures;}
    void MoveCharCommand::setCreatures(int creatures) {this->creatures = creatures;}
    int MoveCharCommand::getNewX() const {return newX;}
    void MoveCharCommand::setNewX(int newX) {this->newX = newX;}
    int MoveCharCommand::getNewY() const {return newY;}
    void MoveCharCommand::setNewY(int newY) {this->newY = newY;}
}
