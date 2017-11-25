#include "TestsRender.h"

namespace render {

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

        // On déclare et initialise un tableau d'éléments :
        std::shared_ptr<state::ElementTab> grid;
        grid.reset(new state::ElementTab(state::TypeID::CELL,7, 5));
        grid.get()->init();
        
        // On initialise un plan pour ce tableau, de type Cell:
        ElementTabLayer gridLayer(*grid.get(), 0);
        // Initialisation de sa surface :
        gridLayer.initSurface();
        // Initialisation de la fenêtre :
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Affichage d'une ligne d'hexagones :)");

        // Paramétrage de l'affichage :
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }
            window.clear();
            gridLayer.getSurface()->draw(window, &gridLayer.getSurface()->getTexture());
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
            //sf::Texture creaTexture;

            //Le premier cas marche chez Victoire, le second chez Aurore
            if (!hexaTexture.loadFromFile("../res/hexa.png"))
                hexaTexture.loadFromFile("./res/hexa.png");
            //else
              //  std::cout << "Erreur chargement texture !\n" << std::endl;
            //throw std::runtime_error("Impossible de lire le fichier");
           // if (!creaTexture.loadFromFile("../res/groupes.png"))
             //   std::cout << "Erreur chargement texture !\n" << std::endl;
            
            
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
        ElementTabLayer cellLayer(*(etat.getGrid().get()),0);
        //const std::shared_ptr<render::TileSet> cellTileSet = new CellTileSet();
        //cellLayer.setTileset(cellTileSet);
        
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        ElementTabLayer charsLayer(*(etat.getCharacters().get()),1);
        //const std::shared_ptr<render::TileSet> charsTileSet = new CharsTileSet();
        //charsLayer.setTileset(charsTileSet);
        
        // On initialise les surfaces de ces deux Layers
        cellLayer.initSurface();
        charsLayer.initSurface();
        
        // On cree des surfaces temporaires qu'on introduira ensuite dans les Layers
        Surface *surfCell = new Surface();
        Surface *surfChars = new Surface();
        
        //int halfHeight = 61;
        int halfWidth = 51;
        int x = 311;
        int y = 187;
        int xTextCell = 71;
        int yTextCell = 81;
        int xTextChars = 71;
        int yTextChars = 81;
        int shift = 0;
        
        // Listes temporaires qui permettront d'initialiser les Surface
        std::vector<sf::VertexArray> quadsListCell;
        quadsListCell.reserve(29);
        std::vector<sf::VertexArray> quadsListChars;
        quadsListChars.reserve(29);
        
        std::vector<int> listXTextCell = std::vector<int>();
        listXTextCell.reserve(29);
        std::vector<int> listYTextCell = std::vector<int>();
        listYTextCell.reserve(29);
        
        std::vector<int> listXTextChars = std::vector<int>();
        listXTextChars.reserve(29);
        std::vector<int> listYTextChars = std::vector<int>();
        listYTextChars.reserve(29);
        
        // On recupere les coordonnees des textures cellules dans l'image de texture associee
        // selon les types de cellules presents dans le tableau de cellules
        for(unsigned int i=0; i<etat.getGrid()->getHeight(); i++){

            for(unsigned int j=0; j<etat.getGrid()->getWidth(); j++){

                if(NULL!=etat.getGrid()->get(i,j)){

                    switch(etat.getGrid()->get(i,j)->getElemType()){
                        case state::ID::SAND :
                            listXTextCell.push_back(71);
                            listYTextCell.push_back(81);
                            break;
                        case state::ID::GRASS :
                            listXTextCell.push_back(191);
                            listYTextCell.push_back(81);
                            break;
                        case state::ID::DIRT :
                            listXTextCell.push_back(311);
                            listYTextCell.push_back(81);
                            break;   
                        case state::ID::BARBECUE :
                            listXTextCell.push_back(71);
                            listYTextCell.push_back(221);
                            break;
                        case state::ID::SKY :
                            listXTextCell.push_back(191);
                            listYTextCell.push_back(221);
                            break;
                        case state::ID::POOL :
                            listXTextCell.push_back(311);
                            listYTextCell.push_back(221);
                            break;
                        case state::ID::CANDY :
                            listXTextCell.push_back(431);
                            listYTextCell.push_back(221);
                            break;
                        default :
                            std::cout << "erreur définition coordonnées textures" << std::endl;
                            break;
                    }
                }
            }
        }
        
        // On recupere les coordonnees des textures creatures dans l'image de texture associee
        // selon les types de creatures presents dans le tableau de creatures
        for(unsigned int i=0; i<etat.getCharacters()->getHeight(); i++){

            for(unsigned int j=0; j<etat.getCharacters()->getWidth(); j++){

                // S'il y a un groupe de creatures dans la case etudiee
                if(NULL!=etat.getCharacters()->get(i,j)){
                    
                    // On recupere les coordonnees de la texture en fonction de son type et du nombre de creatures
                    switch(etat.getCharacters()->get(i,j)->getElemType()){
                        case state::ID::BLACKSMITH :
                            listXTextChars.push_back(50*(2*(etat.getCharacters()->get(i,j)->getCreaturesNbr())-1));
                            listYTextChars.push_back(50);
                            break;
                        case state::ID::COOKER :
                            listXTextChars.push_back(50*(2*(etat.getCharacters()->get(i,j)->getCreaturesNbr())-1));
                            listYTextChars.push_back(150);
                            break;
                        case state::ID::LUMBERJACK :
                            listXTextChars.push_back(50*(2*(etat.getCharacters()->get(i,j)->getCreaturesNbr())-1));
                            listYTextChars.push_back(250);
                            break;
                        case state::ID::MINER :
                            listXTextChars.push_back(50*(2*(etat.getCharacters()->get(i,j)->getCreaturesNbr())-1));
                            listYTextChars.push_back(350);
                            break;
                        default :
                            //std::cout << "elemType : " << etat.getCharacters()->get(i,j)->getElemType() << std::endl;
                            std::cout << "erreur définition coordonnées textures" << std::endl;
                            break;
                    }
                    
                }
                else
                {
                    //std::cout << "chars null en (" << i << "," << j << ")" << std::endl;
                    listXTextChars.push_back(50);
                    listYTextChars.push_back(350);
                }
                
                //std::cout << "(" << i << "," << j << ")" << std::endl;
                
            }
        }
        
        // Coordonnées du tableau correspondant à la coordonnée i de la liste
        // Initialisees sur la premiere case de la grille AFFICHEE
        int xi=0, yi=2;
             
        for (int i = 0; i < 29; i++) 
        {
            // Recuperation de la liste de quads de la surface cellules
            quadsListCell = surfCell->getQuadsList();
            // Recuperation de la liste de quads de la surface creatures
            quadsListChars = surfChars->getQuadsList();
        
            // On ajoute un quad à la liste des quads de cellules
            quadsListCell.push_back(sf::VertexArray(sf::Quads, 4));
            surfCell->setQuadsList(quadsListCell);
            
            //if(listXTextChars[i]!=-1){
            
            // On ajoute un quad à la liste des quads de creatures
            quadsListChars.push_back(sf::VertexArray(sf::Quads, 4));
            surfChars->setQuadsList(quadsListChars);
                //std::cout << "i : " << i << " not null" << std::endl;
            //}
            
            // On se deplace dans la grille selon les indices i et j - modif des coords x,y,xi,yi
            if (i == 5 || i == 11) {
                x -= halfWidth;
                y += 86;
                xi++;
                 
                switch (i) {
                    case 5:
                        yi++;
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
                xi++;//yi++;
                
                switch (i) {
                    case 18:
                        shift = i - 18;
                        break;
                    case 24:
                        yi=0;
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

            
//            xTextCell = listXTextCell[i];
//            yTextCell = listYTextCell[i];
//            
//            xTextChars = listXTextChars[i];
//            yTextChars = listYTextChars[i];
            
            // On initialise un Tile pour la cellule en i_eme position 
            Tile cellTile(listXTextCell[i], listYTextCell[i]);
            // On initialise un Tile pour le groupe de creatures en i_eme position 
            Tile charsTile(listXTextChars[i], listYTextChars[i]);
            
            //std::cout << "xtextcell : " << xTextCell << " ytextcell : " << yTextCell << std::endl;
            //std::cout << "xtextchars : " << xTextChars << " ytextchars : " << yTextChars << std::endl;
            //std::cout << "i : " << i << " xi : " << xi << " yi : " << yi << std::endl;
            
            // S'il y a une cellule en position i du tableau de cellules
            if(etat.getGrid()->get(xi,yi)!=NULL){
                //quadsListCell = surfCell->getQuadsList();
                //std::cout << "size quadslist : " << quadsListCell.size() << std::endl;
                //quadsListCell.reserve(quadsListCell.size()+4);
                //std::cout << "size quadslist : " << quadsListCell.size() << std::endl;
                //surfCell->setQuadsList(quadsListCell);
                //std::cout << "size quadslist : " << surfCell->getQuadsList().size() << std::endl;
                //std::cout << "xtextcell 2 : " << ( (cellLayer.getTileset()).get() )->getTile( etat.getGrid()->get(xi,yi) ).getX() << " ytextcell 2 : " << ( (cellLayer.getTileset()).get() )->getTile( etat.getGrid()->get(xi,yi) ).getY() << std::endl;
                
                // On fixe la position de la cellule dans l'affichage final
                surfCell->setFinalLocation(i, shift, x, y, cellTile);
                // On fixe la position du sprite dans l'image texture de base
                surfCell->setTextureLocation(i, cellTile);

                //surfCell->setFinalLocation(i, xTextCell, yTextCell, ( (cellLayer.getTileset()).get() )->getTile( etat.getGrid()->get(xi,yi) ));
                //surfCell->setTextureLocation(i, ( (cellLayer.getTileset()).get() )->getTile( etat.getGrid()->get(xi,yi) ));
            }
            
            // S'il y a une cellule en position i du tableau de creatures
            if(etat.getCharacters()->get(xi,yi)!=NULL){
                //quadsListChars = surfChars->getQuadsList();
                //quadsListChars.reserve(quadsListChars.size()+4);
                //surfChars->setQuadsList(quadsListChars);
                
                // On fixe la position du groupe de creatures dans l'affichage final
                surfChars->setFinalLocation(i, shift, x, y, charsTile);
                // On fixe la position du sprite dans l'image texture de base
                surfChars->setTextureLocation(i, charsTile);
                
                //surfChars->setFinalLocation(i, shift, xTextChars, yTextChars, ( (charsLayer.getTileset()).get() )->getTile( etat.getCharacters()->get(xi,yi) ));
                //surfChars->setTextureLocation(i, ( (charsLayer.getTileset()).get() )->getTile( etat.getCharacters()->get(xi,yi) ));
            }/*else{
                Tile nullTile = charsLayer.getTileset()->getTile;
                surfChars->setFinalLocation(i, shift, x, y, nullTile);
                surfChars->setTextureLocation(i, nullTile);
            }*/
            
            shift += 1;
            //std::cout << "xi et yi : " << xi << " " << yi << std::endl;
            yi = (yi+1)%7;

        }
        
        
        // Declaration et chargement des textures à exploiter pour l'affichage
        sf::Texture hexaTexture;
        sf::Texture charsTexture;
        
        // Le premier cas marche chez Victoire, le second chez Aurore
        if (!hexaTexture.loadFromFile("../res/hexa.png")) 
            hexaTexture.loadFromFile("./res/hexa.png");
        else
            std::cout << "Erreur chargement texture hexa !\n" << std::endl;
        
        if (!charsTexture.loadFromFile("../res/groupes.png")) 
            charsTexture.loadFromFile("./res/groupes.png");
        else
            std::cout << "Erreur chargement texture groupes !\n" << std::endl;
        
        // On associe les textures chargees aux Surfaces des Layers de cellules et de groupes de creatures
        surfCell->setTexture(hexaTexture);
        surfChars->setTexture(charsTexture);
        
        //surf->setQuadsList(listHexagones);
        //surf->setTexture(hexaTexture);
        
        // On associe les Surfaces aux Layers
        cellLayer.setSurface(surfCell);
        charsLayer.setSurface(surfChars);
        
        //std::cout << "Nombre de quads crees dans la surface de CellLayer : " << cellLayer.getSurface()->getQuadsList().size() << std::endl;
                
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }

            window.clear();
            surfCell->draw(window, &hexaTexture);
            surfChars->draw(window, &charsTexture);

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