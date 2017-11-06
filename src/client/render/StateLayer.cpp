#include <SFML/Graphics.hpp>
#include "StateLayer.h"
#include "StateTileSet.h"

namespace render{

    StateLayer::StateLayer(const state::State& state) : state(state) {
        this->tileset = std::shared_ptr<StateTileSet>(new StateTileSet());
    }

    void StateLayer::initSurface(){
        //this->surface = 
    }
    
}