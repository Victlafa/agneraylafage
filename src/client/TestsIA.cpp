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
                    std::cout << "Fin du tour " << tour << std::endl;
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
        
        std::cout << "Ici s'affrontent deux IAs heuristiques qui peuvent pour le moment seulement se déplacer et combattre avec les quelques créatures qu'elles ont au départ de la partie." << std::endl;
        std::cout << "La démonstration se fera sur 10 tours. Il est possible que lors de certains tours il n'y ait pas de déplacements car nous n'avons pas encore pu faire en sorte qu'à la fin de chaque tour, des renforts viennent s'ajouter à la carte." << std::endl;
        std::cout << "De plus nous avons donné la priorité aux combats. Il est donc possible que des groupes de creatures ne cherchent pas à se disperser tant qu'elles n'ont pas d'ennemies à proximité." << std::endl;
        std::cout << "(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;
        
        while (tour != 20 && window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                
                if (event.type == sf::Event::Closed) window.close();
                else if(event.type == sf::Event::EventType::KeyReleased){
                    std::cout << "\n--------------    Tour n°" << tour/2 + 1 << ", c'est à l'IA n°" << tour%2 + 1 << " de jouer    --------------" << std::endl;
                    if(tour%2==0) ia.run(moteur,1);
                    else ia.run(moteur,2);
                    moteur.update();
                    tour++;
                    moteur.increaseTour();
                    std::cout << "\n(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;
                }
                
            }

            cellLayer.initSurface();
            charsLayer.initSurface();
            
            window.clear();
            cellLayer.getSurface()->draw(window, &hexaTexture);
            charsLayer.getSurface()->draw(window, &charsTexture);
            
            

            window.display();
        }
        
        std::cout << "\nNotre démonstration est terminée :)" << std::endl;

    }
    
    
    
}
