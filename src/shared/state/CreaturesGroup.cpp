/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CreaturesGroup.h"
#include "TypeID.h"

namespace state
{
    // Static attribut :
    int CreaturesGroup::stolenResourceNbr = 2;
    
    // Constructors :
    CreaturesGroup::CreaturesGroup (CreaturesID type){
        placed = false;
        this->creaturesType = type;
    }
    
    CreaturesGroup::~CreaturesGroup (){
        delete this;
    }
    
    // Setters and getters :

    bool CreaturesGroup::getPlaced (){
        return placed;
    }
    
    void CreaturesGroup::toPlace (int x, int y){
        this->x = x;
        this->y = y;
    }
    
    CreaturesID CreaturesGroup::getCreaturesType() const{
        return this->creaturesType;
    }
    
    void CreaturesGroup::setCreaturesType(CreaturesID Creatures_type){
        this->creaturesType = Creatures_type;
    }
};
