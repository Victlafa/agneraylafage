#include <iostream>

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

using namespace std;
using namespace state;
using namespace render;
using namespace engine;


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

            state::State *etat = new State();
            //state::ElementTab tabCell(state::TypeID::CELL, 7, 5)
            //state::ElementTab grid;
            //grid = etat.getGrid();
            TestAffichage(*etat);

        }
        
        else if (argc >= 2 && (string) argv[1] == "engine") {

            srand(time(NULL));
            
            //TestsFightCommand();
            //TestsMoveCharCommand();
            //TestsPoisonCommand();
            //TestsNewGameCommand();
            TestsMoveCommand();
        }
        
        else if (argc >= 2 && (string) argv[1] == "random_ai") {
            
            //state::State *etat = new State();
            //state::ElementTab char = etat->getCharacters();
            /*while(){
                
            }*/
        
        }
        
    } catch (const std::exception &e) {
        
        cout << "Erreur, catch du main" << endl;
        std::cerr << e.what();
    }
            

    return 0;
}


