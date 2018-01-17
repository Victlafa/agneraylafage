/** 
 * @file UserService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "UserService.hpp"
#include "TestsNetwork.h"
#include "../../shared/state/CreaturesID.h"
#include "../../shared/engine.h"

using namespace server;
using namespace state;

state::CreaturesID translateStringType (string typeElement)
    {
        if (typeElement == "BLACKSMITHS")
            return state::CreaturesID::BLACKSMITHS;
        else if (typeElement == "COOKERS") 
            return state::CreaturesID::COOKERS;
        else if (typeElement == "LUMBERJACKS")
            return state::CreaturesID::LUMBERJACKS;
        else if (typeElement == "MINERS")
            return state::CreaturesID::MINERS;
        else
            throw std::runtime_error("UserService - translateType (string -> CreaturesID) - utilisation d'un argument non valable");
    }

UserService::UserService (UserGame& userGame) : AbstractService("/user"),
    userGame(userGame) {
}

HttpStatus UserService::get (Json::Value& out, int id) const {
    
    // Si id = 0, on renvoie le nombre de joueurs connectes sur le serveur
    if (id == 0)
    {
        out["Players_on_the_server"] = userGame.getUsers().size();
    }
        
    // Si id > 0, on peut potentiellement renvoyer un joueur
    else if (id > 0)
    {
        const User* user = userGame.getUser(id);
        if (!user) throw ServiceException(HttpStatus::NOT_FOUND,"UserService::get - Invalid user id");
        
        out["name"] = user->name;
        out["creatures"] = user->creatures;
    }
    
    else throw ServiceException(HttpStatus::NOT_FOUND,"UserService::get - Invalid user id");
    
    return HttpStatus::OK;
}

HttpStatus UserService::post (const Json::Value& in, int id) {
    const User* user = userGame.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    unique_ptr<User> usermod (new User(*user));
    if (in.isMember("name")) {
        usermod->name = in["name"].asString();
    }
    if (in.isMember("creatures")) {
        usermod->creatures = translateStringType(in["creatures"].asString());
    }
    
    this->userGame.setUser(id,std::move(usermod));
    return HttpStatus::NO_CONTENT;
}

HttpStatus UserService::put (Json::Value& out, const Json::Value& in) {
    std::string name = in["name"].asString();
    std::string cr = in["creatures"].asString();
    state::CreaturesID crea = translateStringType(cr);
    out["id"] = userGame.addUser(move(std::unique_ptr<User>(new User(name,crea))));
    return HttpStatus::CREATED;
}

HttpStatus UserService::remove (int id) {
    const User* user = userGame.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    userGame.removeUser(id);
    return HttpStatus::NO_CONTENT;
}

