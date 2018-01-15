/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GameService.hpp"

using namespace server;
using namespace std;

GameService::GameService () : AbstractService("/game") {
    beginner = rand()%2 + 1;
}

HttpStatus GameService::get (Json::Value& out, int id) const {
    
    // Si on souhaite recuperer le numero du joueur qui debute la partie
    if (id == 0)
    {
        cout << "GameService::get - Joueur qui commence : " << beginner << endl;
        out["beginner"] = beginner;
    }
        
    else throw ServiceException(HttpStatus::NOT_FOUND,"GameService::get - Invalid game information id");
    
    return HttpStatus::OK;
}
