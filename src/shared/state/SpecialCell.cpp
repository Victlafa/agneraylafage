#include "SpecialCell.h"
#include "Cell.h"

namespace state
{

    SpecialCell::SpecialCell (ID type, std::string resType, int resNbr, int x, int y, CellState state) : Cell(type, state) {
        
        this->resNbr=resNbr;
        this->resType=resType;
        this->x=x;
        this->y=y;
    }
    
    SpecialCell::~SpecialCell(){};
    
    SpecialCell::SpecialCell(const state::Element& elem){
        this->x=elem.getX();
        this->y=elem.getY();
        this->creaturesNbr=elem.getCreaturesNbr();
    }

    bool SpecialCell::operator== (SpecialCell otherSpecialCell) {
        bool rNbr = this->resNbr == otherSpecialCell.getResNbr();
        bool rtype = this->resType == otherSpecialCell.getResType();
        bool cellType = this->getElemType() == otherSpecialCell.getElemType();
        bool posX = this->x == otherSpecialCell.getX();
        bool posY = this->y == otherSpecialCell.getY();

        if (rNbr && rtype && cellType && posX && posY)
            return true;
        else
            return false;
    }
    
};


