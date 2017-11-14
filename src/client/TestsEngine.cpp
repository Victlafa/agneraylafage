/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestsEngine.cpp
 * Author: pahtatorr
 * 
 * Created on 7 novembre 2017, 09:35
 */

#include "TestsEngine.h"

using namespace state;

namespace engine {
    
    void TestsFightCommand(){
        
        srand(time(NULL));
        
        // On cree un moteur qui creera automatiquement un etat
        engine::Engine moteur;
        
        int ligneCombat = 2;
        int colonne1 = 3;
        int colonne2 = 4;
        
        // On place un forgeron
        std::cout << "Creation d'un forgeron associé au joueur 1" << std::endl;
        CreaturesGroup* forgeron = new CreaturesGroup(CreaturesID::BLACKSMITH, 2, moteur.getPlayer(1).get());
        moteur.getState().getCharacters()->set(forgeron,ligneCombat,colonne1);
        // On place un cuisinie dans la case (4,3)
        std::cout << "Creation d'un cuisinier associé au joueur 2" << std::endl;
        CreaturesGroup* cuisinier = new CreaturesGroup(CreaturesID::COOKER, 2, moteur.getPlayer(2).get());
        moteur.getState().getCharacters()->set(cuisinier,ligneCombat,colonne2);
        
        // On souhaite que le joueur 1 attaque le joueur 2
        moteur.getPlayer(1)->setIsStriker(true);
        
        // On ajoute une commande au moteur
        moteur.addCommand(1,new FightCommand(ligneCombat,colonne1,ligneCombat,colonne2));
        // On execute les commandes
        moteur.update();
        // On affiche les points de conquete des deux joueurs 
        std::cout << "Conquetes joueur 1 :" << moteur.getState().getPlayer(1)->getConquestPoints() << std::endl;
        std::cout << "Conquetes joueur 2 :" << moteur.getState().getPlayer(2)->getConquestPoints() << std::endl;

    }
    void TestsMoveCharCommand(){
        
        engine::Engine moteur;
        
        int ligne = 2;
        int colonne = 4;
        
        // On place un forgeron en (ligne,colonne)
        std::cout << "Creation d'un forgeron associé au joueur 1" << std::endl;
        CreaturesGroup* forgeron = new CreaturesGroup(CreaturesID::BLACKSMITH, 2, moteur.getPlayer(1).get());
        moteur.getState().getCharacters()->set(forgeron,ligne,colonne);
        std::cout << "Position avant deplacement : (" << forgeron->getX() << "," << forgeron->getY() << ")\n" << std::endl;
        
        // On ajoute une commande au moteur
        // On souhaite que la creature du joueur se deplace vers la droite
        moteur.addCommand(1,new MoveCharCommand(ligne,colonne,ligne,colonne + 1,1));
        // On execute les commandes
        moteur.update();
        
        // On affiche les positions de la creature
        
        std::cout << "Position apres deplacement : (" << forgeron->getX() << "," << forgeron->getY() << ")\n" << std::endl;
        
    }
    void TestsPoisonCommand(){
        
        engine::Engine moteur;
        
        int ligne = 2;
        int colonne = 4;
        
        // On place un forgeron en (ligne,colonne)
        std::cout << "Creation d'un forgeron associé au joueur 1" << std::endl;
        CreaturesGroup* forgeron = new CreaturesGroup(CreaturesID::BLACKSMITH, 2, moteur.getPlayer(1).get());
        moteur.getState().getCharacters()->set(forgeron,ligne,colonne);
        
        // On empoisonne la case concernee
        moteur.poisonCell(true,ligne,colonne);
        
        std::cout << "Nombres de creatures presentes avant empoisonnement :" << moteur.getState().getCharacters()->get(ligne, colonne)->getCreaturesNbr() << std::endl;
        
        // Ajout d'une commande au moteur
        moteur.addCommand(1,new PoisonCommand(ligne,colonne));
        // On execute les commandes
        moteur.update();
        
        std::cout << "Nombres de creatures presentes apres empoisonnement :" << moteur.getState().getCharacters()->get(ligne, colonne)->getCreaturesNbr() << std::endl;
    }
}
