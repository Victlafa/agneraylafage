/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "state.h"
#include "Layer.h"

using namespace std;

namespace render
{
    Layer::Layer ()
    {
        this->surface = std::unique_ptr<Surface>(new Surface());
        
    }
    
    Layer::~Layer() {}
    
    const std::unique_ptr<Surface>& Layer::getSurface () const
    {
        return surface;
    }
    void Layer::setSurface (Surface* surface)
    {
        if (surface)
            this->surface.reset(surface);
        else
            this->surface = std::unique_ptr<Surface>(surface);
    }
    
    void Layer::printText (int x, int y, const std::string& msg)
    {
        cout << "Entree dans Layer::printText" << endl;
        sf::Font myFont;
        if (!myFont.loadFromFile("./res/HPS_Extrabold_trial.ttf"))
            std::cout << "Erreur chargement police\n" << std::endl;
        
        sf::Text message(msg,myFont,50.f);
        message.setColor(sf::Color::White);
        message.setPosition(x,y);
    }
    
    // Setters and Getters
    const std::shared_ptr<TileSet>& Layer::getTileset() const
    {
        //std::cout << "gettileset" << std::endl;
        return this->tileset;
    }
    
    void Layer::setTileset(const std::shared_ptr<TileSet>& tileset)
    {
        if (tileset.get())
            this->tileset.reset(tileset.get());
        else
            this->tileset = std::shared_ptr<TileSet>(tileset.get());
    }
}