/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Game.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace server
{
    Game::Game() {
        moteur = NULL;
        beginner = 1; //rand()%2 + 1;
        party = rand()%100 + 1;
        cout << "Game::Game - numero de la partie : " << party << endl;
        currentPlayer = beginner;
        status = GameStatus::CREATING;
        listCommands = Json::Value(Json::arrayValue);
    };
    
    Game::~Game () {};
    engine::Engine* Game::getEngine () { return moteur; }
    
    void Game::run ()
    {}
    
    // Setters and Getters
    GameStatus Game::getStatus() const { return status; }
    void Game::setStatus(GameStatus status) { this->status = status; }
}

