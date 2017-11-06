/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "state.h"
#include "Tile.h"

namespace render
{
    // Constructeurs :
    
    Tile::Tile (){ }
    Tile::Tile (int x, int y, int w, int h)
    {
        this->x = x;
        this->y = y;
        this->height = h;
        this->width = w;
    }
    
    // Setters and Getters
    int Tile::getX() const { return this->x; }
    void Tile::setX(int x) {this->x = x;}
    int Tile::getY() const {return this->y; }
    void Tile::setY(int y) {this->y = y;}
    int Tile::getWidth() const {return this->width;}
    void Tile::setWidth(int width) {this->width = width;}
    int Tile::getHeight() const {return this->height;}
    void Tile::setHeight(int height) {this->height = height;}
}
