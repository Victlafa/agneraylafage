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
            //TestsElementTabLayer();
            
            sf::RenderWindow window(sf::VideoMode(1024,720,32),"Garden Tensions", sf::Style::Close | sf::Style::Titlebar);
            sf::Texture hexagonesTexture;
            
            if (!hexagonesTexture.loadFromFile("res/hexa.png"))
                throw std::runtime_error("Impossible de lire le fichier");
            
            int halfHeight = 61;
            int halfWidth = 51;
            int x = 300;
            int y = 300;
            
            std::vector<sf::VertexArray> listHexagones(5);
            
            for (int i = 0; i < 5; i++)
            {
                // création du VertexArray en quad
                sf::VertexArray hexagon(sf::Quads,4);
                
                // définition des coordonnées des 4 points du quad
                // ie position de l'hexagone dans la fenêtre
                
                hexagon[0].position = sf::Vector2f(x - halfWidth, y + halfHeight);
                hexagon[1].position = sf::Vector2f(x + halfWidth, y + halfHeight);
                hexagon[2].position = sf::Vector2f(x - halfWidth, y - halfHeight);
                hexagon[3].position = sf::Vector2f(x + halfWidth, y - halfHeight);
                
                // définition de la partie de la texture correspondante
                hexagon[0].texCoords = sf::Vector2f(x - halfWidth, y + halfHeight);
                hexagon[1].texCoords = sf::Vector2f(x + halfWidth, y + halfHeight);
                hexagon[2].texCoords = sf::Vector2f(x - halfWidth, y - halfHeight);
                hexagon[3].texCoords = sf::Vector2f(x + halfWidth, y - halfHeight);
                
                listHexagones.push_back(hexagon);
            }
            
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    // fermeture de la fenêtre lorsque l'utilisateur le souhaite
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                    }
                }
                
                window.clear();
                for (int i = 0; i < 5; i++)
                    window.draw(listHexagones[i],&hexagonesTexture);
            
                window.display();
            }
            

        }
        
    } catch (...) {
        int pouet = 5;
        cout << "erreur";
        cout << pouet << endl;
    }
            

    return 0;
}


