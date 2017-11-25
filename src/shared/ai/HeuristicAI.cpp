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
        moteur.getPlayer(2)->setCreaturesLeft(6);
        
        // On lui attribue trois cellules speciales
        std::vector<std::string> speCells;
        speCells.push_back("sky");
        speCells.push_back("barbecue");
        speCells.push_back("candy");
        moteur.getPlayer(2)->setSpeCellsNames(speCells);
        
        //std::cout << moteur.getPlayer(2)->getSpeCellsNames()[0] << std::endl;
        //std::cout << moteur.getPlayer(2)->getSpeCellsNames()[1] << std::endl;
        //std::cout << moteur.getPlayer(2)->getSpeCellsNames()[2] << std::endl;
        
        std::cout << "Joueur 1 : " << moteur.getPlayer(1).get() << std::endl;
        std::cout << "Joueur 2 : " << moteur.getPlayer(2).get() << std::endl;
        
        // On souhaite tester la capacité speciale liee au ciel
        // On doit pour cela choisir une cellule adverse à attaquer sur la carte ainsi qu'une case de depart
        std::vector<int> choixCellules = skyCellResearch(moteur);
        std::cout << "Creatures de l'IA : " << moteur.getState().getCharacters()->get(choixCellules[0], choixCellules[1])->getCreaturesNbr() << std::endl;
        std::cout << "Creatures du joueur 1 : " << moteur.getState().getCharacters()->get(choixCellules[2], choixCellules[3])->getCreaturesNbr() << std::endl;
        
        // On ajoute la commande associee à cette attaque à la liste des commandes
        listCommands.push_back( std::shared_ptr<engine::Command> ( new engine::SpecialCellCommand(choixCellules[0],choixCellules[1],choixCellules[2],choixCellules[3],2,"sky") ) );
        listCommands.at(0)->execute(moteur.getState());
        std::cout << "Une commande de l'ia heuristique a été en principe executée !" << std::endl;
        
        // On vide la liste des commandes
        listCommands.clear();
    }
    
    // On cherche une cellule attaquante pour l'IA ainsi qu'une cellule destination adverse n'importe où sur la carte
    std::vector<int> HeuristicAI::skyCellResearch (engine::Engine& moteur)
    {
        // On va chercher une creature de l'IA dans le moteur donné en argument
        unsigned int ligne = 0;
        unsigned int colonne = 0;
        // On prepare une case de destination
        unsigned int new_ligne = 0;
        unsigned int new_colonne = 0;
        // On recupere le joueur 1
        state::Player* player_real = moteur.getPlayer(1).get();
        // On recupere le joueur 2 (ia)
        state::Player* player_ia = moteur.getPlayer(2).get();
        // De meme avec le tableau de creatures
        state::ElementTab* creaturesTab = moteur.getState().getCharacters().get();
        
        // On declare le tableau de sortie de la methode
        std::vector<int> coordsDestination(4);
        
        // On part à la recherche de cellules adequates dans le tableau
        for (unsigned int i = 0; i < creaturesTab->getHeight(); i++) 
        {
            for (unsigned int j = 0; j < creaturesTab->getWidth(); j++) 
            {
                // Si on trouve un groupe de creatures de pointeur non nul
                if (creaturesTab->get(i,j).get() != 0)
                {
                    // Si ce groupe appartient à l'ia et qu'il a au moins une creature
                    if (creaturesTab->get(i,j)->getPlayer() == player_ia && creaturesTab->get(i,j)->getCreaturesNbr() > 0)
                    {
                        ligne = i;
                        colonne = j;
                        
                        // On sort de la boucle for j - on choisit ainsi arbitrairement de passer à la ligne suivante pour le choix de la cellule adverse
                        break;
                    }
                    
                    // Si ce groupe appartient au joueur adverse et qu'il a au moins une creature
                    else if (creaturesTab->get(i,j)->getPlayer() == player_real && creaturesTab->get(i,j)->getCreaturesNbr() > 0)
                    {
                        new_ligne = i;
                        new_colonne = j;
                        
                        // On sort de la boucle for j - on choisit ainsi arbitrairement de passer à la ligne suivante pour le choix de la cellule de l'ia
                        break;
                    }
                }
                
            }
            
            // On sort de la boucle for i
            if ((ligne != 0 || colonne != 0) && (new_ligne != 0 || new_colonne != 0))
                break;
        }
        
        coordsDestination[0] = ligne;
        coordsDestination[1] = colonne;
        coordsDestination[2] = new_ligne;
        coordsDestination[3] = new_colonne;
        
        return coordsDestination;
    }
    
    std::vector<int> HeuristicAI::placeCellResearch (engine::Engine& moteur)
    {
        
        std::vector<int> coordsDestination(2);
        
        // On verifie que le joueur dispose encore en stock de creatures à placer sur la grille
        if (moteur.getState().getPlayer(2)->getCreaturesLeft() > 0)
        {
            // On va chercher une case vide ou une case appartenant à l'IA
            unsigned int ligne = 0;
            unsigned int colonne = 0;
            // si choice = 0 on cherchera un groupe de l'ia, si choice = 1 on cherche une case vide
            int choice = rand()%2;

            // On recupere le joueur 2 (ia)
            state::Player* player_ia = moteur.getPlayer(2).get();

            for (unsigned int i = 0; i < moteur.getState().getCharacters()->getHeight(); i++) 
            {
                for (unsigned int j = 0; j < moteur.getState().getCharacters()->getWidth(); j++) 
                {
                    // Si on cherche un groupe de creatures et qu'il est de pointeur non nul
                    if (choice == 0 && moteur.getState().getCharacters()->get(i,j).get() != 0)
                    {
                        // Si ce groupe appartient à l'ia et qu'il a au plus 5 creatures
                        int creaNbr = moteur.getState().getCharacters()->get(i,j)->getCreaturesNbr();
                        if (moteur.getState().getCharacters()->get(i,j)->getPlayer() == player_ia && creaNbr > 0 && creaNbr < 6)
                        {
                            ligne = i;
                            colonne = j;

                            // On sort de la boucle for j
                            break;
                        }
                    }
                    // Si on cherche une case vide (ON DOIT VERIFIER QUE LA CASE EST AUTORISEE !!)
                    else if (choice == 1 && moteur.getState().getCharacters()->verifValiditeCase(i,j) && moteur.getState().getCharacters()->get(i,j).get() == NULL )
                    {
                        ligne = i;
                        colonne = j;

                        // On sort de la boucle for j
                        break;
                    }

                }

                // On sort de la boucle for i
                if (ligne != 0 || colonne != 0)
                    break;
            }

            if (ligne == 0 && colonne == 0)
                throw std::runtime_error("Aucune case n'a ete trouvée pour placer une nouvelle creature de l'IA !");

            coordsDestination[0] = ligne;
            coordsDestination[1] = colonne;
        }
        
        else
            throw std::runtime_error("L'IA ne dispose plus de creatures à placer dans la grille !");
        
        return coordsDestination;
    }
}