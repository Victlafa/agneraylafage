/** 
 * @file UserService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "UserService.hpp"
#include "UserService.h"

using namespace server;

UserService::UserService (UserGame& userGame) : AbstractService("/user"),
    userGame(userGame) {
    
}

HttpStatus UserService::get (Json::Value& out, int id) const {
    const User* user = userGame.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    out["name"] = user->name;
    out["id"] = user->id;
    out["creatures"] = user->creatures;
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
    if (in.isMember("id")) {
        usermod->id = in["id"].asInt();
    }
    if (in.isMember("creatures")) {
        if(in["creatures"].asString()=="BLACKSMITHS")
            usermod->creatures = state::CreaturesID::BLACKSMITHS;
        else if(in["creatures"].asString()=="COOKERS")
            usermod->creatures = state::CreaturesID::COOKERS;
        if(in["creatures"].asString()=="LUMBERJACKS")
            usermod->creatures = state::CreaturesID::LUMBERJACKS;
        if(in["creatures"].asString()=="MINERS")
            usermod->creatures = state::CreaturesID::MINERS;
    }
    

    this->userGame.setUser(id,std::move(usermod));
    return HttpStatus::NO_CONTENT;
}

HttpStatus UserService::put (Json::Value& out, const Json::Value& in) {
    std::string name = in["name"].asString();
    int id = in["id"].asInt();
    std::string cr = in["creatures"].asString();
    state::CreaturesID crea;
    if(cr=="BLACKSMITHS")
        crea = state::CreaturesID::BLACKSMITHS;
    else if(cr=="COOKERS")
        crea = state::CreaturesID::COOKERS;
    else if(cr=="LUMBERJACKS")
        crea = state::CreaturesID::LUMBERJACKS;
    else if(cr=="MINERS")
        crea = state::CreaturesID::MINERS;
    
    out["id"] = userGame.addUser(move(std::unique_ptr<User>(new User(name,id,crea))));
    return HttpStatus::CREATED;
}

HttpStatus UserService::remove (int id) {
    const User* user = userGame.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    userGame.removeUser(id);
    return HttpStatus::NO_CONTENT;
}

