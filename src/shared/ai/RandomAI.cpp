/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "RandomAI.h"
//#include "engine/Engine.h"
#include "../shared/engine.h"
#include "../shared/state.h"
#include <iostream>
#include <time.h>

using namespace std;

namespace ai{
    
    RandomAI::RandomAI (int randomSeed) : AI()
    {
        randGen.seed(randomSeed);
    }
    
    void RandomAI::run (engine::Engine& moteur) 
    {
        // On initialise les attributs de l'IA
        this->initIA(moteur);
        
        // On s'arrange pour que l'IA ait au moins une creature a placer en stock
        moteur.getPlayer(2)->setCreaturesLeft(6);
        
        // On cherche dans la grille une cellule appartenant à l'IA ainsi qu'une cellule de destination adjacente pour un deplacement
        std::vector<int> coords; // = moveCellResearch(moteur);
        // On cherche une cellule dispo pour placer une nouvelle creature de l'IA (venant de son stock) dans la grille
        std::vector<int> placeCoords; // = placeCellResearch(moteur);

        // On ajoute 5 commandes de placement et 5 de deplacement à l'IA
        for (int i = 0; i < 5; i++)
        {
            coords = moveCellResearch(moteur);
            placeCoords = placeCellResearch(moteur);
            // On ajoute une commande de deplacement
            listCommands.push_back(std::shared_ptr<engine::Command>(new engine::MoveCommand(coords[0], coords[1], coords[2], coords[3], 2)));
            // On ajoute une commande de placement de nouvelle creature seulement si les coordonnees de placement sont differentes de celles du deplacement
            if (placeCoords[0] != coords[0] && placeCoords[1] != coords[1])
                listCommands.push_back(std::shared_ptr<engine::Command>(new engine::PlaceCommand(placeCoords[0], placeCoords[1], 2, (state::ID)moteur.getPlayer(2)->getClanName())));
        
        }
        
        // On souhaite en executer 5 de façon aleatoire
        int randCommand;
        
        for (int j = 0; j < 5; j ++)
        {
            randCommand = randGen()%(listCommands.size());
            listCommands.at(randCommand)->execute(moteur.getState());
            cout << "RandomAI::run - Une commande de l'ia random a été en principe executée !" << endl;
        }
        
        // On vide la liste des commandes
        listCommands.clear();
    }
    
    // Permet de chercher dans la grille une cellule appartenant à l'IA ainsi qu'une cellule de destination adjacente pour un deplacement
    std::vector<int> RandomAI::moveCellResearch (engine::Engine& moteur)
    {
        // On va chercher une creature de l'IA dans le moteur donné en argument
        unsigned int ligne = 0;
        unsigned int colonne = 0;
        // On prepare une case de destination
        unsigned int new_ligne = 0;
        unsigned int new_colonne = 0;
        // On recupere le joueur 2 (ia)
        state::Player* player_ia = moteur.getPlayer(2).get();
        std::vector<int> coordsDestination(4);
        
        for (unsigned int i = 0; i < moteur.getState().getCharacters()->getHeight(); i++) 
        {
            for (unsigned int j = 0; j < moteur.getState().getCharacters()->getWidth(); j++) 
            {
                // Si on trouve un groupe de creatures de pointeur non nul
                if (moteur.getState().getCharacters()->get(i,j).get() != 0)
                {
                    // Si ce groupe appartient à l'ia et qu'il a au moins une creature
                    if (moteur.getState().getCharacters()->get(i,j)->getPlayer() == player_ia && moteur.getState().getCharacters()->get(i,j)->getCreaturesNbr() > 0)
                    {
                        ligne = i;
                        colonne = j;
                        new_ligne = i;
                        new_colonne = j;
                        
                        // On sort de la boucle for j
                        break;
                    }
                }
                
            }
            
            // On sort de la boucle for i
            if (ligne != 0 || colonne != 0 || new_ligne != 0 || new_colonne != 0)
                break;
        }
        
        // On cherche une case adjacente pour un potentiel deplacement
        
        // Deplacement possible vers l'adjacente n°1 ?
        if (ligne > 0 && moteur.getState().getCharacters()->get(ligne-1,colonne).get() == NULL && moteur.getState().getCharacters()->verifValiditeCase(ligne - 1,colonne))
            new_ligne -= 1;
        // Vers l'adjacente n°2 ?
        else if (ligne > 0 && colonne < moteur.getState().getCharacters()->getWidth() && moteur.getState().getCharacters()->get(ligne-1,colonne + 1).get() == NULL && moteur.getState().getCharacters()->verifValiditeCase(ligne - 1,colonne))
        {
            new_ligne -= 1; new_colonne += 1;
        }
        // Vers l'adjacente n°3 ?
        else if (colonne < moteur.getState().getCharacters()->getWidth() && moteur.getState().getCharacters()->get(ligne,colonne + 1).get() == NULL && moteur.getState().getCharacters()->verifValiditeCase(ligne,colonne+1))
            new_colonne += 1;
        // Vers l'adjacente n°4 ?
        else if (ligne < moteur.getState().getCharacters()->getHeight() && moteur.getState().getCharacters()->get(ligne + 1,colonne).get() == NULL && moteur.getState().getCharacters()->verifValiditeCase(ligne + 1,colonne))
            new_ligne += 1;
        // Vers l'adjacente n°5 ?
        else if (colonne > 0 && ligne < moteur.getState().getCharacters()->getHeight() && moteur.getState().getCharacters()->get(ligne + 1,colonne).get() == NULL && moteur.getState().getCharacters()->verifValiditeCase(ligne + 1,colonne))
        {
            new_ligne += 1; new_colonne -= 1;
        }
        // Vers l'adjacente n°6 ?
        else if (colonne > 0 && moteur.getState().getCharacters()->get(ligne,colonne-1).get() == NULL && moteur.getState().getCharacters()->verifValiditeCase(ligne,colonne-1))
            new_colonne -= 1;
        else
            std::cout << "RandomAI::moveCellResearch - La case selectionnee pour l'IA ne permet aucun deplacement" << std::endl;
            //throw std::runtime_error("Aucune possibilite de deplacement pour l'ia !");
        
        coordsDestination[0] = ligne;
        coordsDestination[1] = colonne;
        coordsDestination[2] = new_ligne;
        coordsDestination[3] = new_colonne;
        
        return coordsDestination;
    }
    
    // Permet de chercher dans la grille une cellule appartenant à l'IA ou une cellule vide pour pouvoir y placer une nouvelle creature
    std::vector<int> RandomAI::placeCellResearch (engine::Engine& moteur)
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
                throw runtime_error("Aucune case n'a ete trouvée pour placer une nouvelle creature de l'IA !");

            coordsDestination[0] = ligne;
            coordsDestination[1] = colonne;
        }
        
        else
            throw runtime_error("L'IA ne dispose plus de creatures à placer dans la grille !");
        
        return coordsDestination;
    }
        
        
}
