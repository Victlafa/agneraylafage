/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CreaturesGroup.h"
#include "TypeID.h"

namespace state
{
    int CreaturesGroup::getx (){
        return x;
    }
    
    void CreaturesGroup::setx (int x){
        this->x = x;
    }
    
    int CreaturesGroup::gety (){
        return y;
    }
    
    void CreaturesGroup::sety (int y){
        this->y = y;
    }
    
    TypeID const CreaturesGroup::getTypeID (){
        return TypeID.CREATURESGROUP;
    }
    
    bool CreaturesGroup::getplaced (){
        return placed;
    }
    
    void CreaturesGroup::place (int x, int y){
        this->x = x;
        this->y = y;
    }
    
    CreaturesID CreaturesGroup::getCreatures_type() const{
        return this->Creatures_type;
    }
    
    void CreaturesGroup::setCreatures_type(CreaturesID Creatures_type){
        this->Creatures_type = Creatures_type;
    }
    
    
};
