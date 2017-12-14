#include <iostream>
#include <fstream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Utf.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "../shared/state.h"
#include "render.h"
#include "../shared/engine.h"
#include "TestsState.h"
#include "TestsRender.h"
#include "TestsEngine.h"
#include "TestsIA.h"
#include "../shared/ai.h"

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

int main(int argc,char* argv[]) 
{
    // argc correspond au nombre de mots entres en arguments lors de l'execution incremente de 1.
    // argv est un tableau de mots dont le premier mot entre par l'utilisateur est l'element d'indice 1.
    // le tout premier element de argv est le chemin où se trouve le fichier à executer
    
    try {
        
        //TestsPlayer();
        
        if (argc >= 2 && (string) argv[1] == "hello")
            cout << "Bonjour tout le monde !" << endl;

        else if (argc >= 2 && (string) argv[1] == "state") {

            TestsElementTab();
            TestsCreaturesGroup();
            TestsCell();
            TestsSimpleCell();
            TestsSpecialCell();
            TestsPlayer();
            TestsState();

        }
        
        else if (argc >= 2 && (string) argv[1] == "render") {

            // On cherche à afficher une ligne de cinq hexagones :
            //TestInitMap();
            //TestsElementTabLayer();
            //state::Element el;

            // On associe au joueur 1 les forgerons. Les creatures de l'IA sont tirees au hasard
            //state::State *etat = new State(CreaturesID::BLACKSMITHS);
            //TestAffichage(*etat);
            
            // Test affichage de donnees d'etat dans la fenetre de jeu
            TestsStateLayer();

        }
        
        else if (argc >= 2 && (string) argv[1] == "engine") {

            srand(time(NULL));
            
            state::State *etat = new State(CreaturesID::BLACKSMITHS);
            
            sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

            CellTabLayer cellLayer(*(etat->getGrid().get()));
            CreaturesTabLayer charsLayer(*(etat->getCharacters().get()));

            // Declaration et chargement des textures à exploiter pour l'affichage
            sf::Texture hexaTexture;
            sf::Texture charsTexture;

            // Le premier cas marche chez Victoire, le second chez Aurore
            if (!hexaTexture.loadFromFile("./res/hexa.png")) hexaTexture.loadFromFile("../res/hexa.png");
            else std::cout << "Erreur chargement texture hexa !\n" << std::endl;

            if (!charsTexture.loadFromFile("./res/groupes.png")) charsTexture.loadFromFile("../res/groupes.png");
            else std::cout << "Erreur chargement texture groupes !\n" << std::endl;

            // On associe les textures chargees aux Surfaces des Layers de cellules et de groupes de creatures
            cellLayer.getSurface()->setTexture(hexaTexture);
            charsLayer.getSurface()->setTexture(charsTexture);

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) window.close();
                }

                window.clear();
                cellLayer.getSurface()->draw(window);
                charsLayer.getSurface()->draw(window);

                window.display();
            }
            
            // COMMANDES FONCTIONNELLES
            TestsPoisonCommand();
            cout << "\n" << endl;
            TestsNewGameCommand();
            cout << "\n" << endl;
            TestsMoveCommandNoOne();
            cout << "\n" << endl;
            TestsMoveCommandAdv();
            cout << "\n" << endl;
            TestsMoveCommandPlayer();
            cout << "\n" << endl;
            TestsSpecialCommandBBQ();
            cout << "\n" << endl;
            TestsSpecialCommandSKY();
            cout << "\n" << endl;
            TestsSpecialCommandCANDY();
            cout << "\n" << endl;
            
            // COMMANDES A FINIR OU A CORRIGER

            //TestsPlaceCommand();
            //cout << "\n" << endl;
            
        }
        
        else if (argc >= 2 && (string) argv[1] == "random_ai") TestsRandomIA();
        
        else if (argc >= 2 && (string) argv[1] == "heuristic_ai") TestsHeuristicIA();
        
        else if (argc >= 2 && (string) argv[1] == "rollback") TestsRollbackMove();
        
        else if (argc >= 2 && (string) argv[1] == "thread") TestsThread();
        
        else if (argc >= 2 && (string) argv[1] == "play"){
            
            
            
            Json::Value fichier;
            fichier["nom"] = "nom_fichier";
            fichier["nbr_command"] = 0;
            fichier["initPos0"] = 0;
            fichier["initPos1"] = 1;
            fichier["finalPos0"] = 14;
            fichier["finalPos1"] = 8;

            Json::StyledWriter styledWriter;
            std::cout << styledWriter.write(fichier) << std::endl;
        }
        
        else if (argc >= 2 && (string) argv[1] == "record"){
            //json reader 
            //ifstream
            srand(time(NULL));

            // On initialise un moteur, on choisit les mineurs pour le joueur 1
            engine::Engine moteur(state::CreaturesID::MINERS);
            // On initialise une ia
            ai::HeuristicAI ia(&moteur, rand()%30000);
            
            std::ofstream file("replay.txt", std::ifstream::in);
            //file.open("replay.txt");
            
            Json::Value jsonArray(Json::arrayValue);
            ia.setJsonFile(jsonArray);
            
            Json::StyledWriter styledWriter;

            int tour = 0;

            std::cout << "Ici s'affrontent deux IAs heuristiques qui peuvent pour le moment seulement se déplacer et combattre avec les quelques créatures qu'elles ont au départ de la partie. Elles peuvent aussi ajouter des creatures lors d'une phase de renfort." << std::endl;
            std::cout << "La démonstration se fera sur 20 tours." << std::endl;
            std::cout << "De plus nous avons donné la priorité aux combats. Il est donc possible que des groupes de creatures ne cherchent pas à se disperser tant qu'elles n'ont pas d'ennemies à proximité." << std::endl;
            std::cout << "(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;

            while(tour!=10){
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
                
                //std::cout << "\n(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;


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

            file << styledWriter.write(ia.getJsonFile());
            
            //std::cout << styledWriter.write(ia.getJsonFile()) << std::endl;
            
            file.close();
        }
        
    } catch (const std::exception &e) {
        
        cout << "Erreur, catch du main" << endl;
        std::cerr << e.what();
    }
            

    return 0;
}


