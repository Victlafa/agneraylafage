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
    
    const SimpleCellID SimpleCell::getSimpleCellID (){
        return this->simpleCellType;
    }
 
    SimpleCellID SimpleCell::getSimpleCellType() const{
        return this->
    }
    
    void SimpleCell::setSimpleCellType(SimpleCellID simpleCellType);
};

