#include "SpecialCell.h"
#include "Cell.h"
#include "SpecialCellID.h"

namespace state
{

    SpecialCell::SpecialCell(SpecialCellID type, std::string resType, int resNbr){
        this->type = type;
        this->neededResType = resType;
        this->neededResNbr = resNbr;
    }
    

    std::string SpecialCell::getResType() {
        return neededResType;
    }

    void SpecialCell::setResType(std::string res) {
        neededResType = res;
    }

    int SpecialCell::getResNbr() {
        return neededResNbr;
    }

    void SpecialCell::setResNbr(int nbr) {
        neededResNbr = nbr;
    }
};


