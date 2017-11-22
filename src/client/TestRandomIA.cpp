/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TestRandomIA.h"

namespace ai {

    void TestRandomIA() 
    {
        srand(time(NULL));
        
        // On initialise un moteur
        engine::Engine moteur;
        
        // On initialise une ia
        RandomAI ia(rand()%30000);
 
        ia.run(moteur);
        
    }
    
}
