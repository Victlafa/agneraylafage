/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "HeuristicAI.h"
#include <iostream>
#include "../shared/engine.h"
#include "../shared/state/CreaturesTab.h"

using namespace state;
using namespace std;

namespace ai
{
    HeuristicAI::HeuristicAI (engine::Engine* moteur, int randomSeed) : AI(moteur)
    {
        randGen.seed(randomSeed);
        // On initialise les attributs de l'IA
        //this->initIA(moteur,player);
    }
    
    void HeuristicAI::run (int player)
    {
        if (getMoteur()->getTour() == 1)
            // On initialise les attributs de l'IA
            this->initIA(player);
        
        // 1. PHASE DE CONQUETE
        cout << "-------------------------------- PHASE DE CONQUETE --------------------------------" << endl << endl;
        // On tire pour cela au sort une cellule de l'ia et une cellule du joueur 1 à attaquer
        std::vector<int> coordsDeplacement = moveCellResearch(player);
        CreaturesTab* creaTab = getMoteur()->getState().getCharacters().get();
        
        std::cout << "HeuristicAI::run - Depart de l'IA n°" << player << " : (" << coordsDeplacement[0] << "," << coordsDeplacement[1] << ")" << std::endl;
        std::cout << "HeuristicAI::run - Destination de l'IA n°" << player << " : (" << coordsDeplacement[2] << "," << coordsDeplacement[3] << ")" << std::endl;
        
        if (creaTab->get(coordsDeplacement[2],coordsDeplacement[3]) == NULL)
            std::cout << "HeuristicAI::run - La case destination est vide" << std::endl;
        
        // On ajoute la commande associee à ce deplacement
        listCommands.push_back(std::shared_ptr<engine::Command> ( new engine::MoveCommand(coordsDeplacement[0], coordsDeplacement[1], coordsDeplacement[2], coordsDeplacement[3], player)));
        
        for (int i = 0; i < (int)(listCommands.size()); i++)
            listCommands[i]->execute(getMoteur()->getState());
        
        // On verifie que le deplacement de la phase de conquete a bien ete effectue
        if (creaTab->get(coordsDeplacement[2],coordsDeplacement[3]) == NULL)
            throw std::runtime_error("HeuristicAI::run - La case de destination est tjrs vide meme apres deplacement !");
                                     
        listCommands.clear();
        
        // 2. PHASE DE RENFORT
        cout << endl;
        cout << "-------------------------------- PHASE DE RENFORT --------------------------------" << endl << endl;
        
        // L'IA reçoit autant de creatures à placer qu'elle dispose de territoires. On plafonne à 8 !
        int nbrCell = (getMoteur()->getPlayer(player)->getCellNbr() > 8) ? 8 : getMoteur()->getPlayer(player)->getCellNbr();
        
        getMoteur()->getPlayer(player)->setCreaturesLeft(nbrCell);
        cout << "L'IA n°" << player << " dispose maintenant de " << nbrCell << " cellules, elle peut donc placer autant de nouvelles creatures sur la carte. (plafonné à 8)" << endl;
        
        // On declare un tableau qui contiendra les coords des cellules selectionnees pour le placement de nouvelles creatures
        std::vector<int> newCreasCoordsTotales(0);
        std::vector<int> newCreasCoordsUnitaires(3);
        engine::PlaceCommand* placement;
        
        // On recupere une liste des coordonnees des cellules qu'occuperont ces creatures et on ajoute les commandes au fur et à mesure à la liste
        for (int i = 0; i < nbrCell; i++)
        {
            newCreasCoordsUnitaires = this->placeCellResearch(player,newCreasCoordsTotales);
            // Si la cellule contiendra en principe 5 creatures apres placement
            if (newCreasCoordsUnitaires[2] == 5)
            {
                // On fait en sorte qu'elle ne puisse plus etre choisie
                newCreasCoordsTotales.push_back(newCreasCoordsUnitaires[0]);
                newCreasCoordsTotales.push_back(newCreasCoordsUnitaires[1]);
            }
            
            placement = new engine::PlaceCommand(newCreasCoordsUnitaires[0], newCreasCoordsUnitaires[1], player, (state::ID)getMoteur()->getPlayer(player)->getClanName());
            placement->execute(getMoteur()->getState());
            cout << "Nombre de cellules vides restantes apres placement : " << getMoteur()->getState().getFreeCellNbr() << endl;
            cout << "Nombre de cellules du joueur : " << getMoteur()->getPlayer(player)->getCellNbr() << endl;
        }
    }
    
    // On cherche une cellule attaquante pour l'IA ainsi qu'une cellule destination adverse ADJACENTE
    std::vector<int> HeuristicAI::moveCellResearch (int player)
    {
        // On recupere la liste des coordonnees des cellules possedees par le joueur reel
        std::vector<int> real_cells = this->playerCellResearch(3-player);  
        // On recupere la liste des coordonnees des cellules possedees par l'IA
        std::vector<int> ia_cells = this->playerCellResearch(player); 
        
        // On declare un tableau où on mettra temporairement les coordonnees des cellules de l'IA qui ont des cellules du joueur 1 pour voisines
        std::vector<int> adjacent_cells;
        // On declare le tableau qui comportera les coordonnees de destination
        std::vector<int> finalDestination;
        // On declare le tableau qui comportera les coordonnees à renvoyer
        std::vector<int> coordsMove(4);
        
        // On fait le tour de la liste de l'ia
        for (int i = 0; i < (int)(ia_cells.size()/2); i++)
        { 
            // Pour chaque cellule de l'ia on explore toutes les cellules du joueur 1, on sort de cette seconde boucle for si on en trouve une
            for (int j = 0; j < (int)(real_cells.size()/2); j++){
            
                // Si la cellule du joueur est valide et qu'elle est adjacente à celle de l'IA
                if (getMoteur()->getState().getCharacters()->isEnable(real_cells[2*j],real_cells[2*j+1]) && isAdjacent(ia_cells[2*i],ia_cells[2*i+1],real_cells[2*j],real_cells[2*j+1]))
                {
                    //std::cout << "Cellule de l'ia : (" << ia_cells[2*i] << "," << ia_cells[2*i+1] << ")" << std::endl;
                    //std::cout << "Cellule adjacente trouvee correspondante : (" << real_cells[2*j] << "," << real_cells[2*j+1] << ")" << std::endl;
                    // On ajoute les coordonnees de l'ia à adjacent_cells
                    adjacent_cells.push_back(ia_cells[2*i]);
                    adjacent_cells.push_back(ia_cells[2*i+1]);
                    break;
                }
            }
            
            //std::cout << std::endl;
        }
        
        //std::cout << "fin de la boucle for" << std::endl;
            
        std::vector<int> startCell;
        
        // si aucune cellule de l'IA n'est voisine d'une cellule du joueur
        if (adjacent_cells.size() == 0)
        {
            // On recupere la cellule de l'IA qui comporte le plus de creatures parmi la liste complete de ses cellules
            startCell = betterIAResearch(ia_cells);
            // Autour de cette cellule on selectionne une cellule au hasard
            finalDestination = this->adjacentCellResearch(startCell[0],startCell[1]);
        }
        
        // S'il y a des cellules du joueur voisines de celles de l'IA
        else
        {
            // On recupere parmi les cellules de l'IA voisines du joueur 1 celle qui compte le plus de creatures
            startCell = betterIAResearch(adjacent_cells);
            // Parmi les cellules adjacentes à cette dernière cellule, on tire celle qui compte le moins de creatures :
            finalDestination = this->adjacentEnnemyResearch(player,startCell[0],startCell[1]);
        }
        
        coordsMove[0] = startCell[0];
        coordsMove[1] = startCell[1];
        coordsMove[2] = finalDestination[0];
        coordsMove[3] = finalDestination[1];
        
        return coordsMove;
    }
    
    // Dans les cellules adjacentes à la cellule argument, on renvoie celle qui rapportera probablement le plus de points à l'IA
    std::vector<int> HeuristicAI::adjacentEnnemyResearch (int player, int init_i, int init_j)
    {
        //std::cout << "HeuristicAI::adjacentEnnemyResearch - coordonnees argument : (" << init_i << "," << init_j << ")" << std::endl;
        
        // On declare un tableau dans lequel on mettra les coordonnees des cellules adjacentes
        std::vector<int> adjacent_Cells;
        std::vector<int> finalCell;
        std::vector<int> possibleAdjs = this->getAdjacences(init_i,init_j);
        bool verifBornes = false;
        bool occupation = false;
        int tabWidth = getMoteur()->getState().getCharacters()->getWidth();
        int tabHeight = getMoteur()->getState().getCharacters()->getHeight();
        CreaturesTab* creaTab = getMoteur()->getState().getCharacters().get();
        
        for (int i = 0; i < 6; i++)
        {
            // On verifie les bornes (pour ne pas se retrouver à chercher une case hors de la grille !)
            if (i >= 0 && i < 3)
                verifBornes = (possibleAdjs[2 * i] >= 0 && possibleAdjs[2 * i + 1] < tabWidth);
            else if (i >= 3 && i < 6)
                verifBornes = (possibleAdjs[2 * i] < tabHeight && possibleAdjs[2 * i + 1] >= 0);
            
            //std::cout << "HeuristicAI::adjacentEnnemyResearch - verifBornes : " << verifBornes << std::endl;

            // On verifie de plus si l'adjacence amene à une case valide
            if (verifBornes && creaTab->isEnable(possibleAdjs[2*i],possibleAdjs[2*i+1]))
            {
                //std::cout << "HeuristicAI::adjacentEnnemyResearch - coordonnees possible adjacence : (" << possibleAdjs[2*i] << "," << possibleAdjs[2*i+1] << ")" << std::endl;
                
                // On verifie si la cellule adjacente possible est occupee ou non par l'adversaire
                occupation = creaTab->isOccupiedByOpp(possibleAdjs[2 * i], possibleAdjs[2 * i + 1], getMoteur()->getPlayer(player).get());

                if (occupation) {
                    //std::cout << "HeuristicAI::adjacentEnnemyResearch - coordonnees adjacence : (" << possibleAdjs[2*i] << "," << possibleAdjs[2*i+1] << ")" << std::endl;
                    // Si les deux conditions sont verifiees, la cellule adjacente etudiee appartient au joueur reel 
                    adjacent_Cells.push_back(possibleAdjs[2 * i]);
                    adjacent_Cells.push_back(possibleAdjs[2 * i + 1]);
                }
            }
            
        }
        
        //std::cout << "HeuristicAI::adjacentEnnemyResearch - fin recherche cellule adjacente" << std::endl;
        
        // Si on trouve aucune cellule adjacente adverse
        if (adjacent_Cells.size() == 0)
            // On leve une exception car on part du principe que la cellule argument a au moins une cellule adverse adjacente
            throw std::runtime_error("HeuristicAI::adjacentEnnemyResearch - La cellule donnee en argument n'a pas de voisine appartenant à l'adversaire !");
        
        // On cherche parmi les cellules adjacentes celles qui comporte le moins de creatures
        finalCell = weakerEnnemyResearch(adjacent_Cells);
        
        return finalCell;
        
    }
    
    // Parmi la liste fournie en argument (liste de coordonnees de cellules), on recherche la cellule qui comporte le plus de creatures
    std::vector<int> HeuristicAI::betterIAResearch (std::vector<int>& listeIA)
    {
        //std::cout << "Entree dans betterIAResearch" << std::endl;
        
        if (listeIA.size() == 0)
            throw std::runtime_error("HeuristicAI::betterIAResearch - la liste donnée en argument est vide !");
        if (listeIA.size() % 2 != 0)
            throw std::runtime_error("HeuristicAI::betterIAResearch - la liste donnée en argument de la methode a une longueur impaire !");
        
        int nbrMaxCreatures = 0;
        std::vector<int> betterCell(2);
        betterCell[0] = listeIA[0];
        betterCell[1] = listeIA[1];
        
        // On parcoure la liste des coordonnees donnée en argument
        for (int i = 1; i < (int)(listeIA.size()/2); i++)
        {
            //std::cout << "HeuristicAI::betterIAResearch - (" << listeIA[2*i] << "," << listeIA[2*i+1] << ")" << std::endl;
            // Pour chaque couple de coords, si le nbre de creatures de la cellule correspondante est superieur à celui defini 
            if (getMoteur()->getState().getCharacters()->get(listeIA[2*i],listeIA[2*i + 1])->getCreaturesNbr() > nbrMaxCreatures)
            {
                // On redefini le nombre max de creature
                nbrMaxCreatures = getMoteur()->getState().getCharacters()->get(listeIA[2*i],listeIA[2*i + 1])->getCreaturesNbr();
                // On change les valeurs de la liste betterCell
                betterCell[0] = listeIA[2*i];
                betterCell[1] = listeIA[2*i + 1];
            }
        }
        
        //std::cout << "Sortie de betterIAResearch" << std::endl;
        
        // On renvoie betterCell
        return betterCell;
    }
    
    // Parmi la liste fournie en argument (liste de coordonnees de cellules), on recherche la cellule qui comporte le moins de creatures
    std::vector<int> HeuristicAI::weakerEnnemyResearch (std::vector<int>& listePlayer)
    {
        if (listePlayer.size() % 2 != 0)
            throw std::runtime_error("HeuristicAI::weakerEnnemyResearch - la liste donnée en argument de la methode a une longueur impaire !");
        
        int nbrMaxCreatures = 6;
        std::vector<int> weakerCell(2);
        weakerCell[0] = listePlayer[0];
        weakerCell[1] = listePlayer[1];
        
        // On parcoure la liste des coordonnees donnée en argument
        for (int i = 1; i < (int)(listePlayer.size()/2); i++)
        {
            // Pour chaque couple de coords, si le nbre de creatures de la cellule correspondante est superieur à celui defini 
            if (getMoteur()->getState().getCharacters()->get(listePlayer[2*i],listePlayer[2*i + 1])->getCreaturesNbr() < nbrMaxCreatures)
            {
                // On redefini le nombre max de creature
                nbrMaxCreatures = getMoteur()->getState().getCharacters()->get(listePlayer[2*i],listePlayer[2*i + 1])->getCreaturesNbr();
                // On change les valeurs de la liste betterCell
                weakerCell[0] = listePlayer[2*i];
                weakerCell[1] = listePlayer[2*i + 1];
            }
        }
        
        // On renvoie betterCell
        return weakerCell;
    }
}