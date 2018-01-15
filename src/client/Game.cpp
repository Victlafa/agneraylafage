/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: pahtatorr
 * 
 * Created on 25 novembre 2017, 18:12
 */

#include "Game.h"

void Start()
{
    int type;
    
    // On demande au joueur 1 quel type de creatures il souhaite jouer
    std::cout << "Quel type de creatures souhaitez-vous jouer ?\n" << std::endl;
    std::cout << "Cuisinier : 1\nForgeron : 2\nBûcheron : 3\nMineur : 4\n" << std::endl;
    std::cin >> type;
    
    // On initialise le moteur de jeu
    Engine moteur(((CreaturesID)(type)),  CreaturesID::BLACKSMITHS);
    
}