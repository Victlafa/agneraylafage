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
        
        //TestPlayer();

        TestsElementTab();
        
        //TestCell();
        
        //TestsCreaturesGroup();
 
    }

    return 0;
}

namespace state
{
void TestsElementTab()
{
    ElementTab* elemTab = new ElementTab(3,4);
    std::unique_ptr<Element> elemTest = std::unique_ptr<Element>();
    
    cout << "Test ElementTab - Init tableau : ";
    (NULL == elemTab) ? cout << "KO" << std::endl : cout << "OK" << std::endl;
    
    cout << "Test ElementTab - Getters hauteur et largeur du tableau : ";
    (elemTab->getHeight()==4 && elemTab->getWidth()==3) ? cout << "OK" << std::endl : cout << "KO" << std::endl;
    
    cout << "Test ElementTab - Methode resize du tableau : ";
    elemTab->resize(6,8);
    (elemTab->getHeight()==8 && elemTab->getWidth()==6) ? cout << "OK" << std::endl : cout << "KO"<< std::endl;
    
//    cout << "Test ElementTab - Setter/Getter Element du tableau : " << std::endl;
//    elemTab->set(*elemTest, 1, 1);
//    (elemTab->get(1,1) == *elemTest) ? cout << "OK" << std::endl : cout << "KO";
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
    if(p1->getXLastCell()==3){
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
    if(c1!=NULL){
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
        cout << "fin testcell";
    }else{
        cout << "KO" << endl;
    }
    
}

}

