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
using namespace state;

namespace ai{
    
    RandomAI::RandomAI (engine::Engine* moteur, int randomSeed) : AI(moteur)
    {
        randGen.seed(randomSeed);
        
    }
    
    void RandomAI::run (int player) 
    {
        if (getMoteur()->getTour() == 1)
            // On initialise les attributs de l'IA
            this->initIA(player);
        
        // On cherche dans la grille une cellule appartenant à l'IA ainsi qu'une cellule de destination adjacente pour un deplacement
        std::vector<int> coords; // = moveCellResearch(moteur);
        // On cherche une cellule dispo pour placer une nouvelle creature de l'IA (venant de son stock) dans la grille
        std::vector<int> placeCoords; // = placeCellResearch(moteur);

        // On ajoute 5 commandes de placement et 5 de deplacement à l'IA
        for (int i = 0; i < 5; i++)
        {
            coords = moveCellResearch(player);
//            placeCoords = placeCellResearch(moteur,player);
            // On ajoute une commande de deplacement
            listCommands.push_back(std::shared_ptr<engine::Command>(new engine::MoveCommand(coords[0], coords[1], coords[2], coords[3], player)));
            // On ajoute une commande de placement de nouvelle creature seulement si les coordonnees de placement sont differentes de celles du deplacement
//            if (placeCoords[0] != coords[0] && placeCoords[1] != coords[1]){
//                listCommands.push_back(std::shared_ptr<engine::Command>(new engine::PlaceCommand(placeCoords[0], placeCoords[1], player, (state::ID)moteur.getPlayer(player)->getClanName())));
//                //std::cout <<  << std::endl;
//            }
        }
        
        // On souhaite en executer 5 de façon aleatoire
        int randCommand;
        
        for (int j = 0; j < 5; j ++)
        {
            randCommand = randGen()%(listCommands.size());
            listCommands.at(randCommand)->execute(getMoteur()->getPileAction(),getMoteur()->getState());
            cout << "RandomAI::run - Une commande de l'ia random a été en principe executée !" << endl;
        }
        
        // On vide la liste des commandes
        listCommands.clear();
    }
        
    // On cherche une cellule attaquante pour l'IA ainsi qu'une cellule destination adverse ADJACENTE
    std::vector<int> RandomAI::moveCellResearch (int player)
    {
        // On va chercher une creature de l'IA dans le moteur donné en argument
        unsigned int ligne = 0;
        unsigned int colonne = 0;
        // On prepare une case de destination
        unsigned int new_ligne = 0;
        unsigned int new_colonne = 0;
        // On recupere le joueur 2 (ia)
        state::Player* player_ia = getMoteur()->getPlayer(player).get();
        std::vector<int> coordsDestination(4);
        CreaturesTab* creaTab = getMoteur()->getState().getCharacters().get();
        
        for (unsigned int i = 0; i < creaTab->getHeight(); i++) 
        {
            for (unsigned int j = 0; j < creaTab->getWidth(); j++) 
            {
                // Si on trouve un groupe de creatures de pointeur non nul
                if (creaTab->get(i,j).get() != 0)
                {
                    // Si ce groupe appartient à l'ia et qu'il a au moins une creature
                    if (creaTab->get(i,j)->getPlayer() == player_ia && creaTab->get(i,j)->getCreaturesNbr() > 0)
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
        if (ligne > 0 && creaTab->get(ligne-1,colonne).get() == NULL && creaTab->isEnable(ligne - 1,colonne))
            new_ligne -= 1;
        // Vers l'adjacente n°2 ?
        else if (ligne > 0 && colonne < creaTab->getWidth() && creaTab->get(ligne-1,colonne + 1).get() == NULL && creaTab->isEnable(ligne - 1,colonne))
        {
            new_ligne -= 1; new_colonne += 1;
        }
        // Vers l'adjacente n°3 ?
        else if (colonne < creaTab->getWidth() && creaTab->get(ligne,colonne + 1).get() == NULL && creaTab->isEnable(ligne,colonne+1))
            new_colonne += 1;
        // Vers l'adjacente n°4 ?
        else if (ligne < creaTab->getHeight() && creaTab->get(ligne + 1,colonne).get() == NULL && creaTab->isEnable(ligne + 1,colonne))
            new_ligne += 1;
        // Vers l'adjacente n°5 ?
        else if (colonne > 0 && ligne < creaTab->getHeight() && creaTab->get(ligne + 1,colonne).get() == NULL && creaTab->isEnable(ligne + 1,colonne))
        {
            new_ligne += 1; new_colonne -= 1;
        }
        // Vers l'adjacente n°6 ?
        else if (colonne > 0 && creaTab->get(ligne,colonne-1).get() == NULL && creaTab->isEnable(ligne,colonne-1))
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
    
        // Dans les cellules adjacentes à la cellule argument, on en renvoie une au hasard
    std::vector<int> RandomAI::adjacentEnnemyResearch (int player, int init_i, int init_j)
    {        
        // On declare un tableau dans lequel on mettra les coordonnees des cellules adjacentes
        std::vector<int> adjacent_Cells;
        std::vector<int> finalCell;
        std::vector<int> possibleAdjs = this->getAdjacences(init_i,init_j);
        //bool verifBornes = false;
        bool occupation = false;
        //int tabWidth = getMoteur()->getState().getCharacters()->getWidth();
        //int tabHeight = getMoteur()->getState().getCharacters()->getHeight();
        int random;
        
        for (int i = 0; i < (int)(possibleAdjs.size()/2); i++)
        {
            // On verifie les bornes (pour ne pas se retrouver à chercher une case hors de la grille !)
//            if (i >= 0 && i < 3)
//                verifBornes = (possibleAdjs[2 * i] >= 0 && possibleAdjs[2 * i + 1] < tabWidth);
//            else if (i >= 3 && i < 6)
//                verifBornes = (possibleAdjs[2 * i] < tabHeight && possibleAdjs[2 * i + 1] >= 0);

            // On verifie de plus si l'adjacence amene à une case valide
//            if (verifBornes && getMoteur()->getState().getCharacters()->isEnable(possibleAdjs[2*i],possibleAdjs[2*i+1]))
//            {
//                
//                
//            }
            // On verifie si la cellule adjacente possible est occupee ou non par l'adversaire
            occupation = getMoteur()->getState().getCharacters()->isOccupiedByOpp(possibleAdjs[2 * i], possibleAdjs[2 * i + 1], getMoteur()->getPlayer(player).get());

            if (occupation) {
                // Si les deux conditions sont verifiees, la cellule adjacente etudiee appartient au joueur reel 
                adjacent_Cells.push_back(possibleAdjs[2 * i]);
                adjacent_Cells.push_back(possibleAdjs[2 * i + 1]);
            }
            
        }
        
        // Si on trouve aucune cellule adjacente adverse
        if (adjacent_Cells.size() == 0)
            // On leve une exception car on part du principe que la cellule argument a au moins une cellule adverse adjacente
            throw std::runtime_error("RandomAI::adjacentEnnemyResearch - La cellule donnee en argument n'a pas de voisine appartenant à l'adversaire !");
        
        // On tire une cellule au hasard parmi la liste
        random = rand()%(int)(adjacent_Cells.size()/2);
        finalCell[0] = adjacent_Cells[2*random];
        finalCell[1] = adjacent_Cells[2*random + 1];
        
        return finalCell;
        
    }

}
