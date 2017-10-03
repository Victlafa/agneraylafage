#include "Element.h"

namespace state
{
    // Constructor :
    Element::Element(){}
    
    // Getters and setters :
    int Element::getX() const{
        return this->x;
    }
    void Element::setX(int x);
    int Element::getY() const;
    void Element::setY(int y);
    int Element::getCreaturesNbr() const;
    void Element::setCreaturesNbr(int creaturesNbr);
    
    
};
