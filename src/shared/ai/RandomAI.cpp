/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "RandomAI.h"
#include "engine/Engine.h"
#include "../shared/state.h"
#include <iostream>

using namespace std;

namespace ai{
    
    RandomAI::RandomAI (int randomSeed) : AI()
    {
        randGen.seed(randomSeed);
    }
    
    void RandomAI::run (engine::Engine& moteur) 
    {
        // On tire au hasard un numero de commande
        int randCommand = randGen()%(listCommands.size());
        
        // On applique cette commande
        listCommands.at(randCommand)->execute(moteur.getState());
        
        cout << "Une commande de l'ia a été en principe executée !" << endl;
    }
}
