#include "State.h"
#include "Player.h"
#include "ElementTab.h"
#include "Cell.h"
#include "CreaturesGroup.h"
#include <iostream>
#include <time.h>
#include <json/json.h>
#include <fstream>

using namespace std;

namespace state
{

    State::State(CreaturesID typePl1, CreaturesID typePl2){
        totalCellNbr = 29;
        grid.reset(new CellTab(7,5));
        characters.reset(new CreaturesTab(7,5));
        player1.reset(new Player(typePl1));
        
        //CreaturesID tirage = typePl1;
        
        // On tire au sort un type de creature qu'on associe à l'IA (on s'arrange pour qu'il soit different de celui du joueur) :
        //while (tirage == typePl1)
        //    tirage = (CreaturesID)(rand()%4 + 1);
        
        //player2.reset(new Player((CreaturesID)tirage));
        player2.reset(new Player(typePl2));
        
        // On initialise le tableau de creatures de sorte à associer 3 groupes de 2 creatures à chaque joueur
        this->initCreatures();
        
        //std::ifstream file("replay.txt", std::ifstream::in);
        
    }
    
    State::~State (){}
    
    // Setters and Getters
    const std::unique_ptr<CellTab>& State::getGrid() const{
        return grid;
    }
    
    const std::unique_ptr<CreaturesTab>& State::getCharacters () const{
        return characters;
    }
    
    int State::getCellNbr () const{
        return totalCellNbr;
    }
    
    int State::getFreeCellNbr() const
    {
        return totalCellNbr - player1->getCellNbr() - player2->getCellNbr();
    }
    
    const std::unique_ptr<Player>& State::getPlayer(int number) const{
        if (number == 1)
            return player1;
        else if (number == 2)
            return player2;
        else
            return NULL;
    }
    
    void State::reset(CreaturesID typeCreatures)
    {
        grid.reset(new CellTab(7,5));
        characters.reset(new CreaturesTab(7,5));
        player1.reset(new Player(typeCreatures));
        int creaEnnemi = rand()%4 + 1;
        player2.reset(new Player((CreaturesID)creaEnnemi));
        
    }
    
    void State::initCreatures ()
    {
        // On fera en sorte en début de partie que chaque joueur dispose de trois groupes de 2 creatures disposées sur la carte
        
        // Cette liste permettra de stocker temporairement les coordonnees deja tirees
        std::vector<int> intRand(12);
        
        for(int k=0; k<12; k++) { intRand[k]=0; }
                
        // Coordonnees pour creatures du joueur 1
        int rand_i, rand_j;
        // Pour celles du joueur 2
        int rand_i_J2, rand_j_J2;
        
        bool verifJ1;
        bool verifJ2;
        bool verifCaseJ1;
        bool verifCaseJ2;

        // On va tirer au sort des coordonnees pour placer 6 groupes de creatures (3 pour chaque joueur)
        
        for (int j = 0; j < 3; j++) {
            
            // On fait les tirages des deux joueurs 
            do {
                rand_i = rand() % characters->getHeight();
                rand_j = rand() % characters->getWidth();
                // On verifie la validite des coordonnees : ont-elles deja été tirees ? Correspondent-elles à des cases interdites ?
                verifJ1 = characters->isUnique(intRand,rand_i,rand_j);
                verifCaseJ1 = characters->isEnable(rand_i,rand_j);
                
            } while ((!verifJ1) || (!verifCaseJ1));
            
            intRand[4*j] = rand_i;
            intRand[4*j + 1] = rand_j;
            
            do {
                
                rand_i_J2 = rand() % characters->getHeight();
                rand_j_J2 = rand() % characters->getWidth();
                // On verifie la validite des coordonnees : ont-elles deja été tirees ? Correspondent-elles à des cases interdites ?
                verifJ2 = characters->isUnique(intRand,rand_i_J2, rand_j_J2);
                verifCaseJ2 = characters->isEnable(rand_i_J2, rand_j_J2);
                
            } while ((!verifJ2) || (!verifCaseJ2));

            intRand[4*j + 2] = rand_i_J2;
            intRand[4*j + 3] = rand_j_J2;

            characters->set(new CreaturesGroup((ID)(player1->getClanName()), 3, player1.get()), rand_i, rand_j);
            //std::cout << "State::initCreatures - appel isSpecial ligne 111" << std::endl;
            // On regarde si le groupe a ete place sur une cellule speciale ou pas
            if (grid->isSpecial(rand_i,rand_j))
                // Si c'est le cas, on signale que le joueur detient cette cellule speciale
                grid->assignSpecialCell(player1.get(),nullptr,grid->get(rand_i,rand_j)->getElemType());
            
//            std::cout << "State.cpp : Coordonnees joueur 1 : " << "(" << intRand[4*j] << "," << intRand[4*j+1] << ") " << std::endl;
//            std::cout << "State.cpp : verif type : " << characters->get(rand_i,rand_j)->getElemType() << std::endl;
            
            characters->set(new CreaturesGroup((ID)(player2->getClanName()), 3, player2.get()), rand_i_J2, rand_j_J2);
            //std::cout << "State::initCreatures - appel isSpecial ligne 120" << std::endl;
            // On regarde si le groupe a ete place sur une cellule speciale ou pas
            if (grid->isSpecial(rand_i_J2,rand_j_J2))
                // Si c'est le cas, on signale que le joueur detient cette cellule speciale
                grid->assignSpecialCell(player2.get(),nullptr,grid->get(rand_i_J2,rand_j_J2)->getElemType());
            
//            std::cout << "State.cpp : Coordonnees joueur 2 : " << "(" << intRand[4*j+2] << "," << intRand[4*j+3] << ")" << std::endl;
//            std::cout << "State.cpp : verif type : " << characters->get(rand_i_J2,rand_j_J2)->getElemType() << std::endl;
            
        }
    }
   
    void State::initCreaturesFromRecord ()
    {
        Json::Reader reader;
        Json::Value fichier;
        std::ifstream file("./src/replay.txt", std::ifstream::in);
        
        if (!reader.parse(file,fichier))
                throw std::runtime_error("State::initCreaturesFromRecord - Erreur lors de la recuperation des donnees contenues dans replay.txt");
        
        // On vide la liste de creatures de l'état actuel
        if (this->characters->clearList() != true)
            throw std::runtime_error("State::initCreaturesFromRecord - la liste n'a pas ete vidée correctement !");
        
        // On recupere dans l'enregistrement les groupes de creatures et on les place dans la liste  --------------" << std::endl << std::endl;
        Json::Value etatInitial = fichier[0];

        //cout << "State::initCreaturesFromRecord - Taille de la liste etatInitial : " << etatInitial.size() << endl;

        // Pour chaque groupe on recupere ses donnees
        for (unsigned int j = 0; j < etatInitial.size(); j++)
        {
            //cout << "State::initCreaturesFromRecord - entree dans boucle for" << endl;
            Json::Value creasGroup = fichier[0][j];
            int player = creasGroup.get("joueur",0).asInt();
            int id = creasGroup.get("creature",0).asInt();
            int nbCreas = creasGroup.get("nbrCrea",0).asInt();
            int x = creasGroup.get("i",-1).asInt();
            int y = creasGroup.get("j",-1).asInt();
            Player* playerPtr = this->getPlayer(player).get();
            //cout << "State::initCreaturesFromRecord - recup etat d'une cellule" << endl;
            // On cree un nouveau groupe
            CreaturesGroup* group = new CreaturesGroup((ID)id,nbCreas,playerPtr);
            //cout << "State::initCreaturesFromRecord - crea nouveau groupe" << endl;
            // On l'ajoute à la grille
            this->characters->set(group,x,y);
            //cout << "State::initCreaturesFromRecord - ajout à la grille" << endl;
        }
    }
};