/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestsPlayRecord.cpp
 * Author: pahtatorr
 * 
 * Created on 18 décembre 2017, 16:12
 */

#include "TestsPlayRecord.h"

void TestPlayConsole() {
    
    cout << "XXXXXXXXXXXXXXXX      REPLAY D'UNE PARTIE      XXXXXXXXXXXXXXXX\n" << endl;

    srand(2);

    // On initialise un moteur, on choisit les mineurs pour le joueur 1
    engine::Engine moteur(state::CreaturesID::MINERS, state::CreaturesID::COOKERS);
    // On recupere le placement initial des creatures presentes sur la grille
    moteur.getState().initCreaturesFromRecord();

    Json::Reader reader;
    Json::Value fichier;
    std::ifstream file("./src/replay.txt", std::ifstream::in);

    if (!reader.parse(file, fichier))
        throw std::runtime_error("Erreur lors de la recuperation des donnees contenues dans replay.txt");

    // Pour chaque tour on recupere les donnees des commandes
    for (int tour = 0; tour < 10; tour++) {
        std::cout << "\n--------------    Tour n°" << tour / 2 + 1 << ", c'est à l'IA n°" << tour % 2 + 1 << " de jouer    --------------" << std::endl << std::endl;
        Json::Value donneesCommandes = fichier[tour + 1];

        cout << "Taille de la liste donneesCommande : " << donneesCommandes.size() << endl;

        // Pour chaque commande du tour on recupere ses parametres et on l'execute
        for (unsigned int j = 0; j < donneesCommandes.size(); j++) {
            if (j == 0)
                std::cout << "\n-------------------------------- PHASE DE CONQUETE --------------------------------" << std::endl << std::endl;
            else if (j == 3)
                std::cout << "\n-------------------------------- PHASE DE RENFORT --------------------------------" << std::endl << std::endl;
            Json::Value commande = fichier[tour + 1][j];
            //cout << "Type de commande executee : " << commande.get("type","").asString() << endl;
            Command* comm = Command::deserialize(commande);
            comm->execute(moteur.getPileAction(), moteur.getState());
        }
    }
}

void TestPlayWindow() {
    
    cout << "XXXXXXXXXXXXXXXX      REPLAY D'UNE PARTIE      XXXXXXXXXXXXXXXX\n" << endl;

    // Declaration de la fenetre
    sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions");
    
    srand(2);

    // On initialise un moteur, on choisit les mineurs pour le joueur 1
    engine::Engine moteur(state::CreaturesID::MINERS, state::CreaturesID::COOKERS);
    // On recupere le placement initial des creatures presentes sur la grille
    moteur.getState().initCreaturesFromRecord();
    
    // On crée un Layer qui permettra de gerer l'affichage des cellules
    render::CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
    // On crée un Layer qui permettra de gerer l'affichage des creatures
    render::CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));  

    Json::Reader reader;
    Json::Value fichier;
    std::ifstream file("./src/replay.txt", std::ifstream::in);

    if (!reader.parse(file, fichier))
        throw std::runtime_error("Erreur lors de la recuperation des donnees contenues dans replay.txt");
    
    int tour = 0;
    int j = 0;
    
    while (tour < 20 && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) window.close();
            else if (event.type == sf::Event::EventType::KeyReleased) {

                //std::cout << "\n--------------    Tour n°" << tour / 2 + 1 << ", c'est à l'IA n°" << tour % 2 + 1 << " de jouer    --------------" << std::endl << std::endl;
                Json::Value donneesCommandes = fichier[tour + 1];
                //cout << "Taille de la liste donneesCommande : " << donneesCommandes.size() << endl;
                
                if (j == 0)
                    std::cout << "\n-------------------------------- PHASE DE CONQUETE --------------------------------" << std::endl << std::endl;
                else if (j == 3)
                    std::cout << "\n-------------------------------- PHASE DE RENFORT --------------------------------" << std::endl << std::endl;
                Json::Value commande = fichier[tour + 1][j];
                //cout << "Type de commande executee : " << commande.get("type","").asString() << endl;
                Command* comm = Command::deserialize(commande);
                comm->execute(moteur.getPileAction(), moteur.getState());
                tour++;
            }

            
        }
    }

    cellLayer.initSurface();
    charsLayer.initSurface();

    window.clear();
    cellLayer.getSurface()->draw(window);
    charsLayer.getSurface()->draw(window);

    window.display();
}
