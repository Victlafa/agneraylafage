/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cell.h"

namespace state
{
    int Cell::getx (){
        return ;
    }
    
    void Cell::setx (int x);
    int Cell::gety ();
    void Cell::sety (int y);
    virtual Cell::TypeID const getTypeID () = 0;
    // Setters and Getters
    const CreaturesGroup& getPositionedOn() const;
    void setPositionedOn(const CreaturesGroup& positionedOn);
    
    
};

