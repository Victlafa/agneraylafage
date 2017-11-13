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
    CreaturesGroup::CreaturesGroup (CreaturesID type, int nbrCrea, Player* joueur) : Element(TypeID::CREATURESGROUP){
        placed = false;
        creaturesType = type;
        this->joueur = joueur;
        this->setCreaturesNbr(nbrCrea);
    }
    
    CreaturesGroup::CreaturesGroup (CreaturesID type, Player* joueur, const Element& elem) : Element(TypeID::CREATURESGROUP)
    {
        this->creaturesType = type;
        this->placed = false;
        this->x = elem.getX();
        this->y = elem.getY();
        this->creaturesNbr = elem.getCreaturesNbr();
        this->joueur = joueur;
    }
    
        CreaturesGroup::CreaturesGroup (const Element& elem) : Element(TypeID::CREATURESGROUP)
    {
        this->creaturesType = ((CreaturesGroup)elem).getCreaturesType();
        this->joueur = ((CreaturesGroup)elem).getPlayer();
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
    
    Player* CreaturesGroup::getPlayer (){return joueur;}
    void CreaturesGroup::setPlayer (Player* joueur){this->joueur = joueur;}
    
    CreaturesID CreaturesGroup::getCreaturesType() const{
        return this->creaturesType;
    }
    
    void CreaturesGroup::setCreaturesType(CreaturesID Creatures_type){
        this->creaturesType = Creatures_type;
    }
};
