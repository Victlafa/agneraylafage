/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestRandomIA.h
 * Author: mikhan
 *
 * Created on 16 novembre 2017, 21:05
 */

#ifndef TESTRANDOMIA_H
#define TESTRANDOMIA_H

#include "../shared/state.h"
#include "../shared/engine.h"
#include "../client/render.h"
#include "../shared/ai.h"
#include <iostream>
#include <vector>

#include "engine/MoveCommand.h"
//#include "ai/AI.h"
//#include "ai/RandomAI.h"
#include <time.h>

using namespace state;

namespace ai{
    void TestsRandomIA();
    void TestsHeuristicIA();
    void TestsRollbackMove();
    void TestsPathFinding();
    
}

#endif /* TESTRANDOMIA_H */

