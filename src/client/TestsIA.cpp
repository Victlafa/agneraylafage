/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TestsIA.h"


namespace ai {

    void TestsRandomIA() 
    {
        srand(time(NULL));
        
        // On initialise un moteur
        // On choisit les cuisiniers pour le joueur 1
        engine::Engine moteur(CreaturesID::COOKERS);
        
        // On initialise une ia
        RandomAI ia(rand()%30000);
 
        ia.run(moteur);
        
    }
    
    void TestsHeuristicIA()
    {
        srand(time(NULL));
        
        // On initialise un moteur
        // On choisit les mineurs pour le joueur 1
        engine::Engine moteur(CreaturesID::MINERS);
        
        // On initialise une ia
        HeuristicAI ia(rand()%30000);
 
        ia.run(moteur);
    }
    
}