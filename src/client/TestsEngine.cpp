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
        
        // On place un forgeron dans la case (4,2)
        moteur.getState().getCharacters().set(new state::CreaturesGroup(state::CreaturesID::BLACKSMITH),4,2);
        // On place un cuisinier dans la case (4,3)
        moteur.getState().getCharacters().set(new state::CreaturesGroup(state::CreaturesID::COOKER),4,3);
        std::cout << "Adresse du joueur 1 : " << moteur.getState().getPlayer(1).get() << std::endl;
        // On cree une cellule en (4,3)
        moteur.getState().getGrid().set(new state::Cell(state::CellTypeID::SIMPLE),4,3);
        
        // On associe le numero du forgeron au joueur 1
        moteur.getState().getPlayer(1)->setAllCreatures(true, 4*7 + 2 - 1);
        
        // On associe le numero du cuisinier au joueur 2
        moteur.getState().getPlayer(2)->setAllCreatures(true, 4*7 + 3 - 1);
        
        // On souhaite que le joueur 1 attaque le joueur 2
        moteur.getState().getPlayer(1)->setIsStriker(true);
        
        // On ajoute une commande au moteur
        moteur.addCommand(1,new FightCommand(4*7 + 2 - 1, 4*7 + 3 - 1, 4*7 + 3 - 1));
        // On execute les commandes
        moteur.update();
        // On affiche les points de conquete des deux joueurs 
        std::cout << "Conquetes joueur 1 :" << moteur.getState().getPlayer(1)->getConquestPoints() << std::endl;
        std::cout << "Conquetes joueur 2 :" << moteur.getState().getPlayer(2)->getConquestPoints() << std::endl;

    }
}
