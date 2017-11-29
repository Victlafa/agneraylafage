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
                
        // On souhaite tester la capacité speciale liee au ciel
        // On doit pour cela choisir une cellule adverse à attaquer sur la carte ainsi qu'une case de depart
        //std::vector<int> choixCellules = skyCellResearch(moteur);
        
        // On ajoute la commande associee à cette attaque à la liste des commandes
        //listCommands.push_back( std::shared_ptr<engine::Command> ( new engine::SpecialCellCommand(choixCellules[0],choixCellules[1],choixCellules[2],choixCellules[3],2,"sky") ) );
        
        // On souhaite introduire une commande de deplacement/conquete
        // On tire pour cela au sort une cellule de l'ia et une cellule du joueur 1 à attaquer
        std::vector<int> coordsDeplacement = moveCellResearch(moteur);
        
        std::cout << "Coordonnees tirees au hasard pour depart de l'IA heuristique : (" << coordsDeplacement[0] << "," << coordsDeplacement[1] << ")" << std::endl;
        std::cout << "Coordonnees tirees au hasard pour destination de l'IA heuristique : (" << coordsDeplacement[2] << "," << coordsDeplacement[3] << ")" << std::endl;
        
        std::cout << "Nombre de creatures de l'IA heuristique sur (" << coordsDeplacement[0] << "," << coordsDeplacement[1] << ") avant deplacement :" << moteur.getState().getCharacters()->get(coordsDeplacement[0],coordsDeplacement[1])->getCreaturesNbr() << std::endl;
        if (moteur.getState().getCharacters()->get(coordsDeplacement[2],coordsDeplacement[3]) != NULL)
            std::cout << "Nombre de creatures sur (" << coordsDeplacement[2] << "," << coordsDeplacement[3] << ") avant deplacement : " << moteur.getState().getCharacters()->get(coordsDeplacement[2],coordsDeplacement[3])->getCreaturesNbr() << std::endl;
        else
            std::cout << "La case destination est vide" << std::endl;
        
        // On ajoute la commande associee à ce deplacement
        listCommands.push_back(std::shared_ptr<engine::Command> ( new engine::MoveCommand(coordsDeplacement[0], coordsDeplacement[1], coordsDeplacement[2], coordsDeplacement[3], 2)));
        
        for (int i = 0; i < (int)(listCommands.size()); i++)
            listCommands[i]->execute(moteur.getState());
        
        std::cout << "Nombre de creatures de l'IA heuristique sur (" << coordsDeplacement[0] << "," << coordsDeplacement[1] << ") apres deplacement :" << moteur.getState().getCharacters()->get(coordsDeplacement[0],coordsDeplacement[1])->getCreaturesNbr() << std::endl;
        
        if (moteur.getState().getCharacters()->get(coordsDeplacement[2],coordsDeplacement[3]) != NULL)
            std::cout << "Nombre de creatures sur (" << coordsDeplacement[2] << "," << coordsDeplacement[3] << ") apres deplacement : " << moteur.getState().getCharacters()->get(coordsDeplacement[2],coordsDeplacement[3])->getCreaturesNbr() << std::endl;
        else
            throw std::runtime_error("La case de destination est tjrs vide meme apres deplacement !");
        
        
        // On vide la liste des commandes
        listCommands.clear();
    }
    
    // On cherche une cellule attaquante pour l'IA ainsi qu'une cellule destination adverse ADJACENTE
    std::vector<int> HeuristicAI::moveCellResearch (engine::Engine& moteur)
    {
        // On recupere la liste des coordonnees des cellules possedees par le joueur reel
        std::vector<int> real_cells = this->playerCellResearch(moteur,1);  // OOKKKK
        // On recupere la liste des coordonnees des cellules possedees par l'IA
        std::vector<int> ia_cells = this->playerCellResearch(moteur,2);  // OOKKKKK
//        std::cout << "Nombre de cellules possedées par l'IA : " << ia_cells.size()/2 << std::endl;
//        
//        for (int k=0; k < ia_cells.size(); k ++)
//            std::cout << ia_cells[k] << " ";
//        std::cout << "\n" << std::endl;
//        for (int a=0; a < real_cells.size(); a ++)
//            std::cout << real_cells[a] << " ";
//        std::cout << std::endl;
        
        // On declare un tableau où on mettra temporairement les coordonnees des cellules de l'IA qui ont des cellules du joueur 1 pour voisines
        std::vector<int> adjacent_cells;
        // On declare le tableau qui comportera les coordonnees de destination
        std::vector<int> finalDestination;
        // On declare le tableau qui comportera les coordonnees à renvoyer
        std::vector<int> coordsMove(4);
        
        // On fait le tour de la liste de l'ia
        for (int i = 0; i < (int)(ia_cells.size()/2); i++)
        { 
            //std::cout << "i : " << i << "\n";
            // Pour chaque cellule de l'ia on explore toutes les cellules du joueur 1, on sort de cette seconde boucle for si on en trouve une
            for (int j = 0; j < (int)(real_cells.size()/2); j++){
            
                //std::cout << "     j :" << j << " ";
                
                //std::cout << "Validite cellule : " << moteur.getState().getCharacters()->verifValiditeCase(real_cells[2*j],real_cells[2*j+1]) << std::endl;
                // Si la cellule du joueur est valide et qu'elle est adjacente à celle de l'IA
                if (moteur.getState().getCharacters()->verifValiditeCase(real_cells[2*j],real_cells[2*j+1]) && isAdjacent(ia_cells[2*i],ia_cells[2*i+1],real_cells[2*j],real_cells[2*j+1]))
                {
                    std::cout << "Cellule de l'ia : (" << ia_cells[2*i] << "," << ia_cells[2*i+1] << ")" << std::endl;
                    std::cout << "Cellule adjacente trouvee correspondante : (" << real_cells[2*j] << "," << real_cells[2*j+1] << ")" << std::endl;
                    // On ajoute les coordonnees de l'ia à adjacent_cells
                    adjacent_cells.push_back(ia_cells[2*i]);
                    adjacent_cells.push_back(ia_cells[2*i+1]);
                    break;
                }
            }
            
            std::cout << std::endl;
        }
        
        //std::cout << "fin de la boucle for" << std::endl;
            
        std::vector<int> startCell;
        
        // si aucune cellule de l'IA n'est voisine d'une cellule du joueur
        if (adjacent_cells.size() == 0)
        {
            // On recupere la cellule de l'IA qui comporte le plus de creatures parmi la liste complete de ses cellules
            startCell = betterIAResearch(moteur,ia_cells);
            // Autour de cette cellule on selectionne une cellule au hasard
            finalDestination = this->adjacentCellResearch(moteur,startCell[0],startCell[1]);
        }
        
        // S'il y a des cellules du joueur voisines de celles de l'IA
        else
        {
            // On recupere parmi les cellules de l'IA voisines du joueur 1 celle qui compte le plus de creatures
            startCell = betterIAResearch(moteur,adjacent_cells);
            // Parmi les cellules adjacentes à cette dernière cellule, on tire celle qui compte le moins de creatures :
            finalDestination = this->adjacentEnnemyResearch(moteur,startCell[0],startCell[1]);
        }
        
        coordsMove[0] = startCell[0];
        coordsMove[1] = startCell[1];
        coordsMove[2] = finalDestination[0];
        coordsMove[3] = finalDestination[1];
        
        return coordsMove;
    }
    
    // Dans les cellules adjacentes à la cellule argument, on renvoie celle qui rapportera probablement le plus de points à l'IA
    std::vector<int> HeuristicAI::adjacentEnnemyResearch (engine::Engine& moteur, int init_i, int init_j)
    {
        //std::cout << "HeuristicAI::adjacentEnnemyResearch - coordonnees argument : (" << init_i << "," << init_j << ")" << std::endl;
        
        // On declare un tableau dans lequel on mettra les coordonnees des cellules adjacentes
        std::vector<int> adjacent_Cells;
        std::vector<int> finalCell;
        std::vector<int> possibleAdjs = this->getAdjacences(init_i,init_j);
        bool verifBornes = false;
        bool occupation = false;
        int tabWidth = moteur.getState().getCharacters()->getWidth();
        int tabHeight = moteur.getState().getCharacters()->getHeight();
        
        for (int i = 0; i < 6; i++)
        {
            // On verifie les bornes (pour ne pas se retrouver à chercher une case hors de la grille !)
            if (i >= 0 && i < 3)
                verifBornes = (possibleAdjs[2 * i] >= 0 && possibleAdjs[2 * i + 1] < tabWidth);
            else if (i >= 3 && i < 6)
                verifBornes = (possibleAdjs[2 * i] < tabHeight && possibleAdjs[2 * i + 1] >= 0);
            
            //std::cout << "HeuristicAI::adjacentEnnemyResearch - verifBornes : " << verifBornes << std::endl;

            // On verifie de plus si l'adjacence amene à une case valide
            if (verifBornes && moteur.getState().getCharacters()->verifValiditeCase(possibleAdjs[2*i],possibleAdjs[2*i+1]))
            {
                //std::cout << "HeuristicAI::adjacentEnnemyResearch - coordonnees possible adjacence : (" << possibleAdjs[2*i] << "," << possibleAdjs[2*i+1] << ")" << std::endl;
                
                // On verifie si la cellule adjacente possible est occupee ou non par l'adversaire
                occupation = moteur.getState().getCharacters()->isOccupiedByOpp(possibleAdjs[2 * i], possibleAdjs[2 * i + 1], moteur.getPlayer(2).get());

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
        finalCell = weakerEnnemyResearch(moteur,adjacent_Cells);
        
        return finalCell;
        
    }
    
    // Parmi la liste fournie en argument (liste de coordonnees de cellules), on recherche la cellule qui comporte le plus de creatures
    std::vector<int> HeuristicAI::betterIAResearch (engine::Engine& moteur, std::vector<int>& listeIA)
    {
        std::cout << "Entree dans betterIAResearch" << std::endl;
        
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
            std::cout << "HeuristicAI::betterIAResearch - (" << listeIA[2*i] << "," << listeIA[2*i+1] << ")" << std::endl;
            // Pour chaque couple de coords, si le nbre de creatures de la cellule correspondante est superieur à celui defini 
            if (moteur.getState().getCharacters()->get(listeIA[2*i],listeIA[2*i + 1])->getCreaturesNbr() > nbrMaxCreatures)
            {
                // On redefini le nombre max de creature
                nbrMaxCreatures = moteur.getState().getCharacters()->get(listeIA[2*i],listeIA[2*i + 1])->getCreaturesNbr();
                // On change les valeurs de la liste betterCell
                betterCell[0] = listeIA[2*i];
                betterCell[1] = listeIA[2*i + 1];
            }
        }
        
        std::cout << "Sortie de betterIAResearch" << std::endl;
        
        // On renvoie betterCell
        return betterCell;
    }
    
    // Parmi la liste fournie en argument (liste de coordonnees de cellules), on recherche la cellule qui comporte le moins de creatures
    std::vector<int> HeuristicAI::weakerEnnemyResearch (engine::Engine& moteur, std::vector<int>& listePlayer)
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
            if (moteur.getState().getCharacters()->get(listePlayer[2*i],listePlayer[2*i + 1])->getCreaturesNbr() < nbrMaxCreatures)
            {
                // On redefini le nombre max de creature
                nbrMaxCreatures = moteur.getState().getCharacters()->get(listePlayer[2*i],listePlayer[2*i + 1])->getCreaturesNbr();
                // On change les valeurs de la liste betterCell
                weakerCell[0] = listePlayer[2*i];
                weakerCell[1] = listePlayer[2*i + 1];
            }
        }
        
        // On renvoie betterCell
        return weakerCell;
    }
}