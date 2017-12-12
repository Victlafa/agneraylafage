#include <SFML/Graphics.hpp>
#include "StateLayer.h"
#include "StateTileSet.h"
#include <iostream>

using namespace std;

namespace render{

    StateLayer::StateLayer(const state::State& state) : state(state) {
        this->tileset = std::unique_ptr<StateTileSet>(nullptr);
        this->surface = std::unique_ptr<Surface>(new Surface());
    }

    void StateLayer::initSurface(){
        
        cout << "Entree dans StateLayer::initSurface" << endl;
        
        // Affichage du fond d'écran
        this->surface->loadTexture("background1.png");
        
        
        // Affichage du titre du jeu
        //this->printText(311,100,"Welcome to the garden !");
    }
    
}