/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "RandomAI.h"
#include "engine/Engine.h"

namespace ai{
    
    RandomAI::RandomAI (int randomSeed)
    {
        randGen.seed(randomSeed);
    }
    
    void RandomAI::run (const engine::Engine& moteur) {}
}
