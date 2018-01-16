#include "TestsRender.h"

namespace render {

    void TestsStateLayer() 
    {
        std::cout << "DEBUT TESTS STATELAYER" << std::endl << std::endl;

        // On initialise un moteur, on choisit les mineurs pour le joueur 1
        engine::Engine moteur(CreaturesID::MINERS, state::CreaturesID::COOKERS);
        // On initialise une ia
        HeuristicAI ia(&moteur, rand()%30000);
        
        // On crée un Layer qui permettra de gerer l'affichage des cellules
        CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
        StateLayer stateLayer(moteur.getState());
        // On crée un layer pour l'affichage des donnees texte de l'etat
        //StateLayer stateLayer(moteur.getState());
        //stateLayer.initSurface();
        sf::RenderWindow gameWindow(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);
        
        sf::Font myFont;
        if (!myFont.loadFromFile("./res/Brainfish_Rush.ttf"))
            std::cout << "Erreur chargement police\n" << std::endl;
        
        sf::Text message("Welcome to the garden !",myFont,50.f);
        message.setColor(sf::Color::White);
        message.setPosition(311,50);
        
        //gameWindow.draw(&background);
        
        sf::Event event;
        
        while (gameWindow.isOpen()) {
            
            while (gameWindow.pollEvent(event)) {
                // Fermeture de la fenetre ?
                if (event.type == sf::Event::Closed) gameWindow.close();
            }
            
            // On met à jour l'affichage
            cellLayer.initSurface();
            charsLayer.initSurface();
            
            gameWindow.clear();
            //gameWindow.draw(&background);
            stateLayer.getSurface()->draw(gameWindow);
            cellLayer.getSurface()->draw(gameWindow);
            charsLayer.getSurface()->draw(gameWindow);
            gameWindow.draw(message);
            
            gameWindow.display();
        }
        

    }

    void TestsElementTabLayer() 
    {
        std::cout << "DEBUT TESTS ELEMENTTABLAYER" << std::endl << std::endl;

        // On déclare et initialise un tableau d'éléments :
        std::shared_ptr<state::CellTab> grid;
        grid.reset(new state::CellTab(7, 5));
        
        // On initialise un plan pour ce tableau, de type Cell:
        CellTabLayer gridLayer(*grid.get());
        
        // Initialisation de la fenêtre :
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Affichage d'une ligne d'hexagones :)");

        // Paramétrage de l'affichage :
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }
            window.clear();
            gridLayer.getSurface()->draw(window);
            window.display();
        }    
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
        std::vector<SpecialCell> l_SpeC;
        std::vector<state::ID> l_SpeCID = {state::ID::BARBECUE, state::ID::CANDY, state::ID::POOL, state::ID::SKY};
        std::vector<int> li = {0,0,0,0};//liste des ordonnées des cellules spéciales
        std::vector<int> lj = {0,0,0,0};//liste des absisses des cellules simples
        
        int i = 0;
        int j = 0;
        
        //On détermine les coordonnées des 4 cellules spéciales
        for(int sc=0; sc<4; sc++){
            
            i = 0;
            j = 0;
               
            bool trouve = true;
                   
            // On s'assure que les coordonnées trouvées sont dans la grille voulue
            // et qu'elle ne se superpose pas à une autre cellule spéciale
            while(((i==0 && j==0) || (i==0 && j==1) || (i==1&&j==0) || (i==4&&j==6) || (i==4&&j==5) || (i==3&&j==6))||trouve){
                trouve=false;
                i = rand()%5;
                j = rand()%7;
                for(int k =0; k<4; k++){
                    if(i==li[k]&&j==lj[k]){
                        trouve=true;
                    }
                }
                
            }

            
            std::string restype = "wood";
            SpecialCell spec(l_SpeCID[sc], restype, 2, i, j);
            l_SpeC.push_back(spec);
            li[sc]=i;lj[sc]=j;
            
            //map_cell(i,j)=*spec;
            //on adapte les coordonnées de la cellule à la liste des textures
            if(i*7+j<7){
                map_cell[i*7+j-2]=spec;
                map_cell_text[i*7+j-2]=sc+3;
            }else 
                if(i*7+j<27){
                    map_cell[i*7+j-3]=spec;
                    map_cell_text[i*7+j-3]=sc+3;
            }else 
                if(i*7+j<33){
                    map_cell[i*7+j-4]=spec;
                    map_cell_text[i*7+j-4]=sc+3;
            }else 
                if(i*7+j<34){
                    map_cell[i*7+j-5]=spec;
                    map_cell_text[i*7+j-5]=sc+3;
            }else{
                map_cell[i*7+j-6]=spec;
                map_cell_text[i*7+j-6]=sc+3;
            }
            
            
            
            std::cout << "i:" << i << " j:" << j << " sc:" << sc << " i*7+j:"<< i*7+j << std::endl;
            
        }
        
        
        std::cout << "Positionnement des Cellules Simples" << std::endl;
        // On remplit map_cell avec des cellules simples
        std::vector<state::ID> l_SimCID = {state::ID::DIRT,state::ID::GRASS,state::ID::SAND};
        
        for(int i=0; i<5; i++){
            for(int j=0; j<7; j++){
                if(!((i==0&&j==0) || (i==0&&j==1) || (i==1&&j==0) || (i==4&&j==6) || (i==4&&j==5) || (i==3&&j==6) || (i==li[0]&&j==lj[0]) || (i==li[1]&&j==lj[1]) || (i==li[2]&&j==lj[2]) || (i==li[3]&&j==lj[3]))){
                    std::string restype = "wood";
                    //map_cell(i,j)= state::SimpleCell(l_SimCID[rand()%3],restype,4,i,j);
                    int iid = rand()%3;
                    state::ID id = l_SimCID[iid];
                    //on adapte les coordonnées de la cellule à la liste des textures
                    if(i*7+j<7){
                        map_cell[i*7+j-2]=SimpleCell(id,restype,4,i,j);
                        map_cell_text[i*7+j-2]=iid;
                    }else 
                        if(i*7+j<27){
                            map_cell[i*7+j-3]=state::SimpleCell(id,restype,4,i,j);
                            map_cell_text[i*7+j-3]=iid;
                    }else 
                        if(i*7+j<33){
                            map_cell[i*7+j-4]=state::SimpleCell(id,restype,4,i,j);
                            map_cell_text[i*7+j-4]=iid;
                    }else 
                        if(i*7+j<34){
                            map_cell[i*7+j-5]=state::SimpleCell(id,restype,4,i,j);
                            map_cell_text[i*7+j-5]=iid;
                    }else{
                        map_cell[i*7+j-6]=state::SimpleCell(id,restype,4,i,j);
                        map_cell_text[i*7+j-6]=iid;
                    }

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
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }

            window.clear();

            sf::Texture hexaTexture;
            //sf::Texture creaTexture;

            //Le premier cas marche chez Victoire, le second chez Aurore
            if (!hexaTexture.loadFromFile("../res/hexa.png"))
                hexaTexture.loadFromFile("./res/hexa.png");
            
            for (int i = 0; i < 29; i++){
                window.draw(listHexagones[i], &hexaTexture);
                //window.draw(listHexagonesCrea[i], &creaTexture);
            }

            window.display();
        }
        
    }
    
    // Affichage souhaite

    void TestAffichage(state::State& etat) {

        sf::RenderWindow window(sf::VideoMode(1024, 720), "Garden Tensions"); //, sf::Style::Close | sf::Style::Titlebar);

        // On crée un Layer qui permettra de gerer l'affichage des cellules
        CellTabLayer cellLayer(*(etat.getGrid().get()));
        
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        CreaturesTabLayer charsLayer(*(etat.getCharacters().get()));
        
        // Declaration et chargement des textures à exploiter pour l'affichage
        sf::Texture hexaTexture;
        sf::Texture charsTexture;
        
        // Le premier cas marche chez Victoire, le second chez Aurore
        if (!hexaTexture.loadFromFile("./res/hexa.png")) 
            hexaTexture.loadFromFile("../res/hexa.png");
        else
            std::cout << "Erreur chargement texture hexa !\n" << std::endl;
        
        if (!charsTexture.loadFromFile("./res/groupes.png")) 
            charsTexture.loadFromFile("../res/groupes.png");
        else
            std::cout << "Erreur chargement texture groupes !\n" << std::endl;
        
        // On associe les textures chargees aux Surfaces des Layers de cellules et de groupes de creatures
        cellLayer.getSurface()->setTexture(hexaTexture);
        charsLayer.getSurface()->setTexture(charsTexture);
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }

            window.clear();
            cellLayer.getSurface()->draw(window);
            charsLayer.getSurface()->draw(window);

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

}