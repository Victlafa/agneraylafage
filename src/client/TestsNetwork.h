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
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

using namespace state;
using namespace ai;
using namespace std;
using namespace render;

namespace server{
    void TestsNetwork();
    void affichageListe();
    void ajoutUser();
    void suppressionUser(string);
    int getPlayerNbr(sf::Http*);
    int getPartyNbr(sf::Http*);
    int getPartyBeginner(sf::Http*);
    int getOccupedPlayer(sf::Http*);
    void setOccupedPlayer(sf::Http*);
    string translateType (CreaturesID);
    void nouvellePartie(int,int);
    void* routine_thread(void*,void*);
}

#endif /* TESTSNETWORK_H */

