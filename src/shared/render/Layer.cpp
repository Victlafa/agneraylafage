/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Layer.h"

namespace render
{
    Layer::Layer ()
    {
        this->surface = std::unique_ptr<Surface>(new Surface());
        this->tileset = std::shared_ptr<TileSet>(new TileSet());
    }
    
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
    
    //void Layer::printText (int x, int y, const std::string& msg, size_t tileMinIdx, size_t tileMaxIdx);
    // Setters and Getters
    const std::shared_ptr<TileSet>& Layer::getTileset() const
    {
        return this->tileset;
    }
    void Layer::setTileset(const std::shared_ptr<TileSet>& tileset)
    {
        if (tileset)
            this->tileset.reset(tileset);
        else
            this->tileset = std::shared_ptr<TileSet>(tileset);
    }
}