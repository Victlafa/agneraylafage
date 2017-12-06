/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PointCompareWeight.h"

namespace ai
{
    bool PointCompareWeight::operator() (const Point& a, const Point& b)
    {
        if (a.getWeight() == b.getWeight())
            return true;
        else
            return false;
    }
}
