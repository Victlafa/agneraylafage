/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AI.h"
#include "../shared/engine/Command.h"
#include "../shared/state.h"
#include <time.h>
#include <iostream>

using namespace state;
using namespace std;

namespace ai{
    AI::AI (engine::Engine* moteur) : listCommands()
    { 
        this->moteur = moteur;
    }
    // Setters and Getters
    const std::vector<std::shared_ptr<engine::Command> >& AI::getListCommands() const { return listCommands; }
    void AI::setListCommands(const std::vector<std::shared_ptr<engine::Command> >& listCommands) { this->listCommands = listCommands; }
    engine::Engine* AI::getMoteur() const { return this->moteur; }
    
    // On initialise les parametres de base de l'IA
    void AI::initIA (int player)
    {
        Player* player_ia = this->moteur->getPlayer(player).get();
                
        // Le tirage au sort du clan de l'IA est effectué dans la classe State, qui est générée automatiquement dans le moteur
        
        player_ia->setCellNbr(3);
        //player_ia->setCreaturesLeft(3);
        
    }
    
    // On cherche une cellule destination pour l'IA afin de placer sur la carte un de ses groupes en reserve
    std::vector<int> AI::placeCellResearch (int player)
    {
        // Les deux premiers elements du tableau seront les coordonnees de la cellule choisie. Le troisieme element sera le nombre de creatures que comportera la cellule apres l'execution du placement
        std::vector<int> coordsDestination(3);
        
        // On recupere le tableau de creatures
        CreaturesTab* creaTab = moteur->getState().getCharacters().get();
        // On recupere le joueur
        state::Player* player_ia = moteur->getPlayer(player).get();
                
        // On verifie que le joueur dispose encore en stock de creatures à placer sur la grille
        if (player_ia->getCreaturesLeft() > 0)
        {
            // On va chercher une case vide ou une case appartenant à l'IA
            unsigned int ligne = 0;
            unsigned int colonne = 0;
            
            // si choice est entre 0 et 80 on cherchera un groupe de l'ia, si choice est entre 81 et 100 on cherche une case vide
            // (donc 80% de chance d'ajouter une creature à une case deja occupée par le joueur)
            
            // S'il n'y a plus de case vide disponible, on met d'office choice à 0
            int choice = (moteur->getState().getFreeCellNbr() == 0) ? 0 : rand()%100 + 1;
            // Si toutes les cases du joueur sont saturees, on le force à chercher une case vide
            if (creaTab->isSaturated(player_ia)) choice = 100;
            // S'il reste un nombre de cases libres inférieur à 5 et différent de 0, on force la recherche de case vide
            //if (moteur->getState().getFreeCellNbr() > 0 && moteur->getState().getFreeCellNbr() < 5) choice = 100;
            
            // Si on cherche un groupe de creatures appartenant au joueur qui souhaite placer une creature et qu'il est de pointeur non null
            if (choice >= 0 && choice <= 95) {
                // On recupere les coordonnees des cellules appartenant au joueur
                std::vector<int> playerCells = playerCellResearch(player);
                int random;
                
                // Parmi ces groupes, on recupere ceux qui peuvent encore accueillir une nouvelle creature
                std::vector<int> availablePlayerCells = playerAvailableCellResearch(playerCells);
                
                //std::cout << "AI::placeCellResearch - nombre de cellules du joueur disponibles pour placer une creature avant placement : " << availablePlayerCells.size()/2 << std::endl;
                
                // On tire au hasard dans cette derniere liste
                random = rand() % (int) (availablePlayerCells.size() / 2);
                
                ligne = availablePlayerCells[2 * random];
                colonne = availablePlayerCells[2 * random + 1];
                coordsDestination[2] = creaTab->get(ligne, colonne)->getCreaturesNbr() + 1;
                
                if (creaTab->isOccupiedByOpp(ligne,colonne,player_ia))
                    throw std::runtime_error("AI::placeCellResearch - La cellule choisie pour un placement appartient à l'adversaire !");
            }

            // Si on cherche une case vide
            else if (choice > 95 && choice <= 100) {
                // On recupere les coordonnees des cases vides de la carte
                std::vector<int> freeCells = creaTab->getFreeCells();
                // On en tire une au hasard
                int random = rand()%(int)(freeCells.size()/2);
                
                ligne = freeCells[2*random];
                colonne = freeCells[2*random+1];
                coordsDestination[2] = 1;
            }

            if (ligne == 0 && colonne == 0)
                throw std::runtime_error("AI::placeCellResearch - Aucune case n'a ete trouvée pour placer une nouvelle creature de l'IA !");

            coordsDestination[0] = ligne;
            coordsDestination[1] = colonne;
            
        }
        
        else
            throw std::runtime_error("AI::placeCellResearch - L'IA ne dispose plus de creatures à placer dans la grille !");
        
        if (creaTab->get(coordsDestination[0], coordsDestination[1]) != NULL && creaTab->get(coordsDestination[0], coordsDestination[1])->getCreaturesNbr() == 5)
            throw std::runtime_error("AI::placeCellResearch - La cellule destination selectionnee dispose deja de 5 creatures !");
        
        return coordsDestination;
    }
    
    // On cherche une cellule attaquante pour l'IA ainsi qu'une cellule destination adverse n'importe où sur la carte
    std::vector<int> AI::skyCellResearch (int player)
    {
        // On va chercher une creature de l'IA dans le moteur donné en argument
        unsigned int ligne = 0;
        unsigned int colonne = 0;
        // On prepare une case de destination
        unsigned int new_ligne = 0;
        unsigned int new_colonne = 0;
        // On recupere le joueur 1
        state::Player* player_real = moteur->getPlayer(3-player).get();
        // On recupere le joueur 2 (ia)
        state::Player* player_ia = moteur->getPlayer(player).get();
        // De meme avec le tableau de creatures
        state::CreaturesTab* creaturesTab = moteur->getState().getCharacters().get();
        
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
    
    // On cherche les coordonnees de toutes les cellules appartenant au joueur dont le num est donne en argument
    std::vector<int> AI::playerCellResearch (int player)
    {
        std::vector<int> coordonnees;
        CreaturesTab* creaTab = moteur->getState().getCharacters().get();
        
        // On parcourt toutes les cellules de la grille
        for (unsigned int i = 0; i < creaTab->getHeight(); i++) 
        {
            for (unsigned int j = 0; j < creaTab->getWidth(); j++) 
            {
                // Si la case est autorisee et qu'une creature est presente a la position etudiee
                if (creaTab->isEnable(i,j) && creaTab->get(i,j).get() != nullptr)
                {
                    // Si ce groupe appartient au joueur designe
                    if (creaTab->get(i,j)->getPlayer() == moteur->getPlayer(player).get())
                    {
                        //std::cout << "AI::playerCellResearch - la cellule (" << i << "," << j << ") appartient au joueur " << moteur.getPlayer(player).get() << std::endl;
                        // On ajoute les coordonnees à la liste
                        coordonnees.push_back(i);
                        coordonnees.push_back(j);
                    }
                }

            }
        }
        
        return coordonnees;
    }
    
    // On cherche les coordonnees des cellules du joueur qui peuvent encore accepter de nouveaux placements
    std::vector<int> AI::playerAvailableCellResearch(const std::vector<int>& playerCells)
    {
        std::vector<int> sortie;
        for (int i = 0; i < (int)(playerCells.size()/2); i++)
        {
            if (getMoteur()->getState().getCharacters()->get(playerCells[2 * i], playerCells[2 * i + 1])->getCreaturesNbr() < 5)
            {
                sortie.push_back(playerCells[2 * i]);
                sortie.push_back(playerCells[2 * i + 1]);
            }
        }
        
        return sortie;
    }
    
    // Test d'adjacence : on veut savoir si la cellule init est adjacente à la final
    bool AI::isAdjacent (int init_i, int init_j, int final_i, int final_j)
    {
        bool verif1 = ((final_i == init_i - 1) && final_j == init_j);
        bool verif2 = ((final_i == init_i - 1) && (final_j == init_j + 1));
        bool verif3 = (final_i == init_i && (final_j == init_j + 1));
        bool verif4 = ((final_i == init_i + 1) && final_j == init_j);
        bool verif5 = ((final_i == init_i + 1) && (final_j == init_j - 1));
        bool verif6 = (final_i == init_i && (final_j == init_j - 1));
        
        //std::cout << "AI::isAdjacent : " << (verif1 || verif2 || verif3 || verif4 || verif5 || verif6) << std::endl;
        
        if (verif1 || verif2 || verif3 || verif4 || verif5 || verif6)
            return true;
        else
            return false;
    }
    
    // On cherche une case ALEATOIRE (donc vide ou pas) adjacente à la cellule argument (caractérisée par ses coords) pour un deplacement
    std::vector<int> AI::adjacentCellResearch (int ligne, int colonne)
    {
        std::vector<int> destination(2);
        std::vector<int> adjCells = getAdjacences(ligne,colonne);
        int random = rand() % (int)(adjCells.size()/2);
        
        destination[0] = adjCells[2*random];
        destination[1] = adjCells[2*random+1];
        
        return destination;
    }
    
    // Retourne la liste des coordonnees des cellules adjacentes à la cellule dont les coordonnees sont fournies en argument
    std::vector<int> AI::getAdjacences (int i, int j)
    {
        std::vector<int> liste;
        CreaturesTab* creaTab = moteur->getState().getCharacters().get();
        
        //std::cout << "AI::getAdjacences - Cellule depart : (" << i << "," << j << ")" << std::endl;
        
        // Adjacente 1 :
        if (i > 0 && creaTab->isEnable(i-1,j))
        {
            liste.push_back(i-1);
            liste.push_back(j);
            //std::cout << "AI::getAdjacences - Adjacente 1 : (" << i-1 << "," << j << ")" << std::endl;
        }
        
        // 2 :
        if (i > 0 && j < (int)creaTab->getWidth()-1 && creaTab->isEnable(i-1,j+1))
        {
            liste.push_back(i-1);
            liste.push_back(j+1);
            //std::cout << "AI::getAdjacences - Adjacente 2 : (" << i-1 << "," << j+1 << ")" << std::endl;
        }
        
        // 3 :
        if (j < (int)creaTab->getWidth()-1 && creaTab->isEnable(i,j+1))
        {
            liste.push_back(i);
            liste.push_back(j+1);
            //std::cout << "AI::getAdjacences - Adjacente 3 : (" << i << "," << j+1 << ")" << std::endl;
        }
        
        // 4 :
        if (i < (int)creaTab->getHeight()-1 && creaTab->isEnable(i+1,j))
        {
            liste.push_back(i+1);
            liste.push_back(j);
            //std::cout << "AI::getAdjacences - Adjacente 4 : (" << i+1 << "," << j << ")" << std::endl;
        }
        
        // 5 :
        if (i < (int)creaTab->getHeight()-1 && j > 0 && creaTab->isEnable(i+1,j-1))
        {
            liste.push_back(i+1);
            liste.push_back(j-1);
            //std::cout << "AI::getAdjacences - Adjacente 5 : (" << i+1 << "," << j-1 << ")" << std::endl;
        }
        
        // 6 :
        if (j > 0 && creaTab->isEnable(i,j-1))
        {
            liste.push_back(i);
            liste.push_back(j-1);
            //std::cout << "AI::getAdjacences - Adjacente 6 : (" << i << "," << j-1 << ")" << std::endl;
        }
        
        
        return liste;
    }

}
