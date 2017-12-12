#include <SFML/Graphics.hpp>
#include "StateLayer.h"
#include "StateTileSet.h"

namespace render{

    StateLayer::StateLayer(const state::State& state) : state(state) {
        this->tileset = std::shared_ptr<StateTileSet>(nullptr);
        this->surface = std::shared_ptr<Surface>(nullptr);
    }

    void StateLayer::initSurface(){
        
        // Affichage du titre du jeu
        this->printText(311,100,"Welcome to the garden !");
    }
    
}