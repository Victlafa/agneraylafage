/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GameService.hpp"

using namespace server;
using namespace std;

GameService::GameService () : AbstractService("/game") {
    srand(time(NULL));
    beginner = rand()%2 + 1;
    party = rand()%100 + 1;
    player = beginner;
}

HttpStatus GameService::get (Json::Value& out, int id) const {
    
    // Si on souhaite recuperer le numero de la partie
    if (id == 0)
        out["party"] = party;
    // Si on souhaite recuperer le numero du joueur qui debute la partie
    else if (id == 1)
        out["beginner"] = beginner;
    // Si on souhaite recuperer le numero du joueur qui est en train de jouer
    else if (id == 2)
        out["player"]= player;
        
    else throw ServiceException(HttpStatus::NOT_FOUND,"GameService::get - Invalid game information id");
    
    return HttpStatus::OK;
}

HttpStatus GameService::post (const Json::Value& in, int id)
{
    //cout << "GameService::post - entree dans methode" << endl;
    //cout << "Affichage entree : " << endl;
    //cout << in.toStyledString() << endl;
    if (id == 2)
    {
        if (in.isMember("player")) player = in["player"].asInt();
    }
    else throw ServiceException(HttpStatus::NOT_FOUND,"GameService::post - Invalid game information id");
    
    //cout << "GameService::post - fin methode, valeur de player : " << player << endl;
    return HttpStatus::OK;
}
