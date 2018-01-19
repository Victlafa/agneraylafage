/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GameService.hpp"
#include <fstream>
#include <iostream>

using namespace server;
using namespace std;

GameService::GameService () : AbstractService("/game"), game() {}

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
        out[id-3] = game.listCommands[id-3];
    else throw ServiceException(HttpStatus::NOT_FOUND,"GameService::get - Invalid game information id");
    
    return HttpStatus::OK;
}

HttpStatus GameService::post (const Json::Value& in, int id)
{
    //std::cout << "GameService::post entree dans la methode" << std::endl;
    if (id == 2)
    {
        if (in.isMember("player")) game.currentPlayer = in["player"].asInt();
    }
    else throw ServiceException(HttpStatus::NOT_FOUND,"GameService::post - Invalid game information id");
    
    //std::cout << "GameService::post sortie de la methode" << std::endl;
    return HttpStatus::OK;
}

HttpStatus GameService::put (Json::Value& out, const Json::Value& in)
{
    std::cout << "GameService::put entree dans la methode" << std::endl;
    
    std::ofstream file("./src/command.txt", std::ios::app);
    
    if(file.bad()){
        std::cout << "Erreur avec le fichier command.txt" << std::endl;
        return HttpStatus::SERVER_ERROR;
    }
    
    Json::StyledWriter styledWriter;
    
    game.listCommands[game.idmax] = in;
    out[game.idmax] = in;
    game.idmax++;
    
    file << styledWriter.write(game.listCommands);
    
    file.close();
    
    return HttpStatus::OK;
}


