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

    CreaturesGroup::CreaturesGroup (ID type, int nbrCrea, Player* joueur) : Element(type, CellState::NOTCELL){
        placed = false;
        
        this->setPlayer(joueur);
//        if (!joueur)
//        {
//            this->player = *(new Player());
//            //throw std::runtime_error("L'argument joueur du constructeur de CreaturesGroup est null !");
//        }
//            
//        else
//            this->player = *joueur;
        
        this->setCreaturesNbr(nbrCrea);
    }
    
    CreaturesGroup::CreaturesGroup (ID type, Player* joueur, const Element& elem) : Element(type, CellState::NOTCELL)
    {
        this->placed = false;
        this->x = elem.getX();
        this->y = elem.getY();
        this->creaturesNbr = elem.getCreaturesNbr();
        this->setPlayer(joueur);
    }
    
    CreaturesGroup::CreaturesGroup (ID type) : Element(type, CellState::NOTCELL){
        placed = false;
        setElemType(type);
    }
    
    CreaturesGroup::CreaturesGroup (const Element& elem) : Element(elem.getElemType(), CellState::NOTCELL)
    {

        this->setPlayer(elem.getPlayer());
        //this->player = elem.getPlayer();
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
        bool type = this->getElemType() == otherGroup.getElemType();
        bool onMap = this->placed == otherGroup.getPlaced();
        bool posX = this->x == otherGroup.getX();
        bool posY = this->y == otherGroup.getY();

        if (creaNbr && type && onMap && posX && posY)
            return true;
        else
            return false;
    }
    
    
};
