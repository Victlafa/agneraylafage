/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SimpleCell.h"
#include "TypeID.h"

namespace state
{
    SimpleCell::SimpleCell(std::string res, int nbr, SimpleCellID type){
        this->genResType = res;
        this->genResNbr = nbr;
        this->type = type;
    }
    
    std::vector<std::string> SimpleCell::getResType (){
        return genResType;
    }
    
    std::vector<int> SimpleCell::getResNbr (){
        return genResNbr;
    }
    
    void SimpleCell::addResType (std::string resType){
        genResType.push_back(resType);
    }
    
    void SimpleCell::addResNbr (int resNbr){
        genResNbr = resNbr;
    }
    
    TypeID const SimpleCell::getTypeID (){
        return TypeID.SIMPLECELL;
    }
    
    int SimpleCell::getx (){
        return this->x;
    }
    
    void SimpleCell::setx (int x){
        this->x = x;
    }
    
    int SimpleCell::gety (){
        return this->y;
    }
    
    void SimpleCell::sety (int y){
        this->y = y;
    }
    
    // Setters and Getters
    SimpleCellID  SimpleCell::type() const{
        return type;
    }
    
    void SimpleCell::type(SimpleCellID type){
        this->type = type;
    }
    
    
};

