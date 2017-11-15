#include <iostream>
#include "Element.h"

namespace state
{
    // Constructor :
    Element::Element(){
        x = 0;
        y = 0;
        creaturesNbr = 0;
<<<<<<< HEAD
        //std::cout << "Initialisation d'un element lambda\n" << std::endl;
=======
        cellState = CellState::NORMAL;
        type = TypeID::CELL;
        elemType = ID::GRASS;
        //std::cout << this << std::endl;
>>>>>>> c836bcfb3b8edfe27cda0d2258311ea44d93de9c
    }
    
    Element::Element (TypeID type){
        x = 0;
        y = 0;
        creaturesNbr = 0;
<<<<<<< HEAD
        elemType = type;
        //std::cout << "Initialisation d'un element de type " << type << "\n" << std::endl;
=======
        cellState = CellState::NORMAL;
        type = type;
        elemType = ((type == TypeID::CELL) ? ID::GRASS : ID::BLACKSMITH);
>>>>>>> c836bcfb3b8edfe27cda0d2258311ea44d93de9c
    }
    
    Element::~Element() {
        //std::cout << "Appel au destructeur Element" << std::endl;
    }
    
    bool Element::operator== (Element otherElement)
    {
        bool coordX = (this->x == otherElement.getX());
        bool coordY = (this->y == otherElement.getY());
        bool creaNbr = (this->creaturesNbr == otherElement.getCreaturesNbr());
       // bool type = (this->type == otherElement.getType());
        bool elemType = (this->elemType == otherElement.getElemType());
        
        if (coordX && coordY && creaNbr && elemType)
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
    
    ID Element::getElemType() const{
        std::cout << "get elemtype" << std::endl;
        return this->elemType;
    }
    
    void Element::setElemType(ID elemType)
    {
        this->elemType = elemType;
    }
    
    /*
    Element::Element(const Element& elem)
    {
        if(elem.
    }*/
                
};
