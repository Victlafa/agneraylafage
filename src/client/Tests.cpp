/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "state.h"
#include "Tests.h"
#include <iostream>


namespace state
{
    
void TestsElementTab()
{
    ElementTab* elemTab = new ElementTab(3,4);
    Element* elemTest = new Element();
    
    std::cout << "Test ElementTab - Init tableau : ";
    (NULL == elemTab) ? std::cout << "KO" << std::endl : std::cout << "OK" << std::endl;
    
    std::cout << "Test ElementTab - Getters hauteur et largeur du tableau : ";
    (elemTab->getHeight()==4 && elemTab->getWidth()==3) ? std::cout << "OK" << std::endl : std::cout << "KO" << std::endl;
    
    std::cout << "Test ElementTab - Methode resize du tableau : ";
    elemTab->resize(6,8);
    (elemTab->getHeight()==8 && elemTab->getWidth()==6) ? std::cout << "OK" << std::endl : std::cout << "KO"<< std::endl;
    
    std::cout << "Test ElementTab - Setter/Getter Element du tableau : ";
    elemTab->set(*elemTest, 1, 1);
    (elemTab->get(1,1) == *elemTest) ? std::cout << "OK" << std::endl : std::cout << "KO";
}

void TestsCreaturesGroup()
{
    CreaturesGroup* group = new CreaturesGroup(CreaturesID::COOKER);
    group->toPlace(2,2);
    
    std::cout << "Création d'un groupe de créatures : ";
    (NULL == group) ? std::cout << "KO" << std::endl : std::cout << "OK" << std::endl;
    
    std::cout << "Test getter du type de créatures : ";
    (group->getCreaturesType() == CreaturesID::COOKER) ? std::cout << "OK" << std::endl : std::cout << "KO" << std::endl;
    
    std::cout << "Test getter/setter de placed : ";
    (group->getPlaced() == true) ? std::cout << "OK" << std::endl : std::cout << "KO" << std::endl;
    
    std::cout << "Test getter coordonnees : ";
    (group->getX() == 2 && group->getY() == 2) ? std::cout << "OK" << std::endl : std::cout << "KO" << std::endl;
}

void TestPlayer()
{   
    Player* p1 = new Player();
    p1->setCellsNbr(12);
    p1->setZonesNbr(2);
    p1->setConquestPts(4);
    p1->setCreaLeft(5);
    p1->setZonesNbr(1);
    p1->setXLastCell(3);
    p1->setYLastCell(1);
    
    std::cout << "Création d'un joueur : ";
    std::cout << ((NULL!=p1) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test Player Init NbrCells : ";
    std::cout << p1->getCellsNbr() << std::endl;
    std::cout << ((p1->getCellsNbr()==0) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test Player Init NbrZones ";
    std::cout << ((p1->getZonesNbr()==0) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Init ConquestPoints : ";
    std::cout << ((p1->getConquestPoints()==0) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test Player Init CreaturesLeft : ";
    std::cout << ((p1->getCreaturesLeft()==0) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Init NbrZones : ";
    std::cout << ((p1->getZonesNbr()==0) ? "OK" : "KO") << std::endl;
     
    std::cout << "Test Player Getters/Setters NbrCells : ";
    std::cout << ((p1->getCellsNbr()==12) ? "OK" : "KO") << std::endl;
      
    std::cout << "Test Player Getters/Setters NbrZones ";
    std::cout << ((p1->getZonesNbr()==2) ? "OK" : "KO") << std::endl;

    std::cout << "Test Player Getters/Setters ConquestPoints ";
    std::cout << ((p1->getConquestPoints() == 4) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Getters/Setters CreaturesLeft ";
    std::cout << ((p1->getCreaturesLeft() == 5) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player decrease CreaturesLeft ";
    p1->decreaseCreaLeft();
    std::cout << ((p1->getCreaturesLeft() == 4) ? "OK" : "KO") << std::endl;
     
    std::cout << "Test Player Getters/Setters NbrZones ";
    std::cout << ((p1->getZonesNbr() == 1) ? "OK" : "KO") << std::endl;
     
    std::cout << "Test Player Getters/Setters xLastCell ";
    std::cout << ((p1->getXLastCell() == 3) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Getters/Setters yLastCell ";
    std::cout << ((p1->getYLastCell()==1) ? "OK" : "KO") << std::endl;
   
}

void TestCell()
{
    std::cout << "Création d'une cellule Cell ";
    Cell *c1 = new Cell();
    if(c1!=NULL){
        std::cout << "OK" << std::endl;
    }else{
        std::cout << "KO" << std::endl;
    }
        
    std::cout << "Test Cell Getters/Setters occupied ";
    c1->setOccupied(true);
    if(c1->getOccupied()==true){
        std::cout << "OK" << std::endl;
    }else{
        std::cout << "KO" << std::endl;
    }
        
    std::cout << "Test Cell Getters/Setters ResType ";
    c1->setResType("wood");
    if(c1->getResType()=="wood"){
        std::cout << "OK" << std::endl;
    }else{
        std::cout << "KO" << std::endl;
    }
        
    std::cout << "Test Cell Getters/Setters ResNbr ";
    c1->setResNbr(2);
    if(c1->getResNbr()==2){
        std::cout << "OK" << std::endl;
    }else{
        std::cout << "KO" << std::endl;
    }
    
    std::cout << "Fin tests cell" << std::endl;
    
}

}
