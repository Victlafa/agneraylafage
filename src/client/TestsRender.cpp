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
#include <time.h>
#include "TestsRender.h"
#include "state.h"
#include "render.h"

namespace render {

    void TestsStateLayer() {
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

    void TestsElementTabLayer() {
        std::cout << "DEBUT TESTS ELEMENTTABLAYER" << std::endl << std::endl;

        // On déclare et initialise un tableau d'éléments :
        std::shared_ptr<state::ElementTab> grid;
        grid = std::shared_ptr<state::ElementTab>(new state::ElementTab(state::TypeID::CELL,7, 5));

        // On initialise un plan pour ce tableau, de type Cell:
        ElementTabLayer *gridLayer = new ElementTabLayer(grid, 0);
        // Initialisation de sa surface :
        gridLayer->initSurface();
        // Initialisation de la fenêtre :
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Affichage d'une ligne d'hexagones :)");

        // Paramétrage de l'affichage :
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }
            window.clear();
            gridLayer->getSurface()->draw(window, &gridLayer->getSurface()->getTexture());
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

    // Initialise la map
    
    void TestInitMap()
    {
        
        std::cout << "Initialisation map_cell & map_creatures" << std::endl;
        //state::ElementTab map_cell(state::TypeID::CELL,(size_t)5,(size_t)7);
        //state::ElementTab map_creatures(state::TypeID::CREATURESGROUP,(size_t)5,(size_t)7);
        
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        srand(time(NULL));
        
        int halfHeight = 61;
        int halfWidth = 51;
        int x = 311;
        int y = 187;
        int xText = 71;
        int yText = 81;
        int shift = 0;
        
        std::map<int,state::Cell> map_cell;
        std::map<int,int> map_cell_text;

        
        std::cout << "Positionnement des Cellules Spéciales" << std::endl;
        //Positionnement des Cellules Spéciales
        std::vector<state::SpecialCell> l_SpeC;
        std::vector<state::SpecialCellID> l_SpeCID = {state::SpecialCellID::BARBECUE, state::SpecialCellID::CANDY, state::SpecialCellID::POOL, state::SpecialCellID::SKY};
        std::vector<int> li = {0,0,0,0};
        std::vector<int> lj = {0,0,0,0};
        
        int i = 0;
        int j = 0;
        
        for(int sc=0; sc<4; sc++){
            
            i = 0;
            j = 0;
               
            bool trouve = true;
                    
            while(((i==0&&j==0) || (i==0&&j==1) || (i==1&&j==0) || (i==4&&j==6) || (i==4&&j==5) || (i==3&&j==6))||trouve){
                trouve=false;
                for(int k =0; k<4; k++){
                    if(i==li[k]&&j==lj[k]){
                        trouve=true;
                    }
                }
                i = rand()%7;
                j = rand()%5;
                
            }

            
            std::string restype = "wood";
            state::SpecialCell *spec = new state::SpecialCell(l_SpeCID[sc], restype, 2, i, j);
            l_SpeC.push_back(*spec);
            li[sc]=i;lj[sc]=j;
            
            //map_cell(i,j)=*spec;
            map_cell[i*7+j]=*spec;
            map_cell_text[i*7+j]=sc+3;
            
            std::cout << i << std::endl;
            std::cout << j << std::endl;
        }
        
        
        std::cout << "Positionnement des Cellules Simples" << std::endl;
        // On remplit map_cell avec des cellules simples
        std::vector<state::SimpleCellID> l_SimCID = {state::SimpleCellID::DIRT,state::SimpleCellID::GRASS,state::SimpleCellID::SAND};
        
        for(int i=0; i<5; i++){
            for(int j=0; j<7; j++){
                if(!((i==0&&j==0) || (i==0&&j==1) || (i==1&&j==0) || (i==4&&j==6) || (i==4&&j==5) || (i==3&&j==6) || (i==li[0]&&j==lj[0]) || (i==li[1]&&j==lj[1]) || (i==li[2]&&j==lj[2]) || (i==li[3]&&j==lj[3]))){
                    std::string restype = "wood";
                    //map_cell(i,j)= state::SimpleCell(l_SimCID[rand()%3],restype,4,i,j);
                    int iid = rand()%3;
                    state::SimpleCellID id = l_SimCID[iid];
                    map_cell[i*7+j]=state::SimpleCell(id,restype,4,i,j);
                    map_cell_text[i*7+j]=iid;
                }
                //else
                    //map_cell(i,j) = NULL;
            }
        }
        

        
        std::vector<sf::VertexArray> listHexagones = std::vector<sf::VertexArray>();
        listHexagones.reserve(29);
        
        for (int i = 0; i < 29; i++) {

            listHexagones.push_back(sf::VertexArray(sf::Quads, 4));
            
            if (i == 5 || i == 11) {
                x -= halfWidth;
                y += 86;
                switch (i) {
                    case 5:
                        shift = i - 5;
                        break;
                    case 11:
                        shift = i - 11;
                        break;
                    default:
                        shift = i;
                }
            }
                
            else if (i == 18 || i == 24) {
                
                x += halfWidth;
                y += 86;
            switch (i) {
                    case 18:
                        shift = i - 18;
                        break;
                    case 24:
                        shift = i - 24;
                        break;
                    default:
                        shift = i;
                }
            }
                
            else
            {
                shift = shift;
            }

            listHexagones[i][0].position = sf::Vector2f(x + halfWidth + shift * 2 * halfWidth, y + halfHeight);
            listHexagones[i][1].position = sf::Vector2f(x + halfWidth + shift * 2 * halfWidth, y - halfHeight);
            listHexagones[i][2].position = sf::Vector2f(x - halfWidth + shift * 2 * halfWidth, y - halfHeight);
            listHexagones[i][3].position = sf::Vector2f(x - halfWidth + shift * 2 * halfWidth, y + halfHeight);

            switch(map_cell_text[i]){
                case 6 :
                    xText=71;
                    yText=221;
                    break;
                case 5 :
                    xText=191;
                    yText=221;
                    break;
                case 4 :
                    xText=311;
                    yText=221;
                    break;
                case 3 :
                    xText=431;
                    yText=221;
                    break;
                case 2 :
                    xText=311;
                    yText=81;
                    break;
                case 1 :
                    xText=191;
                    yText=81;
                    break;
                case 0 :
                    xText=71;
                    yText=81;
                    break;
                default:
                    xText=71;
                    yText=81;
                    break;
            }
            
            
            listHexagones[i][0].texCoords = sf::Vector2f(xText + halfWidth, yText + halfHeight);
            listHexagones[i][1].texCoords = sf::Vector2f(xText + halfWidth, yText - halfHeight);
            listHexagones[i][2].texCoords = sf::Vector2f(xText - halfWidth, yText - halfHeight);
            listHexagones[i][3].texCoords = sf::Vector2f(xText - halfWidth, yText + halfHeight);

            shift += 1;

        }
        
        
        /*
        std::cout << "Initialisation map_creature" << std::endl;
        //On initialise map_creature
        
        std::map<int,state::CreaturesGroup> map_creature;
        std::map<int,int> map_creature_text;
        
        std::vector<int> li1 = {0,0,0};
        std::vector<int> li2 = {0,0,0};
        std::vector<int> lj1 = {0,0,0};
        std::vector<int> lj2 = {0,0,0};
        
        for(int cr=0; cr<3; cr++){
            int i = 0;
            int j = 0;
               
            state::CreaturesGroup crg(state::CreaturesID::BLACKSMITH);
       
            
            bool trouve = true;
                    
            while(((i==0&&j==0) || (i==0&&j==1) || (i==1&&j==0) || (i==4&&j==6) || (i==4&&j==5) || (i==3&&j==6) || (i==li[0]&&j==lj[0]) || (i==li[1]&&j==lj[1]) || (i==li[2]&&j==lj[2]) || (i==li[3]&&j==lj[3]))||trouve){
                i=rand()%5;
                j=rand()%7;
                trouve=false;
                for(int k=0; k<3; k++){
                    if((i==li1[k]&&j==lj1[k])&&(i==li2[k]&&j==lj2[k]))
                        trouve=true;
                }
            }
            
            li1[cr]=i;
            lj1[cr]=j;
            //map_creatures(i,j)=crg;
            map_creature[i*7+j]= crg;
            map_creature_text[i*7+j]=1;
            //crg.toPlace(i,j);
                
        }
        
        for(int cr=0; cr<3; cr++){
            int i = 0;
            int j = 0;
               
            state::CreaturesGroup crg(state::CreaturesID::COOKER); 
            
            bool trouve = true;
                    
            while(((i==0&&j==0) || (i==0&&j==1) || (i==1&&j==0) || (i==4&&j==6) || (i==4&&j==5) || (i==3&&j==6) || (i==li[0]&&j==lj[0]) || (i==li[1]&&j==lj[1]) || (i==li[2]&&j==lj[2]) || (i==li[3]&&j==lj[3]))||trouve){
                i=rand()%5;
                j=rand()%7;
                trouve=false;
                for(int k=0; k<3; k++){
                    if((i==li1[k]&&j==lj1[k])&&(i==li2[k]&&j==lj2[k]))
                        trouve=true;
                }
            }
            
            li2[cr]=i;
            lj2[cr]=j;
            //map_creatures(i,j)=crg;
            map_creature[i*7+j]=crg;
            map_creature_text[i*7+j]=2;
            crg.toPlace(i,j);
                
        }
        
        
        
        std::vector<sf::VertexArray> listHexagonesCrea = std::vector<sf::VertexArray>();
        listHexagonesCrea.reserve(29);
        
        for (int i = 0; i < 29; i++) {

            listHexagonesCrea.push_back(sf::VertexArray(sf::Quads, 4));
            
            if (i == 5 || i == 11) {
                x -= halfWidth;
                y += 86;
                switch (i) {
                    case 5:
                        shift = i - 5;
                        break;
                    case 11:
                        shift = i - 11;
                        break;
                    default:
                        shift = i;
                }
            }
                
            else if (i == 18 || i == 24) {
                
                x += halfWidth;
                y += 86;
            switch (i) {
                    case 18:
                        shift = i - 18;
                        break;
                    case 24:
                        shift = i - 24;
                        break;
                    default:
                        shift = i;
                }
            }
                
            else
            {
                shift = shift;
            }

            listHexagonesCrea[i][0].position = sf::Vector2f(x + halfWidth + shift * 2 * halfWidth, y + halfHeight);
            listHexagonesCrea[i][1].position = sf::Vector2f(x + halfWidth + shift * 2 * halfWidth, y - halfHeight);
            listHexagonesCrea[i][2].position = sf::Vector2f(x - halfWidth + shift * 2 * halfWidth, y - halfHeight);
            listHexagonesCrea[i][3].position = sf::Vector2f(x - halfWidth + shift * 2 * halfWidth, y + halfHeight);

            switch(map_creature_text[i]){
                case 2 :
                    xText=100;
                    yText=100;
                    break;
                case 1 :
                    xText=100;
                    yText=200;
                    break;
                default:
                    xText=100;
                    yText=300;
                    break;
        }
            
            
            listHexagonesCrea[i][0].texCoords = sf::Vector2f(xText + halfWidth, yText + halfHeight);
            listHexagonesCrea[i][1].texCoords = sf::Vector2f(xText + halfWidth, yText - halfHeight);
            listHexagonesCrea[i][2].texCoords = sf::Vector2f(xText - halfWidth, yText - halfHeight);
            listHexagonesCrea[i][3].texCoords = sf::Vector2f(xText - halfWidth, yText + halfHeight);

            shift += 1;

        }*/
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }

            window.clear();

            sf::Texture hexaTexture;
            sf::Texture creaTexture;

            //Le premier cas marche chez Victoire, le second chez Aurore
            if (!hexaTexture.loadFromFile("../res/hexa.png"))
                std::cout << "Erreur chargement texture !\n" << std::endl;
            //throw std::runtime_error("Impossible de lire le fichier");
            if (!creaTexture.loadFromFile("../res/groupes.png"))
                std::cout << "Erreur chargement texture !\n" << std::endl;
            
            
            for (int i = 0; i < 29; i++){
                window.draw(listHexagones[i], &hexaTexture);
                //window.draw(listHexagonesCrea[i], &creaTexture);
            }

            window.display();
        }
        
    }
    
    // Affichage souhaite

    void TestAffichage() {

        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        int halfHeight = 61;
        int halfWidth = 51;
        int x = 311;
        int y = 187;
        int xText = 71;
        int yText = 81;
        int shift = 0;
        
        std::vector<sf::VertexArray> listHexagones = std::vector<sf::VertexArray>();
        listHexagones.reserve(29);
        
        for (int i = 0; i < 29; i++) {

            listHexagones.push_back(sf::VertexArray(sf::Quads, 4));
            
            if (i == 5 || i == 11) {
                x -= halfWidth;
                y += 86;
                switch (i) {
                    case 5:
                        shift = i - 5;
                        break;
                    case 11:
                        shift = i - 11;
                        break;
                    default:
                        shift = i;
                }
            }
                
            else if (i == 18 || i == 24) {
                
                x += halfWidth;
                y += 86;
            switch (i) {
                    case 18:
                        shift = i - 18;
                        break;
                    case 24:
                        shift = i - 24;
                        break;
                    default:
                        shift = i;
                }
            }
                
            else
            {
                shift = shift;
            }

            listHexagones[i][0].position = sf::Vector2f(x + halfWidth + shift * 2 * halfWidth, y + halfHeight);
            listHexagones[i][1].position = sf::Vector2f(x + halfWidth + shift * 2 * halfWidth, y - halfHeight);
            listHexagones[i][2].position = sf::Vector2f(x - halfWidth + shift * 2 * halfWidth, y - halfHeight);
            listHexagones[i][3].position = sf::Vector2f(x - halfWidth + shift * 2 * halfWidth, y + halfHeight);

            listHexagones[i][0].texCoords = sf::Vector2f(xText + halfWidth, yText + halfHeight);
            listHexagones[i][1].texCoords = sf::Vector2f(xText + halfWidth, yText - halfHeight);
            listHexagones[i][2].texCoords = sf::Vector2f(xText - halfWidth, yText - halfHeight);
            listHexagones[i][3].texCoords = sf::Vector2f(xText - halfWidth, yText + halfHeight);

            shift += 1;

        }
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }

            window.clear();

            sf::Texture hexaTexture;

            //Le premier cas marche chez Victoire, le second chez Aurore
            if (!hexaTexture.loadFromFile("../res/hexa.png"))
                std::cout << "Erreur chargement texture !\n" << std::endl;
            //throw std::runtime_error("Impossible de lire le fichier");
          
            
            for (int i = 0; i < 29; i++)
                window.draw(listHexagones[i], &hexaTexture);

            window.display();
        }
    }

    // Brouillon

    void TestAffichage2() {
        //On créé les six sommets de l'hexagone. Pour cela on doit préciser 
        // leurs coordonnées dans l'image de sortie et leurs coordonnées dans 
        // le fichier source de la texture.
        sf::Vertex p1(sf::Vector2f(170, 120), sf::Vector2f(70, 21));
        sf::Vertex p2(sf::Vector2f(221, 155), sf::Vector2f(121, 55));
        sf::Vertex p3(sf::Vector2f(221, 206), sf::Vector2f(121, 106));
        sf::Vertex p4(sf::Vector2f(170, 241), sf::Vector2f(70, 141));
        sf::Vertex p5(sf::Vector2f(120, 206), sf::Vector2f(21, 106));
        sf::Vertex p6(sf::Vector2f(120, 155), sf::Vector2f(21, 55));

        // On créé quatre triangles qui vont nous permettre de former l'hexagone :
        sf::VertexArray t1(sf::Triangles, 3);
        sf::VertexArray t2(sf::Triangles, 3);
        sf::VertexArray t3(sf::Triangles, 3);
        sf::VertexArray t4(sf::Triangles, 3);

        // On paramètre la fenêtre qui sera affichée en sortie :
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Affichage d'un hexagone :)");

        // Initialisation de la texture de notre hexagone :
        sf::Texture text;
        if (!text.loadFromFile("./res/hexa.png"))
            std::cout << " erreur chargement text1" << std::endl;

        // On associe les triangles aux sommets de l'hexagone :
        t1[0] = p1;
        t1[1] = p2;
        t1[2] = p6;
        t2[0] = p2;
        t2[1] = p3;
        t2[2] = p5;
        t3[0] = p2;
        t3[1] = p5;
        t3[2] = p6;
        t4[0] = p3;
        t4[1] = p4;
        t4[2] = p5;

        sf::Font myFont;
        if (!myFont.loadFromFile("./res/HPS_Extrabold_trial.ttf"))
            std::cout << "Erreur chargement police\n" << std::endl;

        sf::Text message("Bonjour !", myFont, 80.f);
        message.setStyle(sf::Text::Bold);
        message.setColor(sf::Color::White);
        message.setPosition(300, 300);

        sf::CircleShape hexagone(120, 6);
        hexagone.setTexture(&text, false);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }
            window.clear();
            window.draw(t1, &text);
            window.draw(t2, &text);
            window.draw(t3, &text);
            window.draw(t4, &text);
            //window.draw(hexagone);
            window.draw(message);
            window.display();
        }
    }

    // Brouillon

    void TestAffichage3() {
        sf::VertexArray hexagon = sf::VertexArray(sf::Quads, 4);
        sf::VertexArray hexagon2 = sf::VertexArray(sf::Quads, 4);

        sf::Vertex p1(sf::Vector2f(200, 200), sf::Color(255, 255, 255, 255), sf::Vector2f(20, 20));
        sf::Vertex p2(sf::Vector2f(302, 200), sf::Color(255, 255, 255, 255), sf::Vector2f(122, 20));
        sf::Vertex p3(sf::Vector2f(200, 322), sf::Color(255, 255, 255, 255), sf::Vector2f(20, 142));
        sf::Vertex p4(sf::Vector2f(302, 322), sf::Color(255, 255, 255, 255), sf::Vector2f(122, 142));

        sf::Vertex p5(sf::Vector2f(302, 200), sf::Vector2f(140, 20));
        sf::Vertex p6(sf::Vector2f(404, 200), sf::Vector2f(242, 20));
        sf::Vertex p7(sf::Vector2f(302, 322), sf::Vector2f(140, 142));
        sf::Vertex p8(sf::Vector2f(404, 322), sf::Vector2f(242, 142));

        hexagon[0] = p1;
        hexagon[1] = p2;
        hexagon[2] = p3;
        hexagon[3] = p4;
        hexagon2[0] = p5;
        hexagon2[1] = p6;
        hexagon2[2] = p7;
        hexagon2[3] = p8;

        // On paramètre la fenêtre qui sera affichée en sortie :
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Affichage d'un hexagone :)");

        // Initialisation de la texture de notre hexagone :
        sf::Texture text;
        if (!text.loadFromFile("./res/hexa.png"))
            std::cout << " erreur chargement text1" << std::endl;

        sf::Font myFont;
        if (!myFont.loadFromFile("./res/HPS_Extrabold_trial.ttf"))
            std::cout << "Erreur chargement police\n" << std::endl;

        sf::Text message("Bonjour !", myFont, 80.f);
        message.setStyle(sf::Text::Bold);
        message.setColor(sf::Color::White);
        message.setPosition(300, 300);

        //        sf::CircleShape hexagone(122,6);
        //        hexagone.setTexture(&text,false);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }
            window.clear();
            window.draw(hexagon, &text);
            window.draw(hexagon2, &text);
            //window.draw(hexagone);
            window.draw(message);
            window.display();
        }

    }

}