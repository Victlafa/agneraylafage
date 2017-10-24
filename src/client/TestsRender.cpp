/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestsRender.cpp
 * Author: pahtatorr
 * 
 * Created on 22 octobre 2017, 11:28
 */

#include "TestsRender.h"
#include "state/State.h"
#include "render/Layer.h"

namespace render
{
    void TestsStateLayer()
    {
//        std::cout << "DEBUT TESTS STATELAYER" << std::endl << std::endl;
//
//        std::unique_ptr<StateLayer> stLayer(new StateLayer(new state::State()));
//
//        std::cout << "Test StateLayer - Init StateLayer : ";
//        std::cout << ((NULL != stLayer) ? "OK" : "KO") << std::endl;
//        
//        std::cout << "Test StateLayer - Getter/Setter surface : ";
//        stLayer//.setSurface(new Surface());
//        std::cout << ((NULL != stLayer.getSurface()) ? "OK" : "KO") << std::endl;
//        
//        std::cout << "Test StateLayer - Init state : ";
//        std::cout << ((NULL != stLayer.state) ? "OK" : "KO") << std::endl;
    }
    
    void TestsElementTabLayer()
    {
        std::cout << "DEBUT TESTS ELEMENTTABLAYER" << std::endl << std::endl;
        
        std::unique_ptr<state::ElementTab> grid(new state::ElementTab(7, 5));
        ElementTabLayer gridLayer(*grid);
        gridLayer.initSurface(0);

        std::cout << "Test ElementTabLayer - Init ElementTabLayer : ";
        std::cout << ((NULL != gridLayer) ? "OK" : "KO") << std::endl;

        std::cout << "Test ElementTabLayer - Getter/Setter surface : ";
        gridLayer.setSurface(new Surface());
        std::cout << ((NULL != gridLayer.getSurface()) ? "OK" : "KO") << std::endl;
        
        
    }
}