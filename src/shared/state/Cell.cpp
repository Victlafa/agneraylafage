/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cell.h"

namespace state
{
    // Constructor :
    
    Cell::Cell(): Element(TypeID::CELL){
        this->setElemType(ID::GRASS);
        //this->setCellState(CellState::NORMAL);
    }
    
    Cell::Cell(ID type) : Element(TypeID::CELL) {
        this->setElemType(type);
        //this->setCellState(CellState::NORMAL);
    }
    
<<<<<<< HEAD
    Cell::~Cell(){}
    
    Cell::Cell(const state::Element& elem, CellTypeID type, CellState state){
        this->cellType = type;
        this->cellState = state;
=======
    Cell::Cell(const state::Element& elem) : Element(TypeID::CELL){
        this->setElemType(ID::GRASS);
        //this->setCellState(CellState::NORMAL);
>>>>>>> c836bcfb3b8edfe27cda0d2258311ea44d93de9c
        this->x=elem.getX();
        this->y=elem.getY();
        this->creaturesNbr=elem.getCreaturesNbr();
    }
    
    Cell::~Cell(){}
    
    
    // Setters and Getters :
    
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

    bool Cell::getOccupied() const{
        return this->occupied;
    }
    
    void Cell::setOccupied(bool occupied){
        this->occupied = occupied;
    }
};

