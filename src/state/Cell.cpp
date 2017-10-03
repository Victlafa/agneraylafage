/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cell.h"

namespace state
{
    // Constructor :
    
    Cell::Cell (){}
    Cell::~Cell (){}
    
    // Setters and Getters :
    
    int Cell::getx (){
        return this->x;
    }
    
    void Cell::setx (int x){
        this->x = x;
    }
    
    int Cell::gety (){
        return this->y;
    }
    
    void Cell::sety (int y){
        this->y = y;
    }
    
    const CreaturesGroup& Cell::getPositionedOn() const{
        return this->positionedOn;
    }
    void Cell::setPositionedOn(const CreaturesGroup& positionedOn){
        this->positionedOn = positionedOn;
    }
    
    
};

