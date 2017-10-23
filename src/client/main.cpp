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
#include "TestsState.h"

using namespace std;
using namespace state;

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

            // On cherche à afficher un seul hexagone.
            
            // On créé les six sommets de l'hexagone. Pour cela on doit préciser 
            // leurs coordonnées dans l'image de sortie et leurs coordonnées dans 
            // le fichier source de la texture.
            sf::Vertex p1(sf::Vector2f(170,120), sf::Vector2f(70,21));
            sf::Vertex p2(sf::Vector2f(221,155), sf::Vector2f(121,55));
            sf::Vertex p3(sf::Vector2f(221,206), sf::Vector2f(121,106));
            sf::Vertex p4(sf::Vector2f(170,241), sf::Vector2f(70,141));
            sf::Vertex p5(sf::Vector2f(120,206), sf::Vector2f(21,106));
            sf::Vertex p6(sf::Vector2f(120,155), sf::Vector2f(21,55));
            
            // On créé quatre triangles qui vont nous permettre de former l'hexagone :
            sf::VertexArray t1(sf::Triangles, 3);
            sf::VertexArray t2(sf::Triangles, 3);
            sf::VertexArray t3(sf::Triangles, 3);
            sf::VertexArray t4(sf::Triangles, 3);
            
            // On paramètre la fenêtre qui sera affichée en sortie :
            sf::RenderWindow window(sf::VideoMode(1024,720),"Affichage d'un hexagone :)");

            // Initialisation de la texture de notre hexagone :
            sf::Texture text;
            if(!text.loadFromFile("./res/hexa.png")) cout<< " erreur chargement text1"<<endl;
            //sf::RenderStates etat1;
            //etat1.texture = &text1;
            
            // On associe les triangles aux sommets de l'hexagone :
            t1[0]=p1;t1[1]=p2;t1[2]=p6;
            t2[0]=p2;t2[1]=p3;t2[2]=p5;
            t3[0]=p2;t3[1]=p5;t3[2]=p6;
            t4[0]=p3;t4[1]=p4;t4[2]=p5;

            sf::Font myFont;
            if (!myFont.loadFromFile("./res/HPS_Extrabold_trial.ttf"))
                std::cout << "Erreur chargement police\n" << std::endl;
            
            sf::Text message("Bonjour !",myFont,80.f);
            message.setStyle(sf::Text::Bold);
            message.setColor(sf::Color::White);
            message.setPosition(300,300);
            
            while(window.isOpen()){
                sf::Event event;
                while(window.pollEvent(event)){
                    if(event.type==sf::Event::Closed) window.close();
                }
                window.clear();
                window.draw(t1,&text);
                window.draw(t2,&text);
                window.draw(t3,&text);
                window.draw(t4,&text);
                window.draw(message);
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


