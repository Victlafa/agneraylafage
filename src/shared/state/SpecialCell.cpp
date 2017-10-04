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
        SpecialCellID id = 1;
        return id;
    }
    
    SpecialCellID SpecialCell::getSpecialCellType() const{
        return specialCellType;
    }
    
    void setSpecialCellType(SpecialCellID specialCellType){
        specialCellType=specialCellType;
    }
};


