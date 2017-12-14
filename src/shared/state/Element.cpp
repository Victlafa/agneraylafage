#include <iostream>
#include "Element.h"

namespace state
{
    // Constructor :
    Element::Element(){
        x = 0;
        y = 0;
        creaturesNbr = 0;
        
        //std::cout << "Initialisation d'un element lambda\n" << std::endl;
        
        cellState = CellState::NORMAL;
        elemType = ID::GRASS;
        player = NULL; //new Player();
        //std::cout << this << std::endl;
    }
    
    Element::Element (ID type, CellState state){
        x = 0;
        y = 0;
        creaturesNbr = 0;
        elemType = type;
        //std::cout << "Element.cpp : Initialisation d'un element de type " << (ID)type << "\n" << std::endl;
        cellState = state;

        //player = Player();

        player = NULL; //new Player();
        //elemType = ((type == TypeID::CELL) ? ID::GRASS : ID::BLACKSMITH);

    }
    
    Element::~Element() {}
    
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
        //std::cout << "Element.cpp : getElemType";
        //if(this!=NULL) std::cout << " : " << this->elemType << std::endl;
        return this->elemType;
    }
    
    void Element::setElemType(ID elemType)
    {
        this->elemType = elemType;
    }
    
    CellState Element::getCellState() const {return cellState;}
    void Element::setCellState(CellState cellState) { this->cellState = cellState; }
    //const Player& Element::getPlayer() const {return player;}
    //void Element::setPlayer(const Player& player) {this->player = player;}
    Player* Element::getPlayer () const { return this->player; }
    void Element::setPlayer (Player* player) { this->player = player; }
    
    ID Element::translateType (std::string typeElement)
    {
        if (typeElement == "ID::BARBECUE")
            return ID::BARBECUE;
        else if (typeElement == "ID::BLACKSMITH")
            return ID::BLACKSMITH;
        else if (typeElement == "ID::CANDY")
            return ID::CANDY;
        else if (typeElement == "ID::COOKER") 
            return ID::COOKER;
        else if (typeElement == "ID::DIRT") 
            return ID::DIRT;
        else if (typeElement == "ID::GRASS") 
            return ID::GRASS;
        else if (typeElement == "ID::LUMBERJACK")
            return ID::LUMBERJACK;
        else if (typeElement == "ID::MINER")
            return ID::MINER;
        else if (typeElement == "ID::POOL")
            return ID::POOL;
        else if (typeElement == "ID::SAND")
            return ID::SAND;
        else if (typeElement == "ID::SKY")
            return ID::SKY;
        else
            throw std::runtime_error("Element::translateType (string -> ID) - utilisation d'un argument non valable");
    }
    
    std::string Element::translateType (ID typeElement)
    {
        if (typeElement == ID::BARBECUE)
            return "ID::BARBECUE";
        else if (typeElement == ID::BLACKSMITH)
            return "ID::BLACKSMITH";
        else if (typeElement == ID::CANDY)
            return "ID::CANDY";
        else if (typeElement == ID::COOKER) 
            return "ID::COOKER";
        else if (typeElement == ID::DIRT) 
            return "ID::DIRT";
        else if (typeElement == ID::GRASS) 
            return "ID::GRASS";
        else if (typeElement == ID::LUMBERJACK)
            return "ID::LUMBERJACK";
        else if (typeElement == ID::MINER)
            return "ID::MINER";
        else if (typeElement == ID::POOL)
            return "ID::POOL";
        else if (typeElement == ID::SAND)
            return "ID::SAND";
        else if (typeElement == ID::SKY)
            return "ID::SKY";
        else
            throw std::runtime_error("Element::translateType (ID -> string) - utilisation d'un argument non valable");
    }
                
};
