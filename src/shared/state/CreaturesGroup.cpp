/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CreaturesGroup.h"
#include "TypeID.h"
#include <iostream>

namespace state
{
    // Static attribut :
    int CreaturesGroup::stolenResourceNbr = 2;
    
    // Constructors :
    CreaturesGroup::CreaturesGroup (CreaturesID type) : Element(TypeID::CREATURESGROUP){
        placed = false;
        this->creaturesType = type;
    }
    
    CreaturesGroup::CreaturesGroup (const Element& elem) : Element(TypeID::CREATURESGROUP)
    {
        this->creaturesType = CreaturesID::BLACKSMITH;
        this->placed = false;
        this->x = elem.getX();
        this->y = elem.getY();
        this->creaturesNbr = elem.getCreaturesNbr();
    }
    
    CreaturesGroup::~CreaturesGroup (){ }
    
    // Setters and getters :

    bool CreaturesGroup::getPlaced () const{
        return placed;
    }
    
    void CreaturesGroup::toPlace (int x, int y){
        this->x = x;
        this->y = y;
        placed = true;
    }

    bool CreaturesGroup::operator== (CreaturesGroup otherGroup) {
        bool creaNbr = this->creaturesNbr == otherGroup.getCreaturesNbr();
        bool type = this->creaturesType == otherGroup.getCreaturesType();
        bool onMap = this->placed == otherGroup.getPlaced();
        bool posX = this->x == otherGroup.getX();
        bool posY = this->y == otherGroup.getY();

        if (creaNbr && type && onMap && posX && posY)
            return true;
        else
            return false;
    }
    
    CreaturesID CreaturesGroup::getCreaturesType() const{
        return this->creaturesType;
    }
    
    void CreaturesGroup::setCreaturesType(CreaturesID Creatures_type){
        this->creaturesType = Creatures_type;
    }
};
