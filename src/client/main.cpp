#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Utf.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"
#include "render.h"
#include "TestsState.h"
#include "TestsRender.h"

using namespace std;
using namespace state;
using namespace render;

int main(int argc,char* argv[]) 
{
    // argc correspond au nombre de mots entres en arguments lors de l'execution incremente de 1.
    // argv est un tableau de mots dont le premier mot entre par l'utilisateur est l'element d'indice 1.
    // le tout premier element de argv est le chemin où se trouve le fichier à executer
    
    try {
        
        //TestsPlayer();
        
        if (argc >= 2 && (string) argv[1] == "hello")
            cout << "Bonjour tout le monde !" << endl;

        if (argc >= 2 && (string) argv[1] == "state") {

            TestsElementTab();
            TestsCreaturesGroup();
            TestsCell();
            TestsSimpleCell();
            TestsSpecialCell();
            TestsPlayer();
            TestsState();

        }
        
        if (argc >= 2 && (string) argv[1] == "render") {

            // On cherche à afficher une ligne de cinq hexagones :
            //TestInitMap();
            //TestsElementTabLayer();
            //state::Element el;
            state::ElementTab tabCell(state::TypeID::CELL, 7, 5);
            TestAffichage(tabCell);
            

        }
        
    } catch (const std::exception &e) {
        
        cout << "Erreur, catch du main" << endl;
        std::cerr << e.what();
    }
            

    return 0;
}


