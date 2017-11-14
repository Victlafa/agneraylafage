/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "RandomAI.h"

namespace ai{
    
    RandomAI::RandomAI (int randomSeed, const engine::Engine& moteur) : moteur(moteur)
    {
        randGen.seed(randomSeed);
    }
    RandomAI::run () {}
}
