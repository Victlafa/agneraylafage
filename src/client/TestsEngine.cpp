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

namespace engine {
    
    void TestsFightCommand(){
        
        // On cree un moteur qui creera automatiquement un etat
        engine::Engine moteur;
        int ligneCombat = 2;
        int colonne1 = 3;
        int colonne2 = 4;
        // On place un forgeron
        std::cout << "Creation d'un forgeron" << std::endl;
        moteur.getState().getCharacters()->set(new state::CreaturesGroup(state::CreaturesID::BLACKSMITH),ligneCombat,colonne1);
        // On place un cuisinie dans la case (4,3)
        std::cout << "Creation d'un cuisinier" << std::endl;
        moteur.getState().getCharacters()->set(new state::CreaturesGroup(state::CreaturesID::COOKER),ligneCombat,colonne2);
        // On cree une cellule en (4,3)
        
        //moteur.getState().getGrid()->set(new state::Cell(state::CellTypeID::SIMPLE),4,3);
        
        // On associe le numero du forgeron au joueur 1
        moteur.getState().getPlayer(1)->setAllCreatures(true, ligneCombat*7 + colonne1 - 1);
        std::cout << "Creature presente en (2,3) : " << moteur.getState().getPlayer(1)->getAllCreatures().at(ligneCombat*7 + colonne1 - 1) << std::endl;
        
        // On associe le numero du cuisinier au joueur 2
        moteur.getState().getPlayer(2)->setAllCreatures(true, ligneCombat*7 + colonne2 - 1);
        std::cout << "Creature presente en (2,4) : " << moteur.getState().getPlayer(2)->getAllCreatures().at(ligneCombat*7 + colonne2 - 1) << std::endl;

        // On souhaite que le joueur 1 attaque le joueur 2
        moteur.getState().getPlayer(1)->setIsStriker(true);
        
        // On ajoute une commande au moteur
        moteur.addCommand(1,new FightCommand(ligneCombat*7 + colonne1 - 1, ligneCombat*7 + colonne2 - 1, ligneCombat*7 + colonne2 - 1));
        // On execute les commandes
        moteur.update();
        // On affiche les points de conquete des deux joueurs 
        std::cout << "Conquetes joueur 1 :" << moteur.getState().getPlayer(1)->getConquestPoints() << std::endl;
        std::cout << "Conquetes joueur 2 :" << moteur.getState().getPlayer(2)->getConquestPoints() << std::endl;

    }
}
