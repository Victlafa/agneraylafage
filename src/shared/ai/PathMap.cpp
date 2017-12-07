/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PathMap.h"

namespace ai
{
    const std::vector<Direction> directions { Direction::NONE, Direction::NORDOUEST, Direction::NORDEST, Direction::EST, Direction::SUDEST, Direction::SUDOUEST, Direction::OUEST };
    
    PathMap::PathMap()
    {
        width = 7;
        height = 5;
        weights.assign(29,-1);
    }
    
    PathMap::PathMap (const Point& start, const Point& destination, state::ElementTab* grid) : start(start), destination(destination)
    {
        weights.assign(29,-1);
        width = grid->getWidth();
        height = grid->getHeight();
        init(grid);
        //this->destination = destination;
    }
    
    int PathMap::getWeight (const Point& p) const { return weights.at(p.getY()*this->width + p.getX()); }
    void PathMap::setWeight (const Point& p, int weight) 
    { 
        weights.at(p.getY()*this->width + p.getX()) = weight;
    }
    const std::vector<int>& PathMap::getWeights () const { return weights; }
    const Point& PathMap::getStart () const { return start; }
    const Point& PathMap::getDestination () const { return destination; }
    
    void PathMap::init (state::ElementTab* grid)
    {
        
    }
    
    bool PathMap::dijkstra ()
    {
        bool found = false;
        // On introduit le point de depart dans la queue
        queue.push(Point(0,0,0));
        
        // Tant qu'elle n'est pas vide
        while (!queue.empty())
        {
            // On en recupere le premier element
            auto p = queue.top(); queue.pop();
            // On en change le poids
            setWeight(p,p.getWeight());
            // Si on se trouve sur le point d'arrivée
            if (p.getX() == destination.getX() && p.getY() == destination.getY())
                found = true;
            // En un point donné, on explore toutes les directions
            for (Direction d : directions)
            {
                auto pp = p.transform(d);
                if (pp.getX() != -1 && pp.getY() != -1 && pp.getWeight() != -1)
                {
                    pp.setWeight(p.getWeight() + 1);
                    // Si le noeud fils a un poids superieur à son pere
                    if (this->getWeight(pp) > p.getWeight())
                        // On ajoute le fils à la queue
                        queue.push(pp);
                }
                
            }
            
        }
        
        return found;
        
        
    }
    void PathMap::update (const state::ElementTab& grid) {}
}