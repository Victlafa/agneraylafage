/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SimpleCell.h"
#include "TypeID.h"
#include <iostream>

namespace state
{
    SimpleCell::SimpleCell (ID type, std::string resType, int resNbr, int x, int y, CellState state) : Cell(type, state) {
        this->resType=resType;
        this->resNbr=resNbr;
        this->x=x;
        this->y=y;
    }
    
    SimpleCell::~SimpleCell(){};
    
    SimpleCell::SimpleCell(const state::Element& elem){
        this->x=elem.getX();
        this->y=elem.getY();
        this->creaturesNbr=elem.getCreaturesNbr();
    }
    
    bool SimpleCell::operator== (SimpleCell otherSimpleCell) {
        bool rNbr = this->resNbr == otherSimpleCell.getResNbr();
        bool rtype = this->resType == otherSimpleCell.getResType();
        bool cellType = this->getElemType() == otherSimpleCell.getElemType();
        bool posX = this->x == otherSimpleCell.getX();
        bool posY = this->y == otherSimpleCell.getY();

        if (rNbr && rtype && cellType && posX && posY)
            return true;
        else
            return false;
    }
    
};

