/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "HeuristicAI.h"
#include <iostream>
#include "../shared/engine.h"


namespace ai
{
    HeuristicAI::HeuristicAI (int randomSeed)
    {
        randGen.seed(randomSeed);
    }
    
    void HeuristicAI::run (engine::Engine& moteur)
    {
        // On initialise les attributs de l'IA
        this->initIA(moteur);
        
        // On s'arrange pour que l'IA ait au moins une creature a placer en stock
        //moteur.getPlayer(2)->setCreaturesLeft(6);
        
        // On lui attribue trois cellules speciales
//        std::vector<std::string> speCells;
//        speCells.push_back("sky");
//        speCells.push_back("barbecue");
//        speCells.push_back("candy");
//        moteur.getPlayer(2)->setSpeCellsNames(speCells);
        
        //std::cout << moteur.getPlayer(2)->getSpeCellsNames()[0] << std::endl;
        //std::cout << moteur.getPlayer(2)->getSpeCellsNames()[1] << std::endl;
        //std::cout << moteur.getPlayer(2)->getSpeCellsNames()[2] << std::endl;
        
        std::vector<int> coordsJoueur1 = playerCellResearch(moteur,1);
        std::vector<int> coordsJoueur2 = playerCellResearch(moteur,2);
        
        std::cout << "Nombre de cellules appartenant au joueur 1 : " << coordsJoueur1.size()/2 << std::endl;
        std::cout << "Nombre de cellules appartenant au joueur 2 : " << coordsJoueur2.size()/2 << std::endl;
        
        // On souhaite tester la capacité speciale liee au ciel
        // On doit pour cela choisir une cellule adverse à attaquer sur la carte ainsi qu'une case de depart
        std::vector<int> choixCellules = skyCellResearch(moteur);
        
        // On ajoute la commande associee à cette attaque à la liste des commandes
        listCommands.push_back( std::shared_ptr<engine::Command> ( new engine::SpecialCellCommand(choixCellules[0],choixCellules[1],choixCellules[2],choixCellules[3],2,"sky") ) );
        
        // On souhaite introduire une commande de deplacement/conquete
        // On tire pour cela au sort une cellule du joueur 1 à attaquer
        
        
        
        listCommands.at(0)->execute(moteur.getState());
        std::cout << "Une commande de l'ia heuristique a été en principe executée !" << std::endl;
        
        // On vide la liste des commandes
        listCommands.clear();
    }
    
    // On cherche une cellule attaquante pour l'IA ainsi qu'une cellule destination adverse ADJACENTE
    std::vector<int> HeuristicAI::moveCellResearch (engine::Engine& moteur)
    {
        // On recupere la liste des coordonnees des cellules possedees par le joueur reel
        std::vector<int> real_cells = this->playerCellResearch(moteur,1);
        // On recupere la liste des coordonnees des cellules possedees par l'IA
        std::vector<int> ia_cells = this->playerCellResearch(moteur,2);
        // On declare un tableau où on mettra temporairement les coordonnees des cellules de l'IA qui ont des cellules du joueur 1 pour voisines
        std::vector<int> adjacent_cells;
        // On declare le tableau qui comportera les coordonnees de destination
        std::vector<int> finalDestination;
        // On declare le tableau qui comportera les coordonnees à renvoyer
        std::vector<int> coordsMove(4);
        
        int ligne_ia, colonne_ia, random;
        
        // On fait le tour de la liste de l'ia
        for (int i = 0; i < (int)(ia_cells.size()/2); i++)
        {
            // Pour chaque cellule de l'ia on explore toutes les cellules du joueur 1
            for (int j = 0; j < (int)(real_cells.size()/2); j++)
            {
                // Si on trouve pour la cellule de l'ia au moins une cellule adjacente appartenant au joueur 1
                if (isAdjacent(ia_cells[2*i],ia_cells[2*i+1],real_cells[2*i],real_cells[2*i+1]))
                {
                    // On ajoute les coordonnees de l'ia à adjacent_cells
                    adjacent_cells.push_back(ia_cells[2*i]);
                    adjacent_cells.push_back(ia_cells[2*i+1]);
                }
            }
        }
            
        // On tire au hasard une cellule parmi les cellules de l'IA voisines du joueur 1
        random = rand()%((int)(adjacent_cells.size()/2));
        ligne_ia = adjacent_cells[2*random];
        colonne_ia = adjacent_cells[2*random + 1];
        
        // Parmi les cellules adjacentes à cette dernière cellule, on en tire une au hasard :
        finalDestination = this->inAdjacentResearch(moteur,ligne_ia,colonne_ia);
        
        coordsMove[0] = ligne_ia;
        coordsMove[1] = colonne_ia;
        coordsMove[2] = finalDestination[0];
        coordsMove[3] = finalDestination[1];
        
        return coordsMove;
    }
}