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
 
<<<<<<< HEAD
    SpecialCellID SpecialCell::getSpecialCellType() const{
=======
    const SpecialCellID SpecialCell::getSpecialCellID(){
>>>>>>> a3b38b0d7950c29f95b0c4db7407c3f51c009ba2
        return specialCellType;
    }
    
    void SpecialCell::setSpecialCellType(SpecialCellID specialCellType){
        this->specialCellType=specialCellType;
    }
    
};


