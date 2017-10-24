#include <SFML/Graphics.hpp>
#include "StateLayer.h"

namespace render{

    StateLayer::StateLayer(const state::State& state){
        this->tileset = std::shared_ptr<TileSet>(new StateTileSet());
        this->state = state;
    }

    void StateLayer::initSurface(int type){
        //this->surface = 
    }
    
}