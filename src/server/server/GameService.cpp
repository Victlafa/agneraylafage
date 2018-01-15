/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GameService.h"

using namespace server;

GameService::GameService () : AbstractService("/game") {
    
}

HttpStatus GameService::get (Json::Value& out, int id) const {
    
    // Si on souhaite recuperer le numero du joueur qui debute la partie
    if (id == 0)
        out["beginner"] = rand()%2 + 1;
    else throw ServiceException(HttpStatus::NOT_FOUND,"GameService::get - Invalid game information id");
    
    return HttpStatus::OK;
}
