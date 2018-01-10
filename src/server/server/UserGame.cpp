/** 
 * @file UserDB.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "UserGame.hpp"
#include "UserGame.h"

using namespace server;

UserGame::UserGame() : idseq(1) {
    
}

const User* UserGame::getUser (int id) const {
    auto ite = users.find(id);
    if (ite == users.cend())
        return nullptr;
    return ite->second.get();
}

int UserGame::addUser (unique_ptr<User> user) {
    int id = idseq++;
    users.insert(std::make_pair(id,std::move(user)));
    return id;
}

void UserGame::setUser (int id, unique_ptr<User> user) {
    users[id] = std::move(user);
    if (id > idseq) {
        idseq = id;
    }
}

void UserGame::removeUser (int id) {
    auto ite = users.find(id);
    if (ite == users.end())
        return;
    users.erase(ite);
    idseq--;
}

const std::map<int,std::unique_ptr<User> >& UserGame::getUsers() const { return users; }


