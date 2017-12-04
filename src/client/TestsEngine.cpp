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
using namespace render;
using namespace std;

namespace engine {
        
    void TestsPoisonCommand(){
        
        cout << "DEBUT TESTS POISONCOMMAND" << endl;
        
        engine::Engine moteur(CreaturesID::BLACKSMITHS);
        
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        // On crée un Layer qui permettra de gerer l'affichage des cellules
        CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
        
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
        
        int ligne = 2;
        int colonne = 4;
        int iter = 0;
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                
                if (event.type == sf::Event::Closed) window.close();
                else if((event.type == sf::Event::EventType::KeyReleased) && (iter==0)){
                    // On place un forgeron en (ligne,colonne)
                    std::cout << "Creation d'un forgeron associé au joueur 1" << std::endl;
                    state::CreaturesGroup *forgeron = new CreaturesGroup(ID::BLACKSMITH, 2, moteur.getPlayer(1).get());
                    
                    while(moteur.getState().getCharacters()->get(ligne,colonne)!=NULL){
                        ligne = rand()%5;
                        colonne = rand()%3+2;
                    }
                    
                    moteur.getState().getCharacters()->set(forgeron,ligne,colonne);
                    moteur.update();
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==1)){
                    // On empoisonne la case concernee
                    moteur.poisonCell(true,ligne,colonne);
                    moteur.update();
                    std::cout << "Nombres de creatures presentes avant empoisonnement :" << moteur.getState().getCharacters()->get(ligne, colonne)->getCreaturesNbr() << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==2)){
                    // Ajout d'une commande au moteur
                    moteur.addCommand(1,new PoisonCommand(ligne,colonne));
                    // On execute les commandes
                    moteur.update();
                    std::cout << "Nombres de creatures presentes apres empoisonnement :" << moteur.getState().getCharacters()->get(ligne, colonne)->getCreaturesNbr() << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==3)){
                    cout << "FIN TESTS POISONCOMMAND" << endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==4)){
                    window.close();
                }
            }

            cellLayer.initSurface();
            charsLayer.initSurface();
            
            window.clear();
            cellLayer.getSurface()->draw(window);
            charsLayer.getSurface()->draw(window);

            window.display();
        }

        cout << "FIN TESTS POISONCOMMAND" << endl;
        
    }
    
    void TestsNewGameCommand(){
        cout << "DEBUT TESTS NEWGAMECOMMAND" << endl;
        
        int iter = 0;
        
        // On initialise un moteur
        engine::Engine moteur(CreaturesID::BLACKSMITHS);
        
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        // On crée un Layer qui permettra de gerer l'affichage des cellules
        CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
        
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
        
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                
                if (event.type == sf::Event::Closed) window.close();
                else if((event.type == sf::Event::EventType::KeyReleased) && (iter==0)){
                    // On place un forgeron en (ligne,colonne)
                    std::cout << "Etat avant : " << &moteur.getState() << std::endl;
                    std::cout << "Grille avant : " << moteur.getState().getGrid().get() << std::endl;
                    moteur.update();
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==1)){
                    moteur.addCommand(1,new NewGameCommand());
                    moteur.update();
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==2)){
                    std::cout << "Etat apres : " << &moteur.getState() << std::endl;
                    std::cout << "Grille apres : " << moteur.getState().getGrid().get() << std::endl;
                    std::cout << "Type de creatures du joueur 1 : " << moteur.getPlayer(1)->getClanName() << std::endl;
                    moteur.update();
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==3)){
                    cout << "FIN TESTS NEWGAMECOMMAND" << endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==4)){
                    window.close();
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
    
    void TestsMoveCommandAdv(){
        
        cout << "DEBUT TESTS MOVECOMMAND - Deplacement vers une case occupée par l'adversaire" << endl;
        
        engine::Engine moteur(CreaturesID::BLACKSMITHS);
        
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        // On crée un Layer qui permettra de gerer l'affichage des cellules
        CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
        
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
        
        std::cout << "Joueur 1 de l'état : " << moteur.getPlayer(1).get() << std::endl;
        std::cout << "Joueur 2 de l'état : " << moteur.getPlayer(2).get() << std::endl;
        
        int ligne = 2;
        int colonne = 4;
        int iter = 0;
        
        CreaturesGroup* forgeron;
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                
                if (event.type == sf::Event::Closed) window.close();
                else if((event.type == sf::Event::EventType::KeyReleased) && (iter==0)){
                    // On place un forgeron en (ligne,colonne)
                    std::cout << "Creation d'un forgeron associé au joueur 1" << std::endl;
                    forgeron = new CreaturesGroup(ID::BLACKSMITH, 5, moteur.getPlayer(1).get());
                    
                    while((moteur.getState().getCharacters()->get(ligne,colonne)!=NULL)||(moteur.getState().getCharacters()->get(ligne,colonne+1)!=NULL)){
                        ligne = rand()%5;
                        colonne = rand()%3+2;
                    }
                    
                    std::cout << "Joueur associe au forgeron : " << forgeron->getPlayer() << std::endl;
                    moteur.getState().getCharacters()->set(forgeron,ligne,colonne);
                    std::cout << "Position avant deplacement : (" << forgeron->getX() << "," << forgeron->getY() << ")\n" << std::endl;
                    std::cout << "Nbre de creatures attaquantes avant deplacement : " << forgeron->getCreaturesNbr() << std::endl;
                    std::cout << "Joueur attaquant : " << forgeron->getPlayer() << std::endl;
                    
                    moteur.update();
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==1)){
                    // On place un cuisinier dans la case à droite
                    std::cout << "Creation d'un cuisinier associé au joueur 2" << std::endl;
                    CreaturesGroup* cuisinier = new CreaturesGroup(ID::COOKER, 3, moteur.getPlayer(2).get());
                    moteur.getState().getCharacters()->set(cuisinier,ligne,colonne + 1);
                    std::cout << "Nbre de creatures de defense avant deplacement : " << cuisinier->getCreaturesNbr() << std::endl;
                    std::cout << "Joueur defenseur : " << cuisinier->getPlayer() << std::endl;
                    
                    moteur.update();
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==2)){
                    // On ajoute une commande au moteur
                    // On souhaite que la creature du joueur se deplace vers la droite
                    moteur.addCommand(1,new MoveCommand(ligne,colonne,ligne,colonne + 1,1));
                    
                    moteur.update();
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==3)){
                    // On affiche les positions de la creature
                    if (forgeron)
                        std::cout << "Nbre de creatures d'attaque apres deplacement : " << forgeron->getCreaturesNbr() << std::endl;
                    else
                        throw std::runtime_error("TestsEngine::TestsMoveCommandAdv - ligne 270 - La variable forgeron n'est pas initialisee");
                    
                    std::cout << "Nbre de creatures de defense apres deplacement : " << moteur.getState().getCharacters()->get(ligne, colonne +1)->getCreaturesNbr() << std::endl;
                    std::cout << "Joueur present en attaque : " << moteur.getState().getCharacters()->get(ligne, colonne)->getPlayer() << std::endl;
                    std::cout << "Joueur present en defense : " << moteur.getState().getCharacters()->get(ligne, colonne + 1)->getPlayer() << std::endl;

                    std::cout << "Conquetes joueur 1 :" << moteur.getState().getPlayer(1)->getConquestPoints() << std::endl;
                    std::cout << "Conquetes joueur 2 :" << moteur.getState().getPlayer(2)->getConquestPoints() << std::endl;

                    std::cout << "Joueur 1 de l'état : " << moteur.getPlayer(1).get() << std::endl;
                    std::cout << "Joueur 2 de l'état : " << moteur.getPlayer(2).get() << std::endl;
                    
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==4)){
                    cout << "FIN TESTS MOVECOMMAND - Deplacement vers une case occupée par l'adversaire" << endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==5)){
                    window.close();
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
    
    void TestsMoveCommandPlayer(){
        cout << "\n\nDEBUT TESTS MOVECOMMAND - Deplacement vers une case occupée par le joueur" << endl;
        
        engine::Engine moteur(CreaturesID::BLACKSMITHS);
        
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        // On crée un Layer qui permettra de gerer l'affichage des cellules
        CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
        
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
        
        std::cout << "Joueur 1 de l'état : " << moteur.getPlayer(1).get() << std::endl;
        
        int ligne = 2;
        int colonne = 4;
        int iter = 0;
        
        CreaturesGroup* forgeron;
        CreaturesGroup* forgeron2;
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                
                if (event.type == sf::Event::Closed) window.close();
                else if((event.type == sf::Event::EventType::KeyReleased) && (iter==0)){
                    // On place un forgeron en (ligne,colonne)
                    std::cout << "Creation d'un forgeron associé au joueur 1" << std::endl;
                    forgeron = new CreaturesGroup(ID::BLACKSMITH, 2, moteur.getPlayer(1).get());
                    
                    while((moteur.getState().getCharacters()->get(ligne,colonne)!=NULL)||(moteur.getState().getCharacters()->get(ligne,colonne+1)!=NULL)){
                        ligne = rand()%5;
                        colonne = rand()%3+2;
                    }
                    
                    std::cout << "Joueur associe au forgeron : " << forgeron->getPlayer() << std::endl;
                    moteur.getState().getCharacters()->set(forgeron,ligne,colonne);
                    std::cout << "Nbre de creatures sur case de depart avant deplacement : " << forgeron->getCreaturesNbr() << std::endl;
        
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==1)){
                    // On place un autre forgeron dans la case à droite
                    forgeron2 = new CreaturesGroup(ID::BLACKSMITH, 1, moteur.getPlayer(1).get());
                    moteur.getState().getCharacters()->set(forgeron2,ligne,colonne + 1);
                    std::cout << "Nbre de creatures sur la case destination avant deplacement : " << forgeron2->getCreaturesNbr() << std::endl;
        
                    moteur.update();
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==2)){
                    // On ajoute une commande au moteur
                    // On souhaite que la creature du joueur se deplace vers la droite
                    moteur.addCommand(1,new MoveCommand(ligne,colonne,ligne,colonne + 1,1));
                    // On execute les commandes
                    moteur.update();
        
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==3)){
                    if (forgeron)
                        std::cout << "Nbre de creatures sur case de depart apres deplacement : " << forgeron->getCreaturesNbr() << std::endl;
                    else
                        throw std::runtime_error("TestsEngine::TestsMoveCommandPlayer - ligne 382 - La variable forgeron n'est pas initialisee");
                    
                    std::cout << "Nbre de creatures sur case de destination apres deplacement : " << moteur.getState().getCharacters()->get(ligne, colonne +1)->getCreaturesNbr() << std::endl;
        
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==4)){
                    cout << "FIN TESTS MOVECOMMAND - Deplacement vers une case occupée par le joueur" << endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==5)){
                    window.close();
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
    
    void TestsMoveCommandNoOne(){
        cout << "DEBUT TESTS MOVECOMMAND - Deplacement vers une case vide" << endl;
        
        engine::Engine moteur(CreaturesID::BLACKSMITHS);
        
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        // On crée un Layer qui permettra de gerer l'affichage des cellules
        CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
        
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
        
        std::cout << "Joueur 1 de l'état : " << moteur.getPlayer(1).get() << std::endl;
        
        int ligne = 2;
        int colonne = 4;
        int iter = 0;
        
        CreaturesGroup* forgeron;
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                
                if (event.type == sf::Event::Closed) window.close();
                else if((event.type == sf::Event::EventType::KeyReleased) && (iter==0)){
                    // On place un forgeron en (ligne,colonne)
                    std::cout << "Creation d'un forgeron associé au joueur 1" << std::endl;
                    forgeron = new CreaturesGroup(ID::BLACKSMITH, 5, moteur.getPlayer(1).get());
                    
                    while(moteur.getState().getCharacters()->get(ligne,colonne)!=NULL){
                        ligne = rand()%5;
                        colonne = rand()%3+2;
                    }
                    
                    std::cout << "Joueur associe au forgeron : " << forgeron->getPlayer() << std::endl;
                    moteur.getState().getCharacters()->set(forgeron,ligne,colonne);
                    std::cout << "Nbre de creatures sur case de depart avant deplacement : " << forgeron->getCreaturesNbr() << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==1)){
                    // On force la case à droite à etre vide
                    moteur.getState().getCharacters()->set(nullptr,ligne,colonne + 1);
                    
                    moteur.update();
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==2)){
                    // On ajoute une commande au moteur
                    // On souhaite que la creature du joueur se deplace vers la droite
                    moteur.addCommand(1,new MoveCommand(ligne,colonne,ligne,colonne + 1,1));
                    // On execute les commandes
                    moteur.update();
        
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==3)){
                    if (forgeron)
                        std::cout << "Nbre de creatures sur case de depart apres deplacement : " << forgeron->getCreaturesNbr() << std::endl;
                    else
                        throw std::runtime_error("TestsEngine::TestsMoveCommandNoOne - ligne 482 - La variable forgeron n'est pas initialisee");
                    
                    std::cout << "Nbre de creatures sur case de destination apres deplacement : " << moteur.getState().getCharacters()->get(ligne, colonne +1)->getCreaturesNbr() << std::endl;
        
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==4)){
                    cout << "FIN TESTS MOVECOMMAND - Deplacement vers une case vide" << endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==5)){
                    window.close();
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
    
    void TestsSpecialCommandBBQ(){
        
        cout << "\n\nDEBUT TESTS SpecialCommand BBQ" << endl;
        
        srand(time(NULL));
        
        // On initialise un moteur
        // On choisit les cuisiniers pour le joueur 1
        engine::Engine moteur(CreaturesID::COOKERS);
        
        // On attribue trois cellules speciales au joueur 1
        std::vector<std::string> speCells;
        speCells.push_back("sky");
        speCells.push_back("barbecue");
        speCells.push_back("candy");
        moteur.getPlayer(1)->setSpeCellsNames(speCells);
        moteur.getPlayer(1)->setCreaturesLeft(2);
        
        int ligneDep = 2;
        int colonneDep = 3;
        int ligneArr = 4;
        int colonneArr = 4;
        
        if((moteur.getState().getCharacters()->get(ligneDep,colonneDep)!=NULL)||(moteur.getState().getCharacters()->get(ligneArr,colonneArr)!=NULL)){
            moteur.getState().getCharacters()->set(nullptr,ligneDep,colonneDep);
            moteur.getState().getCharacters()->set(nullptr,ligneArr,colonneArr);
        }
        
        
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        // On crée un Layer qui permettra de gerer l'affichage des cellules
        CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
        
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
        
        std::cout << "Joueur 1 de l'état : " << moteur.getPlayer(1).get() << std::endl;
        
        int iter = 0;
        
        CreaturesGroup* cuisinier;
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                
                if (event.type == sf::Event::Closed) window.close();
                else if((event.type == sf::Event::EventType::KeyReleased) && (iter==0)){
                    // On place un cuisinier
                    std::cout << "Creation d'un cuisinier associé au joueur 1" << std::endl;
                    cuisinier = new CreaturesGroup(ID::COOKER, 2, moteur.getPlayer(1).get());
                    moteur.getState().getCharacters()->set(cuisinier,ligneDep,colonneDep);
        
                    std::cout << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==1)){
                    // On place un adv dans la case (ligneArr,colonneArr)
                    std::cout << "Creation d'un groupe associé au joueur 2" << std::endl;
                    CreaturesGroup* player2Crea = new CreaturesGroup((ID)moteur.getPlayer(2)->getClanName(), 2, moteur.getPlayer(2).get());
                    moteur.getState().getCharacters()->set(player2Crea,ligneArr,colonneArr);
        
                    moteur.update();
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==2)){
                    // On ajoute une commande au moteur
                    // Test de la capacite speciale liee au barbecue ou à la piscine
                    moteur.addCommand(1,new SpecialCellCommand(ligneDep,colonneDep,ligneArr,colonneArr,1,"barbecue"));
                    std::cout << "Nombre de creatures dans la case de l'IA avant utilisation du barbecue : " << moteur.getState().getCharacters()->get(ligneArr,colonneArr)->getCreaturesNbr() << std::endl;

                    // On execute les commandes
                    moteur.update();
        
                    std::cout << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==3)){
                    std::cout << "Nombre de creatures dans la case de l'IA apres utilisation du barbecue : " << moteur.getState().getCharacters()->get(ligneArr,colonneArr)->getCreaturesNbr() << std::endl;
                    std::cout << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==4)){
                    cout << "FIN TESTS SpecialCommand BBQ" << endl;
                    std::cout << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==5)){
                    window.close();
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
    
    void TestsSpecialCommandSKY(){
        
        cout << "DEBUT TESTS SpecialCommand SKY" << endl;
        
        srand(time(NULL));
        
        // On initialise un moteur
        // On choisit les cuisiniers pour le joueur 1
        engine::Engine moteur(CreaturesID::COOKERS);
        
        // On attribue trois cellules speciales au joueur 1
        std::vector<std::string> speCells;
        speCells.push_back("sky");
        speCells.push_back("barbecue");
        speCells.push_back("candy");
        moteur.getPlayer(1)->setSpeCellsNames(speCells);
        moteur.getPlayer(1)->setCreaturesLeft(2);
        
        int ligneDep = 2;
        int colonneDep = 4;
        int ligneArr = 1;
        int colonneArr = 1;
        
        if((moteur.getState().getCharacters()->get(ligneDep,colonneDep)!=NULL)||(moteur.getState().getCharacters()->get(ligneArr,colonneArr)!=NULL)){
            moteur.getState().getCharacters()->set(nullptr,ligneDep,colonneDep);
            moteur.getState().getCharacters()->set(nullptr,ligneArr,colonneArr);
        }
        
        
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        // On crée un Layer qui permettra de gerer l'affichage des cellules
        CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
        
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
        
        std::cout << "Joueur 1 de l'état : " << moteur.getPlayer(1).get() << std::endl;
        
        int iter = 0;
        
        CreaturesGroup* cuisinier;
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                
                if (event.type == sf::Event::Closed) window.close();
                else if((event.type == sf::Event::EventType::KeyReleased) && (iter==0)){
                    // On place un cuisinier
                    std::cout << "Creation d'un cuisinier associé au joueur 1" << std::endl;
                    cuisinier = new CreaturesGroup(ID::COOKER, 2, moteur.getPlayer(1).get());
                    moteur.getState().getCharacters()->set(cuisinier,ligneDep,colonneDep);
                    
                    std::cout << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==1)){
                    // On place un adv dans la case (ligneArr,colonneArr)
                    std::cout << "Creation d'un groupe associé au joueur 2" << std::endl;
                    CreaturesGroup* player2Crea = new CreaturesGroup((ID)moteur.getPlayer(2)->getClanName(), 2, moteur.getPlayer(2).get());
                    moteur.getState().getCharacters()->set(player2Crea,ligneArr,colonneArr);
        
                    std::cout << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==2)){
                    // On ajoute une commande au moteur
                    // Test de la capacite speciale liee au jet-pack
                    moteur.addCommand(1,new SpecialCellCommand(ligneDep,colonneDep,ligneArr,colonneArr,1,"sky"));
                    std::cout << "Nombre de creatures dans la case de l'IA avant utilisation du jet-pack : " << moteur.getState().getCharacters()->get(ligneArr,colonneArr)->getCreaturesNbr() << std::endl;
                    moteur.update();
        
                    std::cout << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==3)){
                    // On execute les commandes
                    moteur.update();
                    std::cout << "Nombre de creatures dans la reserve du joueur 1 : " << moteur.getPlayer(1)->getCreaturesLeft() << std::endl;
                    std::cout << "Nombre de creatures dans la case de l'IA apres utilisation du jet-pack : " << moteur.getState().getCharacters()->get(ligneArr,colonneArr)->getCreaturesNbr() << std::endl;
                    std::cout << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==4)){
                    cout << "FIN TESTS SpecialCommand SKY" << endl;
                    std::cout << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==5)){
                    window.close();
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
    
    void TestsSpecialCommandCANDY()
    {
        cout << "DEBUT TESTS SpecialCommand CANDY" << endl;
        
        srand(time(NULL));
        
        // On initialise un moteur
        // On choisit les cuisiniers pour le joueur 1
        engine::Engine moteur(CreaturesID::COOKERS);
        
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        // On crée un Layer qui permettra de gerer l'affichage des cellules
        CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
        
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
        
        std::cout << "Joueur 1 de l'état : " << moteur.getPlayer(1).get() << std::endl;
        
        int iter = 0;
        
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                
                if (event.type == sf::Event::Closed) window.close();
                else if((event.type == sf::Event::EventType::KeyReleased) && (iter==0)){
                    // On attribue trois cellules speciales au joueur 1
                    std::vector<std::string> speCells;
                    speCells.push_back("sky");
                    speCells.push_back("barbecue");
                    speCells.push_back("candy");
                    moteur.getPlayer(1)->setSpeCellsNames(speCells);
                    moteur.getPlayer(1)->setCreaturesLeft(2);
                    std::cout << "Nombre de creatures dans la reserve du joueur 1 avant utilisation sucreries : " << moteur.getPlayer(1)->getCreaturesLeft() << std::endl;

                    std::cout << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==1)){
                    // On ajoute une commande au moteur
                    // Test de la capacite speciale liee au jet-pack
                    moteur.addCommand(1,new SpecialCellCommand(0,0,0,0,1,"candy"));
                    // On execute les commandes
                    moteur.update();
                    std::cout << "Nombre de creatures dans la reserve du joueur 1 apres utilisation sucreries : " << moteur.getPlayer(1)->getCreaturesLeft() << std::endl;

                    std::cout << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==2)){
                    cout << "FIN TESTS SpecialCommand CANDY" << endl;
                    std::cout << std::endl;
                    iter++;
                }else if((event.type == sf::Event::EventType::KeyReleased) && (iter==3)){
                    window.close();
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
    
    void TestsPlaceCommand()
    {
        
    }
}
