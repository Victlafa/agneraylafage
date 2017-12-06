/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PointCompareWeight.h"

namespace ai
{
    // Renvoie true si le poids de a est plus petit que celui de b
    bool PointCompareWeight::operator() (const Point& a, const Point& b)
    {
        return a.getWeight() < b.getWeight();
    }
}
