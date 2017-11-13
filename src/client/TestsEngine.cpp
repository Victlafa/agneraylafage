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
        
        // On cree un moteur qui creera automatiquement un etat
        engine::Engine moteur;
        
        int ligneCombat = 2;
        int colonne1 = 3;
        int colonne2 = 4;
        // On place un forgeron
        std::cout << "Creation d'un forgeron associé au joueur 1" << std::endl;
        moteur.getState().getCharacters()->set(new CreaturesGroup(CreaturesID::BLACKSMITH, moteur.getPlayer(1).get()),ligneCombat,colonne1);
        // On place un cuisinie dans la case (4,3)
        std::cout << "Creation d'un cuisinier" << std::endl;
        moteur.getState().getCharacters()->set(new CreaturesGroup(CreaturesID::COOKER, moteur.getPlayer(2).get()),ligneCombat,colonne2);
        // On cree une cellule en (4,3)
        
        //moteur.getState().getGrid()->set(new state::Cell(state::CellTypeID::SIMPLE),4,3);
        
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
}
