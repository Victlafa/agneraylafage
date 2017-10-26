#include "Element.h"
#include <iostream>

namespace state
{
    // Constructor :
    Element::Element(){
        x = 0;
        y = 0;
        creaturesNbr = 0;
        elemType = TypeID::CELL;
        std::cout << this << std::endl;
    }
    
    Element::~Element() {}
    
    bool Element::operator== (Element otherElement)
    {
        bool coordX = (this->x == otherElement.getX());
        bool coordY = (this->y == otherElement.getY());
        bool creaNbr = (this->creaturesNbr == otherElement.getCreaturesNbr());
        bool type = (this->elemType == otherElement.getElemType());
        
        if (coordX && coordY && creaNbr && type)
            return true;
        else
            return false;
    }
    
    // Getters and setters :
    int Element::getX() const{
        return this->x;
    }
    
    void Element::setX(int x){
        this->x = x;
    }
    
    int Element::getY() const{
        return this->y;
    }
    
    void Element::setY(int y){
        this->y = y;
    }
    
    int Element::getCreaturesNbr() const{
        return this->creaturesNbr;
    }
    
    void Element::setCreaturesNbr(int creaturesNbr){
        this->creaturesNbr = creaturesNbr;
    }
    
    TypeID Element::getElemType() const{
        return this->elemType;
    }
    void Element::setElemType(TypeID elemType)
    {
        this->elemType = elemType;
    }
    
    
};
