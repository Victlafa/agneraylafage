#include "State.h"
#include "Player.h"
#include "ElementTab.h"
#include "Cell.h"
#include "CreaturesGroup.h"
#include <iostream>
#include <time.h>

namespace state
{

    State::State(CreaturesID typePl1){
        totalCellNbr = 29;
        grid.reset(new ElementTab(TypeID::CELL));
        characters.reset(new ElementTab(TypeID::CREATURESGROUP));
        player1.reset(new Player(typePl1));
        
        // Pour l'IA on tire au sort un type de creatures
        int typePl2 = rand()%4 + 1;
        player2.reset(new Player((CreaturesID)typePl2));
        
        // On initialise le tableau de creatures de sorte à associer 3 groupes de 2 creatures à chaque joueur
        this->initCreatures();
    }
    
    State::~State (){}
    
    // Setters and Getters
    const std::unique_ptr<ElementTab>& State::getGrid() const{
        return grid;
    }
    
    const std::unique_ptr<ElementTab>& State::getCharacters () const{
        return characters;
    }
    
    int State::getCellNbr () const{
        return totalCellNbr;
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
        grid.reset(new ElementTab(TypeID::CELL));
        characters.reset(new ElementTab(TypeID::CREATURESGROUP));
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
                verifJ1 = characters->verifUnicite(intRand,rand_i,rand_j);
                verifCaseJ1 = characters->verifValiditeCase(rand_i,rand_j);
                
            } while ((!verifJ1) || (!verifCaseJ1));
            
            intRand[4*j] = rand_i;
            intRand[4*j + 1] = rand_j;
            
            do {
                
                rand_i_J2 = rand() % characters->getHeight();
                rand_j_J2 = rand() % characters->getWidth();
                // On verifie la validite des coordonnees : ont-elles deja été tirees ? Correspondent-elles à des cases interdites ?
                verifJ2 = characters->verifUnicite(intRand,rand_i_J2, rand_j_J2);
                verifCaseJ2 = characters->verifValiditeCase(rand_i_J2, rand_j_J2);
                
            } while ((!verifJ2) || (!verifCaseJ2));

            intRand[4*j + 2] = rand_i_J2;
            intRand[4*j + 3] = rand_j_J2;

            characters->set(new CreaturesGroup((ID)(player1->getClanName()), 2, player1.get()), rand_i, rand_j);
            // On regarde si le groupe a ete place sur une cellule speciale ou pas
            if (grid->isSpecial(rand_i,rand_j))
                // Si c'est le cas, on signale que le joueur detient cette cellule speciale
                grid->assignSpecialCell(player1.get(),nullptr,(ID)player1->getClanName());
            
            std::cout << "State.cpp : Coordonnees joueur 1 : " << "(" << intRand[4*j] << "," << intRand[4*j+1] << ") " << std::endl;
            std::cout << "State.cpp : verif type : " << characters->get(rand_i,rand_j)->getElemType() << std::endl;
            
            characters->set(new CreaturesGroup((ID)(player2->getClanName()), 2, player2.get()), rand_i_J2, rand_j_J2);
            // On regarde si le groupe a ete place sur une cellule speciale ou pas
            if (grid->isSpecial(rand_i_J2,rand_j_J2))
                // Si c'est le cas, on signale que le joueur detient cette cellule speciale
                grid->assignSpecialCell(player2.get(),nullptr,(ID)player2->getClanName());
            
            std::cout << "State.cpp : Coordonnees joueur 2 : " << "(" << intRand[4*j+2] << "," << intRand[4*j+3] << ")" << std::endl;
            std::cout << "State.cpp : verif type : " << characters->get(rand_i_J2,rand_j_J2)->getElemType() << std::endl;
            
        }
    }
   
    
};