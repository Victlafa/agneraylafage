/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestsNetwork.h
 * Author: mikhan
 *
 * Created on 19 décembre 2017, 15:50
 */

#ifndef TESTSNETWORK_H
#define TESTSNETWORK_H

#include <SFML/Network.hpp>
#include <iostream>
#include "stdlib.h"
#include "json/json.h"
#include "state.h"
#include "../shared/ai.h"
#include "../shared/engine.h"
#include "../shared/state.h"
#include "render.h"

#include <time.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <sys/types.h>

#include <fstream>

using namespace engine;
using namespace state;
using namespace ai;
using namespace std;
using namespace render;

namespace server{
    void TestsNetwork();
    void affichageListe();
    bool ajoutUser();
    void suppressionUser(string);
    int getServerInfo(sf::Http*, std::string);
    int getCreaOtherPlayer(sf::Http*);
    void setOccupedPlayer(sf::Http*, int);
    bool verifAdversaryCommands(sf::Http*);
    Json::Value getAdversaryCommands(sf::Http*);
    string translateType (CreaturesID);
    void nouvellePartie(int,int);
    void* routine_thread(void*,void*);
}

#endif /* TESTSNETWORK_H */

