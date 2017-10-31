/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cell.h"
#include "SimpleCellID.h"

namespace state
{
    // Constructor :
    
    Cell::Cell() {
        this->cellType = CellTypeID::SIMPLE;
        this->cellState = CellState::NORMAL;
    }
    
    Cell::Cell(CellTypeID type){
        setCellType(type);
        this->cellState = CellState::NORMAL;
    }
    
    Cell::~Cell(){}
    
    Cell::Cell(const state::Element& elem){
        this->cellType = CellTypeID::SIMPLE;
        this->cellState = CellState::NORMAL;
        this->x=elem.getX();
        this->y=elem.getY();
        this->creaturesNbr=elem.getCreaturesNbr();
    }
    
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

