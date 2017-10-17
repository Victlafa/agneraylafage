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

            sf::Vertex p1(sf::Vector2f(20,0), sf::Color::Green, sf::Vector2f(20,0));
            sf::Vertex p2(sf::Vector2f(0,20), sf::Color::Green, sf::Vector2f(0,20));
            sf::Vertex p3(sf::Vector2f(20,40), sf::Color::Green, sf::Vector2f(20,40));
            sf::Vertex p4(sf::Vector2f(40,40), sf::Color::Green, sf::Vector2f(40,40));
            sf::Vertex p5(sf::Vector2f(60,20), sf::Color::Green, sf::Vector2f(60,20));
            sf::Vertex p6(sf::Vector2f(40,0), sf::Color::Green, sf::Vector2f(40,0));
            
            
            sf::VertexArray t1(sf::Triangles, 3);
            sf::VertexArray t2(sf::Triangles, 3);
            sf::VertexArray t3(sf::Triangles, 3);
            sf::VertexArray t4(sf::Triangles, 3);
            sf::RenderWindow window(sf::VideoMode(512,256),"Test Vertex");

            sf::Texture text1;
            if(!text1.loadFromFile("hexa.pgn",sf::IntRect(20,20,101,121))) cout<< " erreur chargement text1"<<endl;
            sf::Texture text2;
            if(!text2.loadFromFile("hexa.pgn",sf::IntRect(20,20,101,121))) cout<< " erreur chargement text2"<<endl;
            sf::Texture text3;
            if(!text3.loadFromFile("hexa.pgn",sf::IntRect(20,20,101,121))) cout<< " erreur chargement text3"<<endl;
            sf::Texture text4;
            if(!text4.loadFromFile("hexa.pgn",sf::IntRect(20,20,101,121))) cout<< " erreur chargement text4"<<endl;
            //sf::RenderStates etat1;
            //etat1.texture = &text1;
            
            t1[0]=p1;t1[1]=p2;t1[2]=p3;
            t2[0]=p1;t2[1]=p3;t2[2]=p4;
            t3[0]=p1;t3[1]=p4;t3[2]=p6;
            t4[0]=p4;t4[1]=p5;t4[2]=p6;
            
            while(window.isOpen()){
                sf::Event event;
                while(window.pollEvent(event)){
                if(event.type==sf::Event::Closed) window.close();
                }
                window.clear();
                window.draw(t1,&text1);
                window.draw(t2,&text1);
                window.draw(t3,&text1);
                window.draw(t4,&text1);
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


