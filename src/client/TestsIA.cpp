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
    
    // Pour gestion multi-thread
//    mutex notre_mutex;
//    int tour = 0;
//    // numero du joueur qui commence en premier
//    int beginner = 0;
//    // Declaration de la fenetre
//    sf::RenderWindow gameWindow(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

    void TestsRandomIA() 
    {
        srand(time(NULL));
        
        // On initialise un moteur
        // On choisit les cuisiniers pour le joueur 1
        engine::Engine moteur(CreaturesID::COOKERS, state::CreaturesID::MINERS);
        
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
        engine::Engine moteur(CreaturesID::MINERS, state::CreaturesID::COOKERS);
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
        
        std::cout << "Ici s'affrontent deux IAs heuristiques qui peuvent pour le moment seulement se déplacer et combattre avec les quelques créatures qu'elles ont au départ de la partie. Elles peuvent aussi ajouter des creatures lors d'une phase de renfort." << std::endl;
        std::cout << "La démonstration se fera sur 20 tours." << std::endl;
        std::cout << "De plus nous avons donné la priorité aux combats. Il est donc possible que des groupes de creatures ne cherchent pas à se disperser tant qu'elles n'ont pas d'ennemies à proximité." << std::endl;
        std::cout << "(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;
        
        sf::Event event;
        //clock_t t1,t2;
        
        while (/*tour != 40 &&*/ window.isOpen()) {
            
            while (window.pollEvent(event)) {
                // Fermeture de la fenetre ?
                if (event.type == sf::Event::Closed) window.close();
                // Appui sur une touche de clavier ?
                else if(event.type == sf::Event::EventType::KeyReleased){
                    std::cout << "\n--------------    Tour n°" << tour/2 + 1 << ", c'est à l'IA n°" << tour%2 + 1 << " de jouer    --------------" << std::endl << std::endl;
                    //t1 = clock();
                    // Tour de l'IA n°1
                    if(tour%2==0) ia.run(1);
                    // Tour de l'IA n°2
                    else ia.run(2);
                    // Execution des commandes demandées par les IA
                    //moteur.update();
                    //t2 = clock();
                    
                    //std::cout << "Temps execution jeu sans thread : " << (float)(t2 - t1)/CLOCKS_PER_SEC << std::endl;
                    cout << "TestsHeuristicIA - Nombre de cellules du joueur 1 : " << moteur.getPlayer(1)->getCellNbr() << endl;
                    cout << "TestsHeuristicIA - Nombre de cellules du joueur 2 : " << moteur.getPlayer(2)->getCellNbr() << endl;

                    tour++;
                    moteur.increaseTour();
                    std::cout << "\n(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;
                }
                
            }
            
            if (moteur.getState().getCellNbr() == moteur.getPlayer(1)->getCellNbr() || moteur.getPlayer(2)->getCellNbr() == 0)
            {
                cout << "L'IA n°1 a conquit toute la carte ou a éliminé son adversaire !" << endl;
                break;
            }
            
            else if (moteur.getState().getCellNbr() == moteur.getPlayer(2)->getCellNbr() || moteur.getPlayer(1)->getCellNbr() == 0)
            {
                cout << "L'IA n°2 a conquit toute la carte ou a éliminé son adversaire !" << endl;
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
    
    void TestsRollbackMove()
    {
        srand(time(NULL));
        
        // On initialise un moteur, on choisit les mineurs pour le joueur 1
        engine::Engine moteur(CreaturesID::MINERS, state::CreaturesID::COOKERS);
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
        
        std::cout << "Ici s'affrontent deux IAs heuristiques qui peuvent pour le moment se déplacer et combattre avec les quelques créatures qu'elles ont au départ de la partie." << std::endl;
        std::cout << "La démonstration se fera sur 6 tours. 3 tours en marche avant et 3 autres en rollback" << std::endl;
        std::cout << "De plus nous avons donné la priorité aux combats. Il est donc possible que des groupes de creatures ne cherchent pas à se disperser tant qu'elles n'ont pas d'ennemies à proximité." << std::endl;
        std::cout << "(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;
        
        sf::Event event;
        
        while (tour != 13 && window.isOpen()) {
            
            while (window.pollEvent(event)) {
                // Fermeture de la fenetre ?
                if (event.type == sf::Event::Closed) window.close();
                // Appui sur une touche de clavier ?
                else if(event.type == sf::Event::EventType::KeyReleased){
                    // On effectue des deplacements
                    if (tour == 0)
                        std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%     PHASES NORMALES DE JEU     %%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
                    if (tour == 6)
                        std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%     PHASES DE ROLLBACK     %%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
                    if (tour < 6)
                    {
                        std::cout << "\n--------------    Tour n°" << tour / 2 + 1 << ", c'est à l'IA n°" << tour % 2 + 1 << " de jouer    --------------" << std::endl << std::endl;
                        // Tour de l'IA n°1
                        if (tour % 2 == 0) ia.run(1);
                            // Tour de l'IA n°2
                        else ia.run(2);
                        // Execution des commandes demandées par les IA
                        //moteur.update();
                        
                        std::cout << "\n(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;
                    }
                    // On les annule
                    else if (tour != 12)
                    {
                        std::cout << "\n--------------    Annulation du Tour n°" << 6 - (tour / 2) << ", de l'IA n°" << 2 - tour % 2<< "   --------------" << std::endl << std::endl;
                        moteur.undo();
                        std::cout << "\n(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;
                    }
                    
                    tour++;
                    moteur.increaseTour();
                    
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
    
//    void TestsThread()
//    {
//        // On prend possession du mutex
//        notre_mutex.lock();
//        srand(time(NULL));
//        
//        // On initialise un moteur, on choisit les mineurs pour le joueur 1
//        engine::Engine moteur(CreaturesID::MINERS);
//        // On initialise une ia
//        HeuristicAI ia(&moteur, rand()%30000);
//        
//        // On crée un Layer qui permettra de gerer l'affichage des cellules
//        render::CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
//        // On crée un Layer qui permettra de gerer l'affichage des creatures
//        render::CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
//        std::cout << "\nTID du thread lié à l'affichage : " << this_thread::get_id() << std::endl;
//        
//        std::cout << "Ici s'affrontent deux IAs heuristiques qui peuvent pour le moment se déplacer, combattre avec les quelques créatures qu'elles ont au départ de la partie, et ajouter de nouvelles creatures sur la carte." << std::endl;
//        std::cout << "Pour accelerer le processus, on permet aux IAs d'effectuer trois déplacements (qui peuvent aboutir à un combat) pendant leur phase d'attaque." << std::endl;
//        std::cout << "La démonstration se fera jusqu'à ce que la partie soit achevée." << std::endl;
//        
//        sf::Event event;
//        
//        // On tire au hasard le joueur qui commence en premier
//        beginner = rand()%2 + 1;
//        std::cout << "C'est l'IA n°" << beginner << " qui a ete tirée au sort pour debuter la partie." << std::endl;
//        
//        std::cout << "(APPUYER sur une touche de clavier pour lancer la partie.)" << std::endl;
//        
//        // On créé le thread lie à l'utilisation de l'ia et du moteur
//        thread threadIA(routine_thread,(void*)&ia);
//        
//        while (gameWindow.isOpen()) {
//            
//            while (gameWindow.pollEvent(event)) {
//                // Fermeture de la fenetre ?
//                if (event.type == sf::Event::Closed) gameWindow.close();
//                if (event.type == sf::Event::KeyPressed) std::cout << "\nTID du thread lié à l'affichage : " << this_thread::get_id() << std::endl;
//                notre_mutex.unlock();
//            }
//           
//            if (moteur.getState().getCellNbr() == moteur.getPlayer(1)->getCellNbr() || moteur.getPlayer(2)->getCellNbr() == 0)
//            {
//                cout << "L'IA n°1 a conquit toute la carte ou a totalement eliminé son adversaire !" << endl;
//                break;
//            }
//            
//            else if (moteur.getState().getCellNbr() == moteur.getPlayer(2)->getCellNbr() || moteur.getPlayer(1)->getCellNbr() == 0)
//            {
//                cout << "L'IA n°2 a conquit toute la carte ou a totalement eliminé son adversaire !" << endl;
//                break;
//            }
//            
//            // On met à jour l'affichage
//            cellLayer.initSurface();
//            charsLayer.initSurface();
//            
//            gameWindow.clear();
//            cellLayer.getSurface()->draw(gameWindow);
//            charsLayer.getSurface()->draw(gameWindow);
//            
//            gameWindow.display();
//        }
//        
//        // Attente de la fin du thread
//        threadIA.join();
//        std::cout << "\nNotre démonstration est terminée :)" << std::endl;
//    }
//    
//    void* routine_thread(void* ia)
//    {
//        HeuristicAI* adrIA = (HeuristicAI*) ia;
//        bool is_IA1_winner = (adrIA->getMoteur()->getState().getCellNbr() == adrIA->getMoteur()->getPlayer(1)->getCellNbr() || adrIA->getMoteur()->getPlayer(2)->getCellNbr() == 0);
//        bool is_IA2_winner = (adrIA->getMoteur()->getState().getCellNbr() == adrIA->getMoteur()->getPlayer(2)->getCellNbr() || adrIA->getMoteur()->getPlayer(1)->getCellNbr() == 0);
//        
//        // On reste dans cette boucle tant qu'aucun des deux joueurs n'a gagné la partie et que la fenetre est ouverte
//        while(!is_IA1_winner && !is_IA2_winner && gameWindow.isOpen())
//        {
//            std::lock_guard<std::mutex> lock (notre_mutex);
//            std::cout << "\nTID du thread lié à l'IA et au moteur : " << this_thread::get_id() << std::endl;
//            std::cout << "\n--------------    Tour n°" << tour / 2 + 1 << " - "; 
//            
//            // Tour de l'IA n°1
//            if (tour % 2 == 0) 
//            {
//                std::cout << "C'est à l'IA n°" << beginner << " de jouer    --------------" << std::endl << std::endl;
//                adrIA->run(beginner);
//            }
//            
//            // Tour de l'IA n°2
//            else
//            {
//                std::cout << "C'est à l'IA n°" << 3-beginner << " de jouer    --------------" << std::endl << std::endl;
//                adrIA->run(3-beginner);
//            }
//            
//            tour++;
//            adrIA->getMoteur()->increaseTour();
//            std::cout << "routine_thread - Points de victoire de l'IA n°1 : " << adrIA->getMoteur()->getPlayer(1)->getConquestPoints() << std::endl;
//            std::cout << "routine_thread - Points de victoire de l'IA n°2 : " << adrIA->getMoteur()->getPlayer(2)->getConquestPoints() << std::endl;
//            std::this_thread::sleep_for(std::chrono::seconds(1));
//            
//            // On verifie si l'un des deux joueurs a gagné ou non la partie
//            is_IA1_winner = (adrIA->getMoteur()->getState().getCellNbr() == adrIA->getMoteur()->getPlayer(1)->getCellNbr() || adrIA->getMoteur()->getPlayer(2)->getCellNbr() == 0);
//            is_IA2_winner = (adrIA->getMoteur()->getState().getCellNbr() == adrIA->getMoteur()->getPlayer(2)->getCellNbr() || adrIA->getMoteur()->getPlayer(1)->getCellNbr() == 0);
//            
//        }
//        
//        return 0;
//    }
    
}
