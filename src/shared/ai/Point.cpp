/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Point.h"

namespace ai
{
    Point::Point (int x, int y, int w) : x(x), y(y), weight(w) {}
    
    Point Point::transform (Direction d)
    {
//        switch (d)
//        {
//            case Direction::NORDOUEST:
//                if ()
//        }
    }
    // Setters and Getters
    int Point::getX() const {return x;}
    void Point::setX(int x) {this->x = x; }
    int Point::getY() const { return y; }
    void Point::setY(int y) {this->y = y; }
    int Point::getWeight() const {return weight; }
    void Point::setWeight(int weight) {this->weight = weight; }
}
