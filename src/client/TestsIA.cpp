/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TestsIA.h"

using namespace state;
using namespace render;
using namespace std;

namespace ai {

    void TestsRandomIA() 
    {
        srand(time(NULL));
        
        // On initialise un moteur
        // On choisit les cuisiniers pour le joueur 1
        engine::Engine moteur(CreaturesID::COOKERS);
        
        // On initialise une ia
        RandomAI ia(rand()%30000);
 
        ia.run(moteur,1);
        ia.run(moteur,2);
        
    }
    
    void TestsHeuristicIA()
    {
        srand(time(NULL));
        
        // On initialise un moteur
        // On choisit les mineurs pour le joueur 1
        engine::Engine moteur(CreaturesID::MINERS);
        
        // On initialise une ia
        HeuristicAI ia(rand()%30000);
 
        
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        // On crée un Layer qui permettra de gerer l'affichage des cellules
        render::ElementTabLayer cellLayer(*(moteur.getState().getGrid().get()),0);
        
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        render::ElementTabLayer charsLayer(*(moteur.getState().getCharacters().get()),1);
        
        // On initialise les surfaces de ces deux Layers
        cellLayer.initSurface();
        charsLayer.initSurface();
        
        
        // Declaration et chargement des textures à exploiter pour l'affichage
        sf::Texture hexaTexture;
        sf::Texture charsTexture;
        
        // Le premier cas marche chez Victoire, le second chez Aurore
        if (!hexaTexture.loadFromFile("./res/hexa.png")) 
            if(!hexaTexture.loadFromFile("../res/hexa.png"))
                std::cout << "Erreur chargement texture hexa !\n" << std::endl;
        
        if (!charsTexture.loadFromFile("./res/groupes.png")) 
            if(!charsTexture.loadFromFile("../res/groupes.png"))
                std::cout << "Erreur chargement texture groupes !\n" << std::endl;
        
        // On associe les textures chargees aux Surfaces des Layers de cellules et de groupes de creatures
        cellLayer.getSurface()->setTexture(hexaTexture);
        charsLayer.getSurface()->setTexture(charsTexture);
        
        int tour = 0;
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                else if(event.type == sf::Event::EventType::KeyReleased){
                    if(tour%2==0) ia.run(moteur,1);
                    else ia.run(moteur,2);
                    moteur.update();
                    tour++;
                }
            }

            cellLayer.initSurface();
            charsLayer.initSurface();
            
            window.clear();
            cellLayer.getSurface()->draw(window, &hexaTexture);
            charsLayer.getSurface()->draw(window, &charsTexture);

            window.display();
        }

    }
    
}
