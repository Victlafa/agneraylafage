/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cell.h"

namespace state
{
    // Constructor :
    
    Cell::Cell(): Element(ID::GRASS,CellState::NORMAL){
    }
    
    Cell::Cell(ID type, CellState state) : Element(type, state) {
    }
 
    Cell::Cell(const state::Element& elem, CellState state){
        this->setElemType(elem.getElemType());
        //this->setCellState(CellState::NORMAL);
        this->x=elem.getX();
        this->y=elem.getY();
        this->creaturesNbr=elem.getCreaturesNbr();
        this->setCellState(state);
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

