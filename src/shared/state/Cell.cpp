/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cell.h"

namespace state
{
    // Constructor :
    
    Cell::Cell(){}
    Cell::~Cell(){}
    
    // Setters and Getters :
    
    CellState Cell::getCellState () const{
        return this->cellState;
    }
    
    void Cell::setCellState(CellState cellState){
        this->cellState = cellState;
    }
    
    const std::string& Cell::getResType() const{
        return this->resType;
    }
    
    void Cell::setResType(const std::string& resType){
        this->resType = resType;
    }
    
    int Cell::getResNbr() const{
        return this->resNbr;
    }
    
    void Cell::setResNbr(int resNbr){
        this->resNbr = resNbr;
    }
    
    CellTypeID Cell::getCellType() const{
        return this->cellType;
    }
    
    void Cell::setCellType(CellTypeID cellType){
        this->cellType = cellType;
    }

    bool Cell::getOccupied() const{
        return this->occupied;
    }
    
    void Cell::setOccupied(bool occupied){
        this->occupied = occupied;
    }
};

