#include <iostream>
#include <fstream>


#include "../shared/state.h"
#include "render.h"
#include "../shared/engine.h"
#include "../shared/ai.h"
#include "TestsState.h"
#include "TestsRender.h"
#include "TestsEngine.h"
//#include "TestsIA.h"
#include "TestsPlayRecord.h"
#include "TestsNetwork.h"


using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace server;
using namespace ai;

int main(int argc,char* argv[]) 
{
    // argc correspond au nombre de mots entres en arguments lors de l'execution incremente de 1.
    // argv est un tableau de mots dont le premier mot entre par l'utilisateur est l'element d'indice 1.
    // le tout premier element de argv est le chemin où se trouve le fichier à executer
    
    try {
        
        if (argc >= 2 && string(argv[1]) == "hello")
            cout << "Bonjour tout le monde !" << endl;

        else if (argc >= 2 && string(argv[1]) == "state") {

            TestsElementTab();
            TestsCreaturesGroup();
            TestsCell();
            TestsSimpleCell();
            TestsSpecialCell();
            TestsPlayer();
            TestsState();

        }
        
        else if (argc >= 2 && string(argv[1]) == "render") {

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
        
        else if (argc >= 2 && string(argv[1]) == "engine") {

            srand(time(NULL));
            
            state::State *etat = new State(CreaturesID::BLACKSMITHS, state::CreaturesID::MINERS);
            
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
        
        //else if (argc >= 2 && string(argv[1]) == "random_ai") TestsRandomIA();
        
        //else if (argc >= 2 && string(argv[1]) == "heuristic_ai") TestsHeuristicIA();
        
        //else if (argc >= 2 && string(argv[1]) == "rollback") TestsRollbackMove();
        
        //else if (argc >= 2 && string(argv[1]) == "thread") TestsThread();
        
        else if (argc >= 2 && string(argv[1]) == "play") TestPlayConsole();
        
        else if (argc >= 2 && string(argv[1]) == "network") TestsNetwork();
        
    } catch (const std::exception &e) {
        
        cout << "Erreur, catch du main" << endl;
        std::cerr << e.what();
    }
            

    return 0;
}


