#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"
#include "Tests.h"

using namespace std;
using namespace state;

int main(int argc,char* argv[]) 
{
    // argc correspond au nombre de mots entres en arguments lors de l'execution incremente de 1.
    // argv est un tableau de mots dont le premier mot entre par l'utilisateur est l'element d'indice 1.
    // le tout premier element de argv est le chemin où se trouve le fichier à executer

    //cout << "It works !" << endl;
<<<<<<< HEAD
    //TestsPlayer();
=======
>>>>>>> 167213987c1264037932effe24d62f7aed584e75
    
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
            //TestsPlayer();
            TestsState();

        }
        
        if (argc >= 2 && (string) argv[1] == "render") {

            sf::Vertex p1(sf::Vector2f(170,120), sf::Color::White, sf::Vector2f(70,21));
            sf::Vertex p2(sf::Vector2f(221,155), sf::Color::White, sf::Vector2f(121,55));
            sf::Vertex p3(sf::Vector2f(221,206), sf::Color::White, sf::Vector2f(121,106));
            sf::Vertex p4(sf::Vector2f(170,241), sf::Color::White, sf::Vector2f(70,141));
            sf::Vertex p5(sf::Vector2f(120,206), sf::Color::White, sf::Vector2f(21,106));
            sf::Vertex p6(sf::Vector2f(120,155), sf::Color::White, sf::Vector2f(21,55));
            
            sf::Vertex pt1(sf::Vector2f(70,20), sf::Color::Green, sf::Vector2f(70,20));
            sf::Vertex pt2(sf::Vector2f(20,55), sf::Color::Green, sf::Vector2f(20,55));
            sf::Vertex pt3(sf::Vector2f(70,55), sf::Color::Green, sf::Vector2f(70,55));
            
            sf::VertexArray t1(sf::Triangles, 3);
            //sf::VertexArray tt1(sf::Triangles, 4);
            sf::VertexArray t2(sf::Triangles, 3);
            sf::VertexArray t3(sf::Triangles, 3);
            sf::VertexArray t4(sf::Triangles, 3);
            sf::RenderWindow window(sf::VideoMode(1024,720),"Test Vertex");

            sf::Texture text1;
            if(!text1.loadFromFile("./res/hexa.png")) cout<< " erreur chargement text1"<<endl;
            sf::Texture text2;
            if(!text2.loadFromFile("./res/hexa.png")) cout<< " erreur chargement text2"<<endl;
            sf::Texture text3;
            if(!text3.loadFromFile("./res/hexa.png")) cout<< " erreur chargement text3"<<endl;
            sf::Texture text4;
            if(!text4.loadFromFile("./res/hexa.png")) cout<< " erreur chargement text4"<<endl;
            //sf::RenderStates etat1;
            //etat1.texture = &text1;
            
            t1[0]=p1;t1[1]=p2;t1[2]=p6;
            //tt1[0]=pt1;tt1[1]=pt2;tt1[2]=pt3;
            t2[0]=p2;t2[1]=p3;t2[2]=p5;
            t3[0]=p2;t3[1]=p5;t3[2]=p6;
            t4[0]=p3;t4[1]=p4;t4[2]=p5;

            
            while(window.isOpen()){
                sf::Event event;
                while(window.pollEvent(event)){
                    if(event.type==sf::Event::Closed) window.close();
                }
                window.clear();
                window.draw(t1,&text1);
                window.draw(t2,&text2);
                window.draw(t3,&text3);
                window.draw(t4,&text4);
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


