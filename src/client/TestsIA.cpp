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
        RandomAI ia(&moteur, rand()%30000);
 
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        // On crée un Layer qui permettra de gerer l'affichage des cellules
        render::CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        render::CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));    
        
        int tour = 0;
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                else if(event.type == sf::Event::EventType::KeyReleased){
                    if(tour%2==0) ia.run(1);
                    else ia.run(2);
                    moteur.update();
                    std::cout << "Fin du tour " << tour << std::endl;
                    tour++;
                }
            }

            cellLayer.initSurface();
            charsLayer.initSurface();
            
            window.clear();
            cellLayer.getSurface()->draw(window);
            charsLayer.getSurface()->draw(window);

            window.display();
        }
        
        
    }
    
    void TestsHeuristicIA()
    {
        srand(time(NULL));
        
        // On initialise un moteur, on choisit les mineurs pour le joueur 1
        engine::Engine moteur(CreaturesID::MINERS);
        // On initialise une ia
        HeuristicAI ia(&moteur, rand()%30000);
        // Declaration de la fenetre
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);
        // On crée un Layer qui permettra de gerer l'affichage des cellules
        render::CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        render::CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
        // On affichera sur un nombre limité de tours
        int tour = 0;
        
        std::cout << "Ici s'affrontent deux IAs heuristiques qui peuvent pour le moment seulement se déplacer et combattre avec les quelques créatures qu'elles ont au départ de la partie." << std::endl;
        std::cout << "La démonstration se fera sur 10 tours. Il est possible que lors de certains tours il n'y ait pas de déplacements car nous n'avons pas encore pu faire en sorte qu'à la fin de chaque tour, des renforts viennent s'ajouter à la carte." << std::endl;
        std::cout << "De plus nous avons donné la priorité aux combats. Il est donc possible que des groupes de creatures ne cherchent pas à se disperser tant qu'elles n'ont pas d'ennemies à proximité." << std::endl;
        std::cout << "(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;
        
        sf::Event event;
        
        while (tour != 40 && window.isOpen()) {
            
            while (window.pollEvent(event)) {
                // Fermeture de la fenetre ?
                if (event.type == sf::Event::Closed) window.close();
                // Appui sur une touche de clavier ?
                else if(event.type == sf::Event::EventType::KeyReleased){
                    std::cout << "\n--------------    Tour n°" << tour/2 + 1 << ", c'est à l'IA n°" << tour%2 + 1 << " de jouer    --------------" << std::endl << std::endl;
                    // Tour de l'IA n°1
                    if(tour%2==0) ia.run(1);
                    // Tour de l'IA n°2
                    else ia.run(2);
                    // Execution des commandes demandées par les IA
                    //moteur.update();
                    tour++;
                    moteur.increaseTour();
                    std::cout << "\n(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;
                }
                
            }
            
            if (moteur.getState().getCellNbr() == moteur.getPlayer(1)->getCellNbr())
            {
                cout << "L'IA n°1 a conquit toute la carte !" << endl;
                break;
            }
            
            else if (moteur.getState().getCellNbr() == moteur.getPlayer(2)->getCellNbr())
            {
                cout << "L'IA n°2 a conquit toute la carte !" << endl;
                break;
            }
            
            // On met à jour l'affichage
            cellLayer.initSurface();
            charsLayer.initSurface();
            
            window.clear();
            cellLayer.getSurface()->draw(window);
            charsLayer.getSurface()->draw(window);
            
            window.display();
        }
        
        std::cout << "\nNotre démonstration est terminée :)" << std::endl;

    }
    
    void TestsRollback()
    {
        srand(time(NULL));
        
        // On initialise un moteur, on choisit les mineurs pour le joueur 1
        engine::Engine moteur(CreaturesID::MINERS);
        // On initialise une ia
        HeuristicAI ia(&moteur, rand()%30000);
        // Declaration de la fenetre
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);
        // On crée un Layer qui permettra de gerer l'affichage des cellules
        render::CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        render::CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
        // On affichera sur un nombre limité de tours
        int tour = 0;
        
        std::cout << "Ici s'affrontent deux IAs heuristiques qui peuvent pour le moment se déplacer et combattre avec les quelques créatures qu'elles ont au départ de la partie. Elles peuvent aussi placer de nouvelles creatures sur la carte pendant la phase de renfort." << std::endl;
        std::cout << "La démonstration se fera sur 10 tours." << std::endl;
        std::cout << "De plus nous avons donné la priorité aux combats. Il est donc possible que des groupes de creatures ne cherchent pas à se disperser tant qu'elles n'ont pas d'ennemies à proximité." << std::endl;
        std::cout << "(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;
        
        sf::Event event;
        
        while (tour != 40 && window.isOpen()) {
            
            while (window.pollEvent(event)) {
                // Fermeture de la fenetre ?
                if (event.type == sf::Event::Closed) window.close();
                // Appui sur une touche de clavier ?
                else if(event.type == sf::Event::EventType::KeyReleased){
                    std::cout << "\n--------------    Tour n°" << tour/2 + 1 << ", c'est à l'IA n°" << tour%2 + 1 << " de jouer    --------------" << std::endl << std::endl;
                    // Tour de l'IA n°1
                    if(tour%2==0) ia.run(1);
                    // Tour de l'IA n°2
                    else ia.run(2);
                    // Execution des commandes demandées par les IA
                    //moteur.update();
                    tour++;
                    moteur.increaseTour();
                    std::cout << "\n(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;
                }
                
            }
            
            if (moteur.getState().getCellNbr() == moteur.getPlayer(1)->getCellNbr())
            {
                cout << "L'IA n°1 a conquit toute la carte !" << endl;
                break;
            }
            
            else if (moteur.getState().getCellNbr() == moteur.getPlayer(2)->getCellNbr())
            {
                cout << "L'IA n°2 a conquit toute la carte !" << endl;
                break;
            }
            
            // On met à jour l'affichage
            cellLayer.initSurface();
            charsLayer.initSurface();
            
            window.clear();
            cellLayer.getSurface()->draw(window);
            charsLayer.getSurface()->draw(window);
            
            window.display();
        }
        
        std::cout << "\nNotre démonstration est terminée :)" << std::endl;
    }
    
    
}
