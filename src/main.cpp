#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"
#include <iostream>

using namespace std;
using namespace state;

int main(int argc,char* argv[]) 
{
    //Exemple exemple;
    //exemple.setX(53);

    cout << "It works !" << endl;
    
    Player joueur = new Player();
    std::cout << joueur->speCellsName << std::endl;

    return 0;
}
