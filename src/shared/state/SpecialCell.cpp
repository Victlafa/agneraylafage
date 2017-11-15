#include "SpecialCell.h"
#include "Cell.h"
#include "SpecialCellID.h"

namespace state
{

    SpecialCell::SpecialCell (SpecialCellID type, std::string resType, int resNbr, int x, int y) : Cell(CellTypeID::SPECIAL) {
        this->resNbr=resNbr;
        this->resType=resType;
        this->specialCellType=type;
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
        bool cellType = this->specialCellType == otherSpecialCell.getSpecialCellType();
        bool posX = this->x == otherSpecialCell.getX();
        bool posY = this->y == otherSpecialCell.getY();

        if (rNbr && rtype && cellType && posX && posY)
            return true;
        else
            return false;
    }
    
    SpecialCellID SpecialCell::getSpecialCellType() const{
        return this->specialCellType;
    }
    
    void SpecialCell::setSpecialCellType(SpecialCellID specialCellType){
        this->specialCellType=specialCellType;
    }
    
};


