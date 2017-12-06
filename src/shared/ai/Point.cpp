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
        switch (d)
        {
            case Direction::NORDOUEST:
                return (y>0) ? Point(x,y-1,weight+1) : Point(-1,-1,-1);
                break;
            case Direction::NORDEST:
                return (y>0 && x<6) ? Point(x+1,y-1,weight+1) : Point(-1,-1,-1);
                break;
            case Direction::EST:
                return (x<6) ? Point(x+1,y,weight+1) : Point(-1,-1,-1);
                break;
            case Direction::SUDEST:
                return (y<6) ? Point(x,y+1,weight+1) : Point(-1,-1,-1);
                break;
            case Direction::SUDOUEST:
                return (y<6 && x>0) ? Point(x-1,y+1,weight+1) : Point(-1,-1,-1);
                break;
            case Direction::OUEST:
                return (x>0) ? Point(x-1,y,weight+1) : Point(-1,-1,-1);
                break;
            default:
                return Point(-1,-1,-1);
                break;   
        }
    }
    // Setters and Getters
    int Point::getX() const {return x;}
    void Point::setX(int x) {this->x = x; }
    int Point::getY() const { return y; }
    void Point::setY(int y) {this->y = y; }
    int Point::getWeight() const {return weight; }
    void Point::setWeight(int weight) {this->weight = weight; }
}
