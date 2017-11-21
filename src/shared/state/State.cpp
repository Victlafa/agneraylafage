#include "State.h"
#include "Player.h"
#include "ElementTab.h"
#include "Cell.h"
#include "CreaturesGroup.h"
#include <iostream>

namespace state
{

    State::State(){
        //std::cout << "Appel constructeur de State" << std::endl;
        totalCellNbr = 29;
        grid.reset(new ElementTab(TypeID::CELL));
        characters.reset(new ElementTab(TypeID::CREATURESGROUP));
        player1.reset(new Player());
        player2.reset(new Player());
        
        // On initialise le tableau de creatures de sorte à associer 3 groupes de 2 creatures à chaque joueur
        this->initCreatures();
    }
    
    State::~State (){ 
        //std::cout << "Appel destructeur de State" << std::endl;
    }
    
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
                
            } while (verifJ1 || !verifCaseJ1);
            
            do {
                
                rand_i_J2 = rand() % characters->getHeight();
                rand_j_J2 = rand() % characters->getWidth();
                // On verifie la validite des coordonnees : ont-elles deja été tirees ? Correspondent-elles à des cases interdites ?
                verifJ2 = characters->verifUnicite(intRand,rand_i_J2, rand_j_J2);
                verifCaseJ2 = characters->verifValiditeCase(rand_i_J2, rand_j_J2);
                
            } while (verifJ2 || !verifCaseJ2);

            intRand[4*j] = rand_i;
            intRand[4*j + 1] = rand_j;
            intRand[4*j + 2] = rand_i_J2;
            intRand[4*j + 3] = rand_j_J2;

            this->characters->set(new CreaturesGroup((ID)(this->getPlayer(1)->getClanName()), 2, this->getPlayer(1).get()), rand_i, rand_j);
            this->characters->set(new CreaturesGroup((ID)(this->getPlayer(2)->getClanName()), 2, this->getPlayer(2).get()), rand_i_J2, rand_j_J2);

        }
    }
   
    
};