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
 
    const SpecialCellID SpecialCell::getSpecialCellID(){
        return specialCellType;
    }
    
    void SpecialCell::setSpecialCellType(SpecialCellID specialCellType){
        this->specialCellType=specialCellType;
    }
    
};


