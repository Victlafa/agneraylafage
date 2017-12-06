/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PathMap.h"

namespace ai
{
    PathMap::PathMap (const state::ElementTab& grid)
    {
        weights.assign(29,-1);
        width = grid.getWidth();
        height = grid.getHeight();
        init(grid);
    }
    
    int PathMap::getWeight (const Point& p) const { return p.getWeight(); }
    void PathMap::setWeight (const Point& p, int weight) { p.setWeight(weight); }
    std::vector<int>& PathMap::getWeights () const { return weights; }
    void PathMap::init (const state::ElementTab& grid)
    {
        
    }
    void PathMap::addSink (Point p) {}
    void PathMap::update (const state::ElementTab& grid) {}
}