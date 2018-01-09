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

using namespace state;
using namespace std;

namespace server{
    void TestsNetwork();
    void affichageListe();
    void ajoutUser();
    string translateType (CreaturesID);
}

#endif /* TESTSNETWORK_H */

