/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SimpleCell.h"
#include "TypeID.h"

namespace state
{
    SimpleCell::SimpleCell (SimpleCellID type, std::string resType, int resNbr, int x, int y){
        this->simpleCellType=type;
        this->resType=resType;
        this->resNbr=resNbr;
        this->x=x;
        this->y=y;
    }
    
    SimpleCell::~SimpleCell(){};
    
    SimpleCell::SimpleCell(const state::Element elem){
        this->x=elem.getX();
        this->y=elem.getY();
        this->creaturesNbr=elem.getCreaturesNbr();
    }
    
    SimpleCellID SimpleCell::getSimpleCellType() const{
        return this->simpleCellType;
    }
    
    void SimpleCell::setSimpleCellType(SimpleCellID simpleCellType){
        this->simpleCellType = simpleCellType;
    }
};

