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
        
        // On s'arrange pour que l'IA ait une creature a placer en stock
        moteur.getPlayer(2)->setCreaturesLeft(1);
        
        // On initialise une ia
        RandomAI ia(rand()%30000);
        
        // On initialise une liste de commandes
        std::vector<std::shared_ptr<engine::Command> > commands;
        
        // On cherche dans la grille une cellule appartenant à l'IA ainsi qu'une cellule de destination adjacente pour un deplacement
        std::vector<int> coords = ia.moveCellResearch(moteur);
        // On cherche une cellule dispo pour placer une nouvelle creature de l'IA (venant de son stock) dans la grille
        std::vector<int> placeCoords = ia.placeCellResearch(moteur);
        
        // On ajoute une commande de deplacement
        commands.push_back(std::shared_ptr<engine::Command>(new engine::MoveCommand(coords[0], coords[1], coords[2], coords[3], 2)));
        // On ajoute une commande de placement de nouvelle creature
        commands.push_back(std::shared_ptr<engine::Command>(new engine::PlaceCommand(coords[0], coords[1], 2, (state::ID)moteur.getPlayer(2)->getClanName())));
        
        // On ajoute cette liste de commandes à l'ia
        ia.setListCommands(commands);
        
        // On met l'ia en route
        ia.run(moteur);
        
    }
    
}
