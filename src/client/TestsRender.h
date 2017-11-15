/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestsRender.h
 * Author: pahtatorr
 *
 * Created on 22 octobre 2017, 11:28
 */

#ifndef TESTSRENDER_H
#define TESTSRENDER_H

//#include "state.h"
#include "../shared/state.h"
#include "render.h"
#include <iostream>
#include <time.h>

using namespace state;

namespace render
{
    //void TestsStateLayer();
    void TestsElementTabLayer();
    void TestInitMap();
    void TestAffichage(State& etat);
    void TestAffichage2();
    void TestAffichage3();
}

#endif /* TESTSRENDER_H */
