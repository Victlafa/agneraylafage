/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Game.h"
#include <cstdlib>

namespace server
{
    Game::Game() {
        moteur = NULL;
        beginner = rand()%2 + 1;
        party = rand()%100 + 1;
        currentPlayer = beginner;
        status = GameStatus::CREATING;
    };
    
    Game::~Game () {};
    engine::Engine* Game::getEngine () { return moteur; }
    
    void Game::run ()
    {}
    
    // Setters and Getters
    GameStatus Game::getStatus() const { return status; }
    void Game::setStatus(GameStatus status) { this->status = status; }
}

