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
        
        // On initialise une ia
        RandomAI ia(rand()%30000);
        
        // On recupere le joueur 2
        state::Player* player_ia = moteur.getPlayer(2).get();
        
        // On initialise une liste de commandes
        std::vector<std::shared_ptr<engine::Command> > commands;
        
        // On va chercher une creature de l'IA dans le moteur donné en argument
        unsigned int ligne = 0;
        unsigned int colonne = 0;
        // On prepare une case de destination
        unsigned int new_ligne = 0;
        unsigned int new_colonne = 0;
        
        //int randCommand = 0;
        
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
                        std::cout << "Coordonnees : (" << i << "," << j << ") " << std::endl;
                        std::cout << "Groupe de creatures selectionne : " << moteur.getState().getCharacters()->get(i,j).get() << std::endl;
                        std::cout << "Nombre de creatures du groupe : " << moteur.getState().getCharacters()->get(i,j)->getCreaturesNbr() << std::endl;
                        
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
        // Deplacement possible vers la gauche ?
        if (colonne > 0 && moteur.getState().getCharacters()->get(ligne,colonne-1).get() == NULL && moteur.getState().getCharacters()->verifValiditeCase(ligne,colonne-1))
            new_colonne -= 1;
        // Vers la droite ?
        else if (colonne < moteur.getState().getCharacters()->getWidth() && moteur.getState().getCharacters()->get(ligne,colonne + 1).get() == NULL && moteur.getState().getCharacters()->verifValiditeCase(ligne,colonne+1))
            new_colonne += 1;
        // Vers le haut ?
        else if (ligne > 0 && moteur.getState().getCharacters()->get(ligne-1,colonne).get() == NULL && moteur.getState().getCharacters()->verifValiditeCase(ligne - 1,colonne))
            new_ligne -= 1;
        // Vers le bas ?
        else if (ligne < moteur.getState().getCharacters()->getHeight() && moteur.getState().getCharacters()->get(ligne + 1,colonne).get() == NULL && moteur.getState().getCharacters()->verifValiditeCase(ligne + 1,colonne))
            new_ligne += 1;
        else
            throw std::runtime_error("Aucune possibilite de deplacement pour l'ia !");
        
        // Commande de deplacement
        commands.push_back(std::shared_ptr<engine::Command>(new engine::MoveCommand(ligne, colonne, new_ligne, new_colonne, 2)));
                
        // On ajoute cette liste de commandes à l'ia
        ia.setListCommands(commands);
        // On met l'ia en route
        ia.run(moteur);
        
    }
    
}
