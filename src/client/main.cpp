#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"

using namespace std;
using namespace state;

int main(int argc,char* argv[]) 
{
    // argc correspond au nombre de mots entres en arguments lors de l'execution incremente de 1.
    // argv est un tableau de mots dont le premier mot entre par l'utilisateur est l'element d'indice 1.
    // le tout premier element de argv est le chemin où se trouve le fichier à executer

    cout << "It works !" << endl;
    
    if (argc >= 2 && (string)argv[1] == "hello")
        cout << "Bonjour tout le monde !" << endl;
		
    if (argc >= 2 && (string)argv[1] == "state"){
        cout << "Création du joueur 1" << endl;
        Player* p1 = new Player();
        if(NULL!=p1){
            cout <<    "Joueur 1 a bien été créé" << endl;
        }
    }

    return 0;
}

