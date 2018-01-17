/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GameService.hpp"

using namespace server;
using namespace std;

GameService::GameService () : AbstractService("/game") {
    srand(game.party);
}

HttpStatus GameService::get (Json::Value& out, int id) const {
    
    // Si on souhaite recuperer le numero de la partie
    if (id == 0)
        out["party"] = game.party;
    // Si on souhaite recuperer le numero du joueur qui debute la partie
    else if (id == 1)
        out["beginner"] = game.beginner;
    // Si on souhaite recuperer le numero du joueur qui est en train de jouer
    else if (id == 2)
        out["player"] = game.currentPlayer;
    else if (id>2)
        out[id] = game.listCommands[id];
    else throw ServiceException(HttpStatus::NOT_FOUND,"GameService::get - Invalid game information id");
    
    return HttpStatus::OK;
}

HttpStatus GameService::post (const Json::Value& in, int id)
{
    if (id == 2)
    {
        if (in.isMember("player")) game.currentPlayer = in["player"].asInt();
    }
    else throw ServiceException(HttpStatus::NOT_FOUND,"GameService::post - Invalid game information id");
    
    return HttpStatus::OK;
}

HttpStatus GameService::put (const Json::Value& in)
{
    game.listCommands[game.idmax] = in;
    game.idmax++;
    return HttpStatus::OK;
}


