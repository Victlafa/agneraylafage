/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestsRender.cpp
 * Author: pahtatorr
 * 
 * Created on 22 octobre 2017, 11:28
 */

#include <iostream>
#include "TestsRender.h"
#include "state.h"
#include "render.h"

namespace render
{
    void TestsStateLayer()
    {
//        std::cout << "DEBUT TESTS STATELAYER" << std::endl << std::endl;
//
//        std::unique_ptr<StateLayer> stLayer(new StateLayer(new state::State()));
//
//        std::cout << "Test StateLayer - Init StateLayer : ";
//        std::cout << ((NULL != stLayer) ? "OK" : "KO") << std::endl;
//        
//        std::cout << "Test StateLayer - Getter/Setter surface : ";
//        stLayer//.setSurface(new Surface());
//        std::cout << ((NULL != stLayer.getSurface()) ? "OK" : "KO") << std::endl;
//        
//        std::cout << "Test StateLayer - Init state : ";
//        std::cout << ((NULL != stLayer.state) ? "OK" : "KO") << std::endl;
    }
    
    void TestsElementTabLayer()
    {
        std::cout << "DEBUT TESTS ELEMENTTABLAYER" << std::endl << std::endl;
        
        std::shared_ptr<state::ElementTab> grid;
        grid = std::shared_ptr<state::ElementTab>(new state::ElementTab(7, 5));
        ElementTabLayer *gridLayer = new ElementTabLayer(grid,0);
        gridLayer->initSurface();
        sf::RenderWindow window(sf::VideoMode(1024,720),"Affichage d'une ligne d'hexagones :)");
        
        while(window.isOpen())
        {
            sf::Event event;
            while(window.pollEvent(event)){
                if(event.type==sf::Event::Closed) window.close();
            }
            window.clear();
            gridLayer->getSurface()->draw(window,&gridLayer->getSurface()->getTexture());
            window.display();
        }


//        std::cout << "Test ElementTabLayer - Init ElementTabLayer : ";
//        std::cout << ((NULL != gridLayer) ? "OK" : "KO") << std::endl;
//
//        std::cout << "Test ElementTabLayer - Getter/Setter surface : ";
//        gridLayer->setSurface(new Surface());
//        std::cout << ((NULL != gridLayer->getSurface()) ? "OK" : "KO") << std::endl;
//        
//        
    }
    
    // Affichage souhaite
    void TestAffichage()
    {
        
        sf::RenderWindow window(sf::VideoMode(1024,720),"Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        while (window.isOpen())
        {
            sf::Event event;
            while(window.pollEvent(event)){
                if(event.type==sf::Event::Closed) window.close();
            }

            window.clear();

            sf::Texture hexaTexture;

            if (!hexaTexture.loadFromFile("../res/hexa.png"))
                std::cout << "Erreur chargement texture !\n" << std::endl;
                //throw std::runtime_error("Impossible de lire le fichier");

            int halfHeight = 61;
            int halfWidth = 51;
            int x = 311;
            int y = 187;
            int xText = 71;
            int yText = 81;

            std::vector<sf::VertexArray> listHexagones = std::vector<sf::VertexArray>();
            listHexagones.reserve(5);

            for (int i = 0; i < 5; i++)
            {
                listHexagones.push_back(sf::VertexArray(sf::Quads,4));
                listHexagones[i][0].position = sf::Vector2f(40 + i*2*halfWidth, 120);
                listHexagones[i][1].position = sf::Vector2f(100 + i*2*halfWidth, 120);
                listHexagones[i][2].position = sf::Vector2f(40 + i*2*halfWidth, 60);
                listHexagones[i][3].position = sf::Vector2f(100 + i*2*halfWidth, 60);

                listHexagones[i][0].texCoords = sf::Vector2f(40, yText + halfHeight);
                listHexagones[i][1].texCoords = sf::Vector2f(120, yText + halfHeight);
                listHexagones[i][2].texCoords = sf::Vector2f(40, yText - halfHeight);
                listHexagones[i][3].texCoords = sf::Vector2f(120, yText - halfHeight);
                /*
                listHexagones[i][0].position = sf::Vector2f(x - halfWidth + i*2*halfWidth, y + halfHeight);
                listHexagones[i][1].position = sf::Vector2f(x + halfWidth + i*2*halfWidth, y + halfHeight);
                listHexagones[i][2].position = sf::Vector2f(x - halfWidth + i*2*halfWidth, y - halfHeight);
                listHexagones[i][3].position = sf::Vector2f(x + halfWidth + i*2*halfWidth, y - halfHeight);

                listHexagones[i][0].texCoords = sf::Vector2f(xText - halfWidth, yText + halfHeight);
                listHexagones[i][1].texCoords = sf::Vector2f(xText + halfWidth, yText + halfHeight);
                listHexagones[i][2].texCoords = sf::Vector2f(xText - halfWidth, yText - halfHeight);
                listHexagones[i][3].texCoords = sf::Vector2f(xText + halfWidth, yText - halfHeight);
*/
            }
            
            for (int i = 0; i < 5; i++){
                
                window.draw(listHexagones[i],&hexaTexture);
            }
            sf::VertexArray tab_v(sf::Quads, 4);

            tab_v[0].position = sf::Vector2f(600,400);
            tab_v[1].position = sf::Vector2f(600,300);
            tab_v[2].position = sf::Vector2f(500,300);
            tab_v[3].position = sf::Vector2f(500,400);
            
            tab_v[0].color = sf::Color::Red;
            tab_v[1].color = sf::Color::Blue;
            tab_v[2].color = sf::Color::Green;
            
            tab_v[0].texCoords = sf::Vector2f(xText - halfWidth, yText + halfHeight);
            tab_v[1].texCoords = sf::Vector2f(xText + halfWidth, yText + halfHeight);
            tab_v[2].texCoords = sf::Vector2f(xText - halfWidth, yText - halfHeight);
            tab_v[3].texCoords = sf::Vector2f(xText + halfWidth, yText - halfHeight);

            window.draw(tab_v,&hexaTexture);
            window.display();
        }
    }
    
    // Brouillon
    void TestAffichage2()
    {
         //On créé les six sommets de l'hexagone. Pour cela on doit préciser 
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
            if(!text.loadFromFile("./res/hexa.png")) 
                std::cout<< " erreur chargement text1"<<std::endl;

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

            sf::CircleShape hexagone(120,6);
            hexagone.setTexture(&text,false);

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
                //window.draw(hexagone);
                window.draw(message);
                window.display();
            }
    }
    
    // Brouillon
    void TestAffichage3()
    {
        sf::VertexArray hexagon = sf::VertexArray(sf::Quads,4);
        sf::VertexArray hexagon2 = sf::VertexArray(sf::Quads,4);
        
        sf::Vertex p1(sf::Vector2f(200,200), sf::Color(255,255,255,255), sf::Vector2f(20,20));
        sf::Vertex p2(sf::Vector2f(302,200), sf::Color(255,255,255,255), sf::Vector2f(122,20));
        sf::Vertex p3(sf::Vector2f(200,322), sf::Color(255,255,255,255), sf::Vector2f(20,142));
        sf::Vertex p4(sf::Vector2f(302,322), sf::Color(255,255,255,255), sf::Vector2f(122,142));
        
        sf::Vertex p5(sf::Vector2f(302,200), sf::Vector2f(140,20));
        sf::Vertex p6(sf::Vector2f(404,200), sf::Vector2f(242,20));
        sf::Vertex p7(sf::Vector2f(302,322), sf::Vector2f(140,142));
        sf::Vertex p8(sf::Vector2f(404,322), sf::Vector2f(242,142));

        hexagon[0] = p1;
        hexagon[1] = p2;
        hexagon[2] = p3;
        hexagon[3] = p4;
        hexagon2[0] = p5;
        hexagon2[1] = p6;
        hexagon2[2] = p7;
        hexagon2[3] = p8;

        // On paramètre la fenêtre qui sera affichée en sortie :
        sf::RenderWindow window(sf::VideoMode(1024,720),"Affichage d'un hexagone :)");

        // Initialisation de la texture de notre hexagone :
        sf::Texture text;
        if(!text.loadFromFile("./res/hexa.png")) 
            std::cout<< " erreur chargement text1"<<std::endl;

        sf::Font myFont;
        if (!myFont.loadFromFile("./res/HPS_Extrabold_trial.ttf"))
            std::cout << "Erreur chargement police\n" << std::endl;

        sf::Text message("Bonjour !",myFont,80.f);
        message.setStyle(sf::Text::Bold);
        message.setColor(sf::Color::White);
        message.setPosition(300,300);
        
//        sf::CircleShape hexagone(122,6);
//        hexagone.setTexture(&text,false);

        while(window.isOpen()){
            sf::Event event;
            while(window.pollEvent(event)){
                if(event.type==sf::Event::Closed) window.close();
            }
            window.clear();
            window.draw(hexagon,&text);
            window.draw(hexagon2,&text);
            //window.draw(hexagone);
            window.draw(message);
            window.display();
        }
    
    }
    
}