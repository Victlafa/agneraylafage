/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mikhan
 *
 * Created on 14 décembre 2017, 10:26
 */

#include <iostream>
#include <fstream>

#include "../shared/state.h"
#include "../shared/engine.h"
#include "../shared/ai.h"

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;


int main(int argc, char** argv) {

    if (argc >= 2 && (string) argv[1] == "record"){
        
        cout << "XXXXXXXXXXXXXXXX      ENREGISTREMENT D'UNE PARTIE      XXXXXXXXXXXXXXXX\n" << endl;
        
        srand(2);

        // On initialise un moteur, on choisit les mineurs pour le joueur 1
        engine::Engine moteur(state::CreaturesID::MINERS);
        // On initialise une ia
        ai::HeuristicAI ia(&moteur, 2);

        std::ofstream file("./src/replay.txt", std::ios::out);
        //file.open("../replay.txt");
        if(file.bad()){
            std::cout << "Erreur avec le fichier replay.txt" << std::endl;
            return 1;
        }
        
        Json::Value jsonArray(Json::arrayValue);
        //ia.setJsonFile(jsonArray);

        Json::StyledWriter styledWriter;
        
        //On sauvegarde l'état initial du jeu
        Json::Value etatInit(Json::arrayValue);
        
        for(int i=0; i<5; i++){
            for(int j=0; j<7; j++){
                if(moteur.getState().getCharacters()->get(i,j)!=NULL){
                    Json::Value elem;
                    elem["joueur"] = moteur.getState().getCharacters()->get(i,j)->getPlayer();
                    elem["creature"] = moteur.getState().getCharacters()->get(i,j)->getElemType();
                    elem["nbrCrea"] = moteur.getState().getCharacters()->get(i,j)->getCreaturesNbr();
                    elem["i"] = i;
                    elem["j"] = j;
                    etatInit.append(elem);
                }
            }
        }
        
        jsonArray.append(etatInit);
        moteur.setRecord(jsonArray);

        int tour = 0;

        std::cout << "Ici s'affrontent deux IAs heuristiques qui peuvent pour le moment seulement se déplacer et combattre avec les quelques créatures qu'elles ont au départ de la partie. Elles peuvent aussi ajouter des creatures lors d'une phase de renfort." << std::endl;
        std::cout << "La démonstration se fera sur 20 tours." << std::endl;
        std::cout << "De plus nous avons donné la priorité aux combats. Il est donc possible que des groupes de creatures ne cherchent pas à se disperser tant qu'elles n'ont pas d'ennemies à proximité." << std::endl;
        std::cout << "(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;

        while(tour!=10){
            std::cout << "\n--------------    Tour n°" << tour/2 + 1 << ", c'est à l'IA n°" << tour%2 + 1 << " de jouer    --------------" << std::endl << std::endl;

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

            ///std::cout << styledWriter.write(ia.getJsonFile()) << std::endl;
        }

        file << styledWriter.write(ia.getMoteur()->getRecord());

        //std::cout << styledWriter.write(ia.getJsonFile()) << std::endl;

        file.close();
    }
    
    return 0;
}

