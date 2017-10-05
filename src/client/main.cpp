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
    
    if (argc >= 2 && (string)argv[1] == "hello")
        cout << "Bonjour tout le monde !" << endl;
		
    if (argc >= 2 && (string)argv[1] == "state"){
        
        /*cout << "Création de l'état du jeu ";
        State* gameState = new State();
        if(NULL!=gameState){
            cout << "OK" << endl;
        }else{
            cout << "KO" << endl;
        }
        
        cout << "Nombre de cellules ";
        int nbrCell = gameState->getCellNbr();
        if(49==nbrCell){
            cout << "OK" << endl;
        }else{
            cout << "KO" << endl;
        }*/
        
        TestPlayer();
        
        /*
        cout << "Test Player CreaturesId ";
        p1->setClanName(CreaturesID.BLACKSMITH);
        if(CreaturesID.BLACKSMITH==p1->getClanName()){
            cout << "OK" << endl;
        }else{
            cout << "KO" << endl;
        }*/
        TestsElementTab();
 
    }

    return 0;
}

namespace state
{
void TestsElementTab()
{
    cout << "Création d'un tableau d'elements : ";
    ElementTab* elemTab = new ElementTab(3,4);
    if (NULL == elemTab)
        cout << "KO" << std::endl;
    else
        cout << "OK" << std::endl;
    
    cout << "Test getters de hauteur et largeur du tableau : ";
    if (elemTab->getHeight()==4 && elemTab->getWidth()==3)
        cout << "OK" << std::endl;
    else
        cout << "KO" << std::endl;
    
    cout << "Test resize du tableau : ";
    elemTab->resize(6,8);
    if (elemTab->getHeight()==8 && elemTab->getWidth()==6)
        cout << "OK" << std::endl;
    else
        cout << "KO"<< std::endl;
    
    //cout << "Test setter/getter Element du tableau : " << std::endl;
    //std::unique_ptr<Element> elemTest = std::unique_ptr<Element>();
    //elemTab->set(*elemTest, 1, 1);
    //if (elemTab->get(1,1) == *elemTest)
        //cout << "OK" << std::endl;
    //else
        //cout << "KO";
}

void TestsCreaturesGroup()
{
    cout << "Création d'un groupe de créatures : ";
    //state::CreaturesID creaTypes; 
    CreaturesGroup* group = new CreaturesGroup(CreaturesID::COOKER);
    if (NULL == group)
        cout << "KO";
    else
        cout << "OK";
    
    cout << "Test getter du type de créatures : " << std::endl;
    if (group->getCreaturesType() == CreaturesID::COOKER)
        cout << "OK" << std::endl;
    else
        cout << "KO";
    
    cout << "Test getter/setter de placed : " << std::endl;
    group->toPlace(2,2);
    if (group->getPlaced() == true)
        cout << "OK";
    else
        cout << "KO";
}

void TestPlayer()
{
    cout << "Création d'un joueur ";
    Player* p1 = new Player();
    if(NULL!=p1){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
    cout << "Test Player Init NbrCells ";
  
    if(p1->getCellsNbr()==0){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
    cout << "Test Player Init NbrZones ";
    if(p1->getZonesNbr()==0){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
    cout << "Test Player Init ConquestPoints ";
    if(p1->getConquestPoints()==0){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
    cout << "Test Player Init CreaturesLeft ";
    if(p1->getCreaturesLeft()==0){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
    cout << "Test Player Init NbrZones ";
    if(p1->getZonesNbr()==0){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
    cout << "Test Player Getters/Setters NbrCells ";
    p1->setCellsNbr(12);
    if(p1->getCellsNbr()==12){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
    cout << "Test Player Getters/Setters NbrZones ";
    p1->setZonesNbr(2);
    if(p1->getZonesNbr()==2){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
        cout << "Test Player Getters/Setters ConquestPoints ";
        p1->setConquestPts(4);
        if(p1->getConquestPoints()==4){
            cout << "OK" << endl;
        }else{
            cout << "KO" << endl;
        }
        
        cout << "Test Player Getters/Setters CreaturesLeft ";
        p1->setCreaLeft(5);
        if(p1->getCreaturesLeft()==5){
            cout << "OK" << endl;
        }else{
            cout << "KO" << endl;
        }
        cout << "Test Player decrease CreaturesLeft ";
        p1->decreaseCreaLeft();
        if(p1->getCreaturesLeft()==4){
            cout << "OK" << endl;
        }else{
            cout << "KO" << endl;
        }
        
        cout << "Test Player Getters/Setters NbrZones ";
        p1->setZonesNbr(1);
        if(p1->getZonesNbr()==1){
            cout << "OK" << endl;
        }else{
            cout << "KO" << endl;
        }
        
    cout << "Test Player Getters/Setters xLastCell ";
    p1->setXLastCell(3);
    if(p1->getXLastCell()==2){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
    cout << "Test Player Getters/Setters yLastCell ";
    p1->setYLastCell(1);
    if(p1->getYLastCell()==1){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
}

void TestCell()
{
    cout << "Création d'une cellule Cell ";
    Cell *c1 = new Cell();
    if(c1==NULL){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
    cout << "Test Cell Getters/Setters occupied ";
    c1->setOccupied(true);
    if(c1->getOccupied()==true){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
    cout << "Test Cell Getters/Setters ResType ";
    c1->setResType("wood");
    if(c1->getResType()=="wood"){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
        
    cout << "Test Cell Getters/Setters ResNbr ";
    c1->setResNbr(2);
    if(c1->getResNbr()==2){
        cout << "OK" << endl;
    }else{
        cout << "KO" << endl;
    }
}
}

