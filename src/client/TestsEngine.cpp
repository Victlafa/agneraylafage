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
using namespace std;

namespace engine {
    
    void TestsFightCommand(){
        
        cout << "DEBUT TESTS FIGHTCOMMAND" << endl;
        
        // On cree un moteur qui creera automatiquement un etat
        engine::Engine moteur(CreaturesID::BLACKSMITHS);
        
        int ligneCombat = 2;
        int colonne1 = 3;
        int colonne2 = 4;
        
        // On place un forgeron
        std::cout << "Creation d'un forgeron associé au joueur 1" << std::endl;
        CreaturesGroup* forgeron = new CreaturesGroup(ID::BLACKSMITH, 2, moteur.getPlayer(1).get());
        moteur.getState().getCharacters()->set(forgeron,ligneCombat,colonne1);
        // On place un cuisinie dans la case (4,3)
        std::cout << "Creation d'un cuisinier associé au joueur 2" << std::endl;
        CreaturesGroup* cuisinier = new CreaturesGroup(ID::COOKER, 2, moteur.getPlayer(2).get());
        moteur.getState().getCharacters()->set(cuisinier,ligneCombat,colonne2);
        
        // On ajoute une commande au moteur
        moteur.addCommand(1,new MoveCommand(ligneCombat,colonne1,ligneCombat,colonne2,1));
        // On execute les commandes
        moteur.update();
        // On affiche les points de conquete des deux joueurs 
        std::cout << "Conquetes joueur 1 :" << moteur.getState().getPlayer(1)->getConquestPoints() << std::endl;
        std::cout << "Conquetes joueur 2 :" << moteur.getState().getPlayer(2)->getConquestPoints() << std::endl;

        
        cout << "FIN TESTS FIGHTCOMMAND" << endl;
    }
    void TestsMoveCharCommand(){
        
        cout << "DEBUT TESTS MOVECHARCOMMAND" << endl;
        
        engine::Engine moteur(CreaturesID::BLACKSMITHS);
        
        int ligne = 2;
        int colonne = 4;
        
        // On place un forgeron en (ligne,colonne)
        std::cout << "Creation d'un forgeron associé au joueur 1" << std::endl;
        CreaturesGroup* forgeron = new CreaturesGroup(ID::BLACKSMITH, 2, moteur.getPlayer(1).get());
        moteur.getState().getCharacters()->set(forgeron,ligne,colonne);
        std::cout << "Position avant deplacement : (" << forgeron->getX() << "," << forgeron->getY() << ")\n" << std::endl;
        
        // On ajoute une commande au moteur
        // On souhaite que la creature du joueur se deplace vers la droite
        moteur.addCommand(1,new MoveCommand(ligne,colonne,ligne,colonne + 1,1));
        // On execute les commandes
        moteur.update();
        
        // On affiche les positions de la creature
        
        std::cout << "Position apres deplacement : (" << forgeron->getX() << "," << forgeron->getY() << ")\n" << std::endl;
                
        cout << "FIN TESTS MOVECHARCOMMAND" << endl;
    }
    void TestsPoisonCommand(){
        
        cout << "DEBUT TESTS POISONCOMMAND" << endl;
        
        engine::Engine moteur(CreaturesID::BLACKSMITHS);
        
        int ligne = 2;
        int colonne = 4;
        
        // On place un forgeron en (ligne,colonne)
        std::cout << "Creation d'un forgeron associé au joueur 1" << std::endl;
        CreaturesGroup* forgeron = new CreaturesGroup(ID::BLACKSMITH, 2, moteur.getPlayer(1).get());
        moteur.getState().getCharacters()->set(forgeron,ligne,colonne);
        
        // On empoisonne la case concernee
        moteur.poisonCell(true,ligne,colonne);
        
        std::cout << "Nombres de creatures presentes avant empoisonnement :" << moteur.getState().getCharacters()->get(ligne, colonne)->getCreaturesNbr() << std::endl;
        
        // Ajout d'une commande au moteur
        moteur.addCommand(1,new PoisonCommand(ligne,colonne));
        // On execute les commandes
        moteur.update();
        
        std::cout << "Nombres de creatures presentes apres empoisonnement :" << moteur.getState().getCharacters()->get(ligne, colonne)->getCreaturesNbr() << std::endl;
    
        cout << "FIN TESTS POISONCOMMAND" << endl;
    }
    void TestsNewGameCommand()
    {
        cout << "DEBUT TESTS NEWGAMECOMMAND" << endl;
        
        engine::Engine moteur(CreaturesID::BLACKSMITHS);
        std::cout << "Etat avant : " << &moteur.getState() << std::endl;
        std::cout << "Grille avant : " << moteur.getState().getGrid().get() << std::endl;
        moteur.addCommand(1,new NewGameCommand());
        moteur.update();
        std::cout << "Etat apres : " << &moteur.getState() << std::endl;
        std::cout << "Grille apres : " << moteur.getState().getGrid().get() << std::endl;
        std::cout << "Type de creatures du joueur 1 : " << moteur.getPlayer(1)->getClanName() << std::endl;
        
        cout << "FIN TESTS NEWGAMECOMMAND" << endl;
    }
    void TestsMoveCommand(){
        cout << "DEBUT TESTS MOVECHARCOMMAND" << endl;
        
        engine::Engine moteur(CreaturesID::BLACKSMITHS);
        
        std::cout << "Joueur 1 de l'état : " << moteur.getPlayer(1).get() << std::endl;
        std::cout << "Joueur 2 de l'état : " << moteur.getPlayer(2).get() << std::endl;
        
        int ligne = 2;
        int colonne = 4;
        
        // On place un forgeron en (ligne,colonne)
        std::cout << "Creation d'un forgeron associé au joueur 1" << std::endl;
        CreaturesGroup* forgeron = new CreaturesGroup(ID::BLACKSMITH, 2, moteur.getPlayer(1).get());
        std::cout << "Joueur associe au forgeron : " << forgeron->getPlayer() << std::endl;
        //moteur.getPlayer(1)->setIsStriker(true);
        moteur.getState().getCharacters()->set(forgeron,ligne,colonne);
        //std::cout << "Position avant deplacement : (" << forgeron->getX() << "," << forgeron->getY() << ")\n" << std::endl;
        std::cout << "Nbre de creatures attaquantes avant deplacement : " << forgeron->getCreaturesNbr() << std::endl;
        std::cout << "Joueur attaquant : " << forgeron->getPlayer() << std::endl;
        
        
        
        // On place un cuisinier dans la case à droite
        std::cout << "Creation d'un cuisinier associé au joueur 2" << std::endl;
        CreaturesGroup* cuisinier = new CreaturesGroup(ID::COOKER, 2, moteur.getPlayer(2).get());
        moteur.getState().getCharacters()->set(cuisinier,ligne,colonne + 1);
        std::cout << "Nbre de creatures de defense avant deplacement : " << cuisinier->getCreaturesNbr() << std::endl;
        std::cout << "Joueur defenseur : " << cuisinier->getPlayer() << std::endl;
        
        // On ajoute une commande au moteur
        // On souhaite que la creature du joueur se deplace vers la droite
        moteur.addCommand(1,new MoveCommand(ligne,colonne,ligne,colonne + 1,1));
        // On execute les commandes
        moteur.update();
        
        // On affiche les positions de la creature
        
        //std::cout << "Position apres deplacement : (" << forgeron->getX() << "," << forgeron->getY() << ")\n" << std::endl;
        std::cout << "Nbre de creatures d'attaque apres deplacement : " << forgeron->getCreaturesNbr() << std::endl;
        std::cout << "Nbre de creatures de defense apres deplacement : " << moteur.getState().getCharacters()->get(ligne, colonne +1)->getCreaturesNbr() << std::endl;
        std::cout << "Joueur present en attaque : " << moteur.getState().getCharacters()->get(ligne, colonne)->getPlayer() << std::endl;
        std::cout << "Joueur present en defense : " << moteur.getState().getCharacters()->get(ligne, colonne + 1)->getPlayer() << std::endl;
                
        std::cout << "Conquetes joueur 1 :" << moteur.getState().getPlayer(1)->getConquestPoints() << std::endl;
        std::cout << "Conquetes joueur 2 :" << moteur.getState().getPlayer(2)->getConquestPoints() << std::endl;
        
        std::cout << "Joueur 1 de l'état : " << moteur.getPlayer(1).get() << std::endl;
        std::cout << "Joueur 2 de l'état : " << moteur.getPlayer(2).get() << std::endl;

        cout << "FIN TESTS MOVECHARCOMMAND" << endl;
        
        //moteur.getPlayer(1)->setIsStriker(true);
    }
    void TestsSpecialCommand()
    {
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
        
        
        // On place un cuisinier
        std::cout << "Creation d'un cuisinier associé au joueur 1" << std::endl;
        CreaturesGroup* cuisinier = new CreaturesGroup(ID::COOKER, 2, moteur.getPlayer(1).get());
        moteur.getState().getCharacters()->set(cuisinier,ligneDep,colonneDep);
        
        // On place un adv dans la case (ligneArr,colonneArr)
        std::cout << "Creation d'un groupe associé au joueur 2" << std::endl;
        CreaturesGroup* player2Crea = new CreaturesGroup((ID)moteur.getPlayer(2)->getClanName(), 2, moteur.getPlayer(2).get());
        moteur.getState().getCharacters()->set(player2Crea,ligneArr,colonneArr);
        
        // On ajoute une commande au moteur
        
        // Test de la capacite speciale liee au barbecue ou à la piscine
        moteur.addCommand(1,new SpecialCellCommand(ligneDep,colonneDep,ligneArr,colonneArr,1,"barbecue"));
        std::cout << "Nombre de creatures dans la case de l'IA avant utilisation du barbecue : " << moteur.getState().getCharacters()->get(ligneArr,colonneArr)->getCreaturesNbr() << std::endl;

        // Test de la capacité spéciale liee au pot de sucreries
        //moteur.addCommand(2,new SpecialCellCommand(ligneDep,colonneDep,ligneArr,colonneArr,1,"candy"));
        //std::cout << "Nombre de creatures dans la reserve du joueur 1 : " << moteur.getPlayer(1)->getCreaturesLeft() << std::endl;
        // On souhaite tester la capacité speciale liee au ciel
        // On doit pour cela choisir une cellule adverse à attaquer sur la carte ainsi qu'une case de depart
        //moteur.addCommand(3,new SpecialCellCommand(ligneDep,colonneDep,ligneArr,colonneArr,1,"sky"));
        
        // On execute les commandes
        moteur.update();
        std::cout << "Nombre de creatures dans la reserve du joueur 1 : " << moteur.getPlayer(1)->getCreaturesLeft() << std::endl;
        std::cout << "Nombre de creatures dans la case de l'IA apres utilisation du barbecue : " << moteur.getState().getCharacters()->get(ligneArr,colonneArr)->getCreaturesNbr() << std::endl;

        
        
    }
}
