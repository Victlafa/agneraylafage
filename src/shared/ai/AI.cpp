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
    { this->moteur = moteur; }
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
    std::vector<int> AI::placeCellResearch (int player, std::vector<int>& disabledPlaces)
    {
        // Les deux premiers elements du tableau seront les coordonnees de la cellule choisie. Le troisieme element sera le nombre de creatures que comportera la cellule apres l'execution du placement
        std::vector<int> coordsDestination(3);
                
        // On verifie que le joueur dispose encore en stock de creatures à placer sur la grille
        if (moteur->getState().getPlayer(player)->getCreaturesLeft() > 0)
        {
            // On va chercher une case vide ou une case appartenant à l'IA
            unsigned int ligne = 0;
            unsigned int colonne = 0;
            
            // si choice = 0 on cherchera un groupe de l'ia, si choice = 1 on cherche une case vide
            // S'il n'y a plus de case vide disponible, on met d'office choice à 0
            int choice = (moteur->getState().getFreeCellNbr() == 0) ? 0 : rand()%2;
            // S'il reste un nombre de cases libres inférieur à 5 et différent de 0, on favorise le choix de ces cases
            if (moteur->getState().getFreeCellNbr() > 0 && moteur->getState().getFreeCellNbr() < 5) choice = 1;
            
            // On recupere le joueur
            state::Player* player_ia = moteur->getPlayer(player).get();

            for (unsigned int i = 0; i < moteur->getState().getCharacters()->getHeight(); i++) 
            {
                for (unsigned int j = 0; j < moteur->getState().getCharacters()->getWidth(); j++) 
                {
                    // On verifie si les coordonnees etudiees ne sont pas deja prevues pour un autre placement durant ce tour
                    if (isAvailable(i,j,disabledPlaces))
                    {
                        //cout << "i : " << i << "|| j : " << j << endl;  // Oooooookkkkk
                        
                        // Si on cherche un groupe de creatures appartenant au joueur qui souhaite placer une creature et qu'il est de pointeur non nul
                        if (choice == 0 && moteur->getState().getCharacters()->get(i, j).get() != 0 && moteur->getState().getCharacters()->get(i, j)->getPlayer() == player_ia) {
                            //cout << "Cellule du joueur disponible " << "i : " << i << "|| j : " << j << endl; // Oooooooookkkk
                            // Si ce groupe appartient à l'ia et qu'il a au plus 4 creatures
                            int creaNbr = moteur->getState().getCharacters()->get(i, j)->getCreaturesNbr();
                            
                            if (creaNbr > 0 && creaNbr < 5) {
                                // Il est valide et on le selectionne
                                ligne = i;
                                colonne = j;
                                coordsDestination[2] = moteur->getState().getCharacters()->get(ligne,colonne)->getCreaturesNbr() + 1;
                                //cout << "Nombre de creatures prevu apres placement : " << coordsDestination[2] << endl;

                                // On sort de la boucle for j
                                break;
                            }
                        }                            
                        
                        // Si on cherche une case vide (ON DOIT VERIFIER QUE LA CASE EST AUTORISEE !!)
                        else if (choice == 1 && moteur->getState().getCharacters()->isEnable(i, j) && moteur->getState().getCharacters()->get(i, j).get() == NULL) {
                            //cout << "Cellule vide disponible " << "i : " << i << "|| j : " << j << endl; // Oooooooookkkk
                            ligne = i;
                            colonne = j;
                            coordsDestination[2] = 1;

                            // On sort de la boucle for j
                            break;
                        }
                    }
                    

                }

                // On sort de la boucle for i
                if (ligne != 0 || colonne != 0)
                    break;
            }

            if (ligne == 0 && colonne == 0)
                throw std::runtime_error("AI::placeCellResearch - Aucune case n'a ete trouvée pour placer une nouvelle creature de l'IA !");

            coordsDestination[0] = ligne;
            coordsDestination[1] = colonne;
            
        }
        
        else
            throw std::runtime_error("AI::placeCellResearch - L'IA ne dispose plus de creatures à placer dans la grille !");
        
        if (moteur->getState().getCharacters()->get(coordsDestination[0], coordsDestination[1]) != NULL && moteur->getState().getCharacters()->get(coordsDestination[0], coordsDestination[1])->getCreaturesNbr() == 5)
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
        CreaturesTab* groupes = moteur->getState().getCharacters().get();
        
        // On parcourt toutes les cellules de la grille
        for (unsigned int i = 0; i < groupes->getHeight(); i++) 
        {
            for (unsigned int j = 0; j < groupes->getWidth(); j++) 
            {
                // Si la case est autorisee et qu'une creature est presente a la position etudiee
                if (groupes->isEnable(i,j) && groupes->get(i,j).get() != nullptr)
                {
                    // Si ce groupe appartient au joueur designe
                    if (groupes->get(i,j)->getPlayer() == moteur->getPlayer(player).get())
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
    
    // On cherche une case QUELCONQUE (donc vide ou pas) adjacente à la cellule argument (caractérisée par ses coords) pour un deplacement
    std::vector<int> AI::adjacentCellResearch (int ligne, int colonne)
    {
        //int new_ligne = ligne;
        //int new_colonne = colonne;
        std::vector<int> destination(2);
        std::vector<int> adjCells = getAdjacences(ligne,colonne);
        int random = rand() % (int)(adjCells.size()/2);
        //CreaturesTab* creaTab = moteur->getState().getCharacters().get();
        
//        // Deplacement possible vers l'adjacente n°1 ?
//        if (ligne > 0 /*&& creaTab->get(ligne-1,colonne).get() == NULL*/ && creaTab->isEnable(ligne - 1,colonne))
//            new_ligne -= 1;
//        // Vers l'adjacente n°2 ?
//        else if (ligne > 0 && colonne < (int)(creaTab->getWidth()) && /*creaTab->get(ligne-1,colonne + 1).get() == NULL &&*/ creaTab->isEnable(ligne - 1,colonne))
//        {
//            new_ligne -= 1; new_colonne += 1;
//        }
//        // Vers l'adjacente n°3 ?
//        else if (colonne < (int)(creaTab->getWidth()) /*&& creaTab->get(ligne,colonne + 1).get() == NULL*/ && creaTab->isEnable(ligne,colonne+1))
//            new_colonne += 1;
//        // Vers l'adjacente n°4 ?
//        else if (ligne < (int)(creaTab->getHeight()) /*&& creaTab->get(ligne + 1,colonne).get() == NULL*/ && creaTab->isEnable(ligne + 1,colonne))
//            new_ligne += 1;
//        // Vers l'adjacente n°5 ?
//        else if (colonne > 0 && ligne < (int)(creaTab->getHeight()) /*&& creaTab->get(ligne + 1,colonne).get() == NULL*/ && creaTab->isEnable(ligne + 1,colonne))
//        {
//            new_ligne += 1; new_colonne -= 1;
//        }
//        // Vers l'adjacente n°6 ?
//        else if (colonne > 0 && /*creaTab->get(ligne,colonne-1).get() == NULL &&*/ creaTab->isEnable(ligne,colonne-1))
//            new_colonne -= 1;
        //else
            //throw std::runtime_error("AI::moveCellResearch - La case selectionnee pour l'IA ne permet aucun deplacement");
        
        destination[0] = adjCells[2*random];
        destination[1] = adjCells[2*random+1];
        
        return destination;
    }
    
    // Retourne la liste des coordonnees des cellules adjacentes à la cellule dont les coordonnees sont fournies en argument
    std::vector<int> AI::getAdjacences (int i, int j)
    {
        std::vector<int> liste;
        CreaturesTab* creaTab = moteur->getState().getCharacters().get();
        
        std::cout << "AI::getAdjacences - Cellule depart : (" << i << "," << j << ")" << std::endl;
        
        // Adjacente 1 :
        if (i > 0 && creaTab->isEnable(i-1,j))
        {
            liste.push_back(i-1);
            liste.push_back(j);
            std::cout << "AI::getAdjacences - Adjacente 1 : (" << i-1 << "," << j << ")" << std::endl;
        }
        
        // 2 :
        if (i > 0 && j < (int)creaTab->getWidth()-1 && creaTab->isEnable(i-1,j+1))
        {
            liste.push_back(i-1);
            liste.push_back(j+1);
            std::cout << "AI::getAdjacences - Adjacente 2 : (" << i-1 << "," << j+1 << ")" << std::endl;
        }
        
        // 3 :
        if (j < (int)creaTab->getWidth()-1 && creaTab->isEnable(i,j+1))
        {
            liste.push_back(i);
            liste.push_back(j+1);
            std::cout << "AI::getAdjacences - Adjacente 3 : (" << i << "," << j+1 << ")" << std::endl;
        }
        
        // 4 :
        if (i < (int)creaTab->getHeight()-1 && creaTab->isEnable(i+1,j))
        {
            liste.push_back(i+1);
            liste.push_back(j);
            std::cout << "AI::getAdjacences - Adjacente 4 : (" << i+1 << "," << j << ")" << std::endl;
        }
        
        // 5 :
        if (i < (int)creaTab->getHeight()-1 && j > 0 && creaTab->isEnable(i+1,j-1))
        {
            liste.push_back(i+1);
            liste.push_back(j-1);
            std::cout << "AI::getAdjacences - Adjacente 5 : (" << i+1 << "," << j-1 << ")" << std::endl;
        }
        
        // 6 :
        if (j > 0 && creaTab->isEnable(i,j-1))
        {
            liste.push_back(i);
            liste.push_back(j-1);
            std::cout << "AI::getAdjacences - Adjacente 6 : (" << i << "," << j-1 << ")" << std::endl;
        }
        
        
        return liste;
    }
    
    // Renvoie true si les coordonnees i et j ne sont pas presentes dans la liste disabledPlaces
    bool AI::isAvailable (int i, int j, std::vector<int>& disabledPlaces)
    {
        if (disabledPlaces.size() == 0)
            return true;
        else
        {
            //cout << "Elements de disabledPlaces : ";
            for (int k = 0; k < (int) disabledPlaces.size() / 2; k++) {
                //cout << disabledPlaces[2*k] << "," << disabledPlaces[2*k+1] << " ";
                if (disabledPlaces[2 * k] == i && disabledPlaces[2 * k + 1] == j)
                    return false;
            }
            //cout << endl;
            return true;
        }
        
    }

}
