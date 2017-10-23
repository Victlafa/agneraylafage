#include <SFML/Graphics.hpp>
#include "CellDraw.h"

namespace render{
    
    //à refaire
    CellDraw::CellDraw(int number){
        
        sf::Vertex p1(sf::Vector2f(170,120), sf::Vector2f(70,21));
        sf::Vertex p2(sf::Vector2f(221,155), sf::Vector2f(121,55));
        sf::Vertex p3(sf::Vector2f(221,206), sf::Vector2f(121,106));
        sf::Vertex p4(sf::Vector2f(170,241), sf::Vector2f(70,141));
        sf::Vertex p5(sf::Vector2f(120,206), sf::Vector2f(21,106));
        sf::Vertex p6(sf::Vector2f(120,155), sf::Vector2f(21,55));
        
        // On créé quatre triangles qui vont nous permettre de former l'hexagone :
        vertexArray1(sf::Triangles, 3);
        vertexArray2(sf::Triangles, 3);
        vertexArray3(sf::Triangles, 3);
        vertexArray4(sf::Triangles, 3);
         
        // On paramètre la fenêtre qui sera affichée en sortie :
        sf::RenderWindow window(sf::VideoMode(1024,720),"Affichage d'un hexagone :)");

        // Initialisation de la texture de notre hexagone :
        sf::Texture text;
        if(!text.loadFromFile("./res/hexa.png")) cout<< " erreur chargement text1"<<endl;
        //sf::RenderStates etat1;
        //etat1.texture = &text1;
            
        // On associe les triangles aux sommets de l'hexagone :
        vertexArray1[0]=p1;vertexArray1[1]=p2;vertexArray1[2]=p6;
        vertexArray2[0]=p2;vertexArray2[1]=p3;vertexArray2[2]=p5;
        vertexArray3[0]=p2;vertexArray3[1]=p5;vertexArray3[2]=p6;
        vertexArray4[0]=p3;vertexArray4[1]=p4;vertexArray4[2]=p5;

            
        while(window.isOpen()){
            sf::Event event;
            while(window.pollEvent(event)){
                if(event.type==sf::Event::Closed) window.close();
            }
            window.clear();
            window.draw(vertexArray1,&text);
            window.draw(vertexArray2,&text);
            window.draw(vertexArray3,&text);
            window.draw(vertexArray4,&text);
            window.display();
        }

    }
}