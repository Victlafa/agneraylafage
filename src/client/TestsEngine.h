/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestsEngine.h
 * Author: pahtatorr
 *
 * Created on 7 novembre 2017, 09:35
 */

#ifndef TESTSENGINE_H
#define TESTSENGINE_H

#include "../shared/state.h"
#include "../shared/engine.h"
#include <iostream>

namespace engine{
    void TestsFightCommand();
    void TestsMoveCharCommand();
    void TestsPoisonCommand();
    void TestsNewGameCommand();
}

#endif /* TESTSENGINE_H */
