#include <SFML/Graphics.hpp>
#include "StateLayer.h"

namespace render{

    StateLayer::StateLayer(const state::State& state){
        this->state = state;
    }

    void initSurface(){
        //Ajouter dans les textures un alphabet pour pouvori afficher 
        //l'état du joueur...
    
    }
    
}