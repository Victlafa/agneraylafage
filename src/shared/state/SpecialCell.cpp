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

    SpecialCellID SpecialCell::getSpecialCellType() const{
        return this->specialCellType;
    }
    
    void SpecialCell::setSpecialCellType(SpecialCellID specialCellType){
        this->specialCellType=specialCellType;
    }
    
};


