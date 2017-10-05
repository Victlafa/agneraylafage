#include "SpecialCell.h"
#include "Cell.h"
#include "SpecialCellID.h"

namespace state
{

    SpecialCell::SpecialCell (SpecialCellID type, std::string resType, int resNbr, int x, int y){
        this->resNbr=resNbr;
        this->resType=resType;
        this->specialCellType=type;
        this->x=x;
        this->y=y;
    }
    
    SpecialCell::~SpecialCell()
    {
        delete this;
    }

    SpecialCellID SpecialCell::getSpecialCellType() const{
        return this->specialCellType;
    }
    
    void SpecialCell::setSpecialCellType(SpecialCellID specialCellType){
        this->specialCellType=specialCellType;
    }
    
};


