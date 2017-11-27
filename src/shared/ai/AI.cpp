/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AI.h"
#include "../shared/engine/Command.h"
#include "../shared/state.h"
#include <time.h>

using namespace state;

namespace ai{
    AI::AI () : listCommands() {}
    // Setters and Getters
    const std::vector<std::shared_ptr<engine::Command> >& AI::getListCommands() const { return listCommands; }
    void AI::setListCommands(const std::vector<std::shared_ptr<engine::Command> >& listCommands) { this->listCommands = listCommands; }
    
    // On initialise les parametres de base de l'IA
    void AI::initIA (engine::Engine& moteur)
    {
        CreaturesID typeJoueur1 = moteur.getPlayer(1)->getClanName();
        Player* player_ia = moteur.getPlayer(2).get();
        CreaturesID tirage = typeJoueur1;
        
        // On tire au sort un type de creature qu'on associe à l'IA (on s'arrange pour qu'il soit different de celui du joueur) :
        while (tirage == typeJoueur1)
            tirage = (CreaturesID)(rand()%4 + 1);
        
        player_ia->setClanName(tirage);
        player_ia->setCellNbr(3);
        player_ia->setCreaturesLeft(3);
        
    }
    
    // On cherche une cellule destination pour l'IA afin de placer sur la carte un de ses groupes en reserve
    std::vector<int> AI::placeCellResearch (engine::Engine& moteur)
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
    
    // On cherche une cellule attaquante pour l'IA ainsi qu'une cellule destination adverse n'importe où sur la carte
    std::vector<int> AI::skyCellResearch (engine::Engine& moteur)
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
    
    // On cherche les coordonnees de toutes les cellules appartenant au joueur dont le num est donne en argument
    std::vector<int> AI::playerCellResearch (engine::Engine& moteur, int player)
    {
        std::vector<int> coordonnees;
        
        // On parcourt toutes les cellules de la grille
        for (unsigned int i = 0; i < moteur.getState().getCharacters()->getHeight(); i++) 
        {
            for (unsigned int j = 0; j < moteur.getState().getCharacters()->getWidth(); j++) 
            {
                // Si une creature est presente a la position etudiee
                if (moteur.getState().getCharacters()->get(i,j).get() != 0)
                {
                    // Si ce groupe appartient au joueur designe
                    if (moteur.getState().getCharacters()->get(i,j)->getPlayer() == moteur.getPlayer(player).get())
                    {
                        // On ajoute les coordonnees à la liste
                        coordonnees.push_back(i);
                        coordonnees.push_back(j);
                    }
                }

            }
        }
        
        return coordonnees;
    }
    
    // Test d'adjacence de deux cellules ennemies
    bool AI::isAdjacent (int init_i, int init_j, int final_i, int final_j)
    {
        bool verif1 = ((final_i == init_i - 1) && final_j == init_j);
        bool verif2 = ((final_i == init_i - 1) && (final_j == init_j + 1));
        bool verif3 = (final_i == init_i && (final_j == init_j + 1));
        bool verif4 = ((final_i == init_i + 1) && final_j == init_j);
        bool verif5 = ((final_i == init_i + 1) && (final_j == init_j - 1));
        bool verif6 = (final_i == init_i && (final_j == init_j - 1));
        
        if (verif1 || verif2 || verif3 || verif4 || verif5 || verif6)
            return true;
        else
            return false;
    }
    
    // Dans les cellules adjacentes à la cellule argument, on en renvoie une au hasard appartenant à l'adversaire
    std::vector<int> AI::inAdjacentResearch (engine::Engine& moteur, int init_i, int init_j)
    {
        // On declare un tableau dans lequel on mettra les coordonnees des cellules adjacentes
        std::vector<int> adjacent_Cells;
        std::vector<int> finalCell;
        int random;
                
        // L'adjacente n°1 appartient-elle à l'adversaire ?
        if (moteur.getState().getCharacters()->verifValiditeCase(init_i - 1,init_j) && init_i > 0 && moteur.getState().getCharacters()->isOccupiedByOpp(init_i - 1, init_j, moteur.getPlayer(1).get()))
        {
            adjacent_Cells.push_back(init_i - 1);
            adjacent_Cells.push_back(init_j);
        }
        // l'adjacente n°2 ?
        if (moteur.getState().getCharacters()->verifValiditeCase(init_i - 1,init_j + 1) && init_i > 0 && init_j < moteur.getState().getCharacters()->getWidth() &&  moteur.getState().getCharacters()->isOccupiedByOpp(init_i - 1, init_j + 1, moteur.getPlayer(1).get()))
        {
            adjacent_Cells.push_back(init_i - 1);
            adjacent_Cells.push_back(init_j + 1);
        }
        // l'adjacente n°3 ?
        if (moteur.getState().getCharacters()->verifValiditeCase(init_i,init_j+1) && init_j < moteur.getState().getCharacters()->getWidth() && moteur.getState().getCharacters()->isOccupiedByOpp(init_i, init_j + 1, moteur.getPlayer(1).get()))
        {
            adjacent_Cells.push_back(init_i);
            adjacent_Cells.push_back(init_j + 1);
        }
        // l'adjacente n°4 ?
        if (moteur.getState().getCharacters()->verifValiditeCase(init_i + 1,init_j) && init_i < moteur.getState().getCharacters()->getHeight() && moteur.getState().getCharacters()->isOccupiedByOpp(init_i + 1, init_j, moteur.getPlayer(1).get()))
        {
            adjacent_Cells.push_back(init_i + 1);
            adjacent_Cells.push_back(init_j);
        }
        // l'adjacente n°5 ?
        if (moteur.getState().getCharacters()->verifValiditeCase(init_i + 1,init_j - 1) && init_j > 0 && init_i < moteur.getState().getCharacters()->getHeight() && moteur.getState().getCharacters()->isOccupiedByOpp(init_i + 1, init_j - 1, moteur.getPlayer(1).get()))
        {
            adjacent_Cells.push_back(init_i + 1);
            adjacent_Cells.push_back(init_j - 1);
        }
        // l'adjacente n°6 ?
        if (moteur.getState().getCharacters()->verifValiditeCase(init_i,init_j-1) && init_j > 0 && moteur.getState().getCharacters()->isOccupiedByOpp(init_i, init_j - 1, moteur.getPlayer(1).get()))
        {
            adjacent_Cells.push_back(init_i);
            adjacent_Cells.push_back(init_j - 1);
        }
        
        // Si on trouve aucune cellule adjacente adverse
        if (adjacent_Cells.size() == 0)
            // On leve une exception car on part du principe que la cellule argument a au moins une cellule adverse adjacente
            throw std::runtime_error("AI::inAdjacentResearch - La cellule donnee en argument n'a pas de voisine appartenant à l'adversaire !");
        
        // On tire une cellule adjacente au hasard 
        random = rand()%((int)(adjacent_Cells.size()/2));
        finalCell[0] = adjacent_Cells[2*random];
        finalCell[1] = adjacent_Cells[2*random + 1];
        
        return finalCell;
        
    }
}
