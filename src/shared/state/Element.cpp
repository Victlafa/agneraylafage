#include "Element.h"

namespace state
{
    // Constructor :
    Element::Element(){
        x = 0;
        y = 0;
        creaturesNbr = 0;
    }
    
    Element::~Element() {}
    
    bool Element::operator== (Element otherElement)
    {
        bool coordX = (this->x == otherElement.getX());
        bool coordY = (this->y == otherElement.getY());
        bool creaNbr = (this->creaturesNbr == otherElement.getCreaturesNbr());
        
        if (coordX && coordY && creaNbr)
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
    
    
};
