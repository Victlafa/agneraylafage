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
    std::cout << "DEBUT TESTS ELEMENTTAB" << std::endl << std::endl;
    
    ElementTab* elemTab = new ElementTab(3,4);
    Element* elemTest = new Element();
    
    std::cout << "Test ElementTab - Init tableau : ";
    std::cout << ((NULL != elemTab) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test ElementTab - Getters hauteur et largeur du tableau : ";
    std::cout << ((elemTab->getHeight()==4 && elemTab->getWidth()==3) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test ElementTab - Methode resize du tableau : ";
    elemTab->resize(6,8);
    std::cout << ((elemTab->getHeight()==8 && elemTab->getWidth()==6) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test ElementTab - Getters/Setters type de tableau : ";
    elemTab->setTabType(TypeID::CREATURESGROUP);
    std::cout << ((elemTab->getTabType()==TypeID::CREATURESGROUP) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test ElementTab - Setter/Getter Element du tableau : ";
    elemTab->set(*elemTest, 1, 1);
    std::cout << ((elemTab->get(1,1) == *elemTest) ? "OK" : "KO") << std::endl << std::endl;
    
    std::cout << "FIN TESTS ELEMENTTAB" << std::endl << std::endl;
}

void TestsCreaturesGroup()
{
    std::cout << "DEBUT TESTS CREATURESGROUP" << std::endl << std::endl;
    
    CreaturesGroup* group = new CreaturesGroup(CreaturesID::COOKER);
    group->toPlace(2,2);
    
    std::cout << "Création d'un groupe de créatures : ";
    std::cout << ((NULL != group) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test getter du type de créatures : ";
    std::cout << ((group->getCreaturesType() == CreaturesID::COOKER) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test getter/setter de placed : ";
    std::cout << ((group->getPlaced() == true) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test getter coordonnees : ";
    std::cout << ((group->getX() == 2 && group->getY() == 2) ? "OK" : "KO") << std::endl<< std::endl;
    
    std::cout << "FIN TESTS CREATURESGROUP" << std::endl << std::endl;
}

void TestsPlayer()
{   
    std::cout << "DEBUT TESTS PLAYER" << std::endl << std::endl;
    Player* p1 = new Player();
   
    std::cout << "Création d'un joueur : ";
    std::cout << ((NULL!=p1) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test Player Init NbrCells : ";
    std::cout << ((p1->getCellsNbr()==0) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test Player Init NbrZones ";
    std::cout << ((p1->getZonesNbr()==0) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Init ConquestPoints : ";
    std::cout << ((p1->getConquestPoints()==0) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test Player Init CreaturesLeft : ";
    std::cout << ((p1->getCreaturesLeft()==0) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Init speCellsNames : ";
    std::cout << ((NULL != p1->getSpeCellsNames()) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Init allCreatures : ";
    std::cout << ((NULL != p1->getAllCreatures()) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Init NbrZones : ";
    std::cout << ((p1->getZonesNbr()==0) ? "OK" : "KO") << std::endl;
     
    std::cout << "Test Player Getters/Setters NbrCells : ";
    p1->setCellsNbr(12);
    std::cout << ((p1->getCellsNbr()==12) ? "OK" : "KO") << std::endl;
      
    std::cout << "Test Player Getters/Setters NbrZones : ";
    p1->setZonesNbr(2);
    std::cout << ((p1->getZonesNbr()==2) ? "OK" : "KO") << std::endl;

    std::cout << "Test Player Getters/Setters ConquestPoints : ";
    p1->setConquestPts(4);
    std::cout << ((p1->getConquestPoints() == 4) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Getters/Setters CreaturesLeft : ";
    p1->setCreaLeft(5);
    std::cout << ((p1->getCreaturesLeft() == 5) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player decrease CreaturesLeft : ";
    p1->decreaseCreaLeft();
    std::cout << ((p1->getCreaturesLeft() == 4) ? "OK" : "KO") << std::endl;
     
    std::cout << "Test Player Getters/Setters xLastCell : ";
    p1->setXLastCell(3);
    std::cout << ((p1->getXLastCell() == 3) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Getters/Setters yLastCell : ";
    p1->setYLastCell(1);
    std::cout << ((p1->getYLastCell()==1) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player modifySpeCellsNames - ajout nom : ";
    p1->modifySpeCellsNames("NomCellule",true);
    std::cout << ((p1->getSpeCellsNames()->at(0) == "NomCellule") ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player modifySpeCellsNames - retrait nom : ";
    size_t listSize = p1->getSpeCellsNames()->size();
    p1->modifySpeCellsNames("NomCellule",false);
    std::cout << ((p1->getSpeCellsNames()->size() == listSize - 1) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Getter/Setter allCreatures - liste complete : ";
    p1->setAllCreatures(new std::vector<CreaturesGroup>());
    std::cout << ((NULL != p1->getAllCreatures()) ? "OK" : "KO") << std::endl<< std::endl;
    
//    std::cout << "Test Player Getter/Setter allCreatures - ajout d'un element : ";
//    CreaturesGroup* group = new CreaturesGroup();
//    p1->setAllCreatures(true, group);
//    std::cout << ((NULL != p1->getAllCreatures()->at(0)) ? "OK" : "KO") << std::endl<< std::endl;
//    
//    std::cout << "Test Player Getter/Setter allCreatures - retrait d'un element : ";
//    size_t listSize2 = p1->getAllCreatures()->size();
//    p1->setAllCreatures(false, group);
//    std::cout << ((p1->getSpeCellsNames()->size() == listSize2 - 1) ? "OK" : "KO") << std::endl<< std::endl;
//    
    std::cout << "FIN TESTS PLAYER"  << std::endl<< std::endl;
}

void TestsCell()
{
    std::cout << "DEBUT TESTS CELL" << std::endl << std::endl;
    
    std::cout << "Création d'une cellule Cell : ";
    Cell *c1 = new Cell();
    std::cout << ((c1!=NULL) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Cell Getters/Setters type : ";
    c1->setCellType(CellTypeID::SIMPLE);
    std::cout << ((c1->getCellType()==CellTypeID::SIMPLE) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Cell Getters/Setters state : ";
    c1->setCellState(CellState::POISONED);
    std::cout << ((c1->getCellState()==CellState::POISONED) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test Cell Getters/Setters occupied : ";
    c1->setOccupied(true);
    std::cout << ((c1->getOccupied()==true) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test Cell Getters/Setters ResType : ";
    c1->setResType("wood");
    std::cout << ((c1->getResType()=="wood") ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Cell Getters/Setters ResNbr : ";
    c1->setResNbr(2);
    std::cout << ((c1->getResNbr()==2) ? "OK" : "KO") << std::endl << std::endl;
    
    std::cout << "FIN TESTS CELL" << std::endl << std::endl;
    
}

void TestsState()
{
    State* etat = new State();
    
    std::cout << "DEBUT TESTS STATE" << std::endl << std::endl;
   
    std::cout << "Création d'un état : ";
    std::cout << ((NULL!=etat) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test State Init player : ";
    std::cout << (NULL != &(etat->getPlayer()) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test State Init grid : ";
    std::cout << (NULL != etat->getGrid() ? "OK" : "KO") << std::endl;
    
    std::cout << "Test State Init characters : ";
    std::cout << (NULL != etat->getCharacters() ? "OK" : "KO") << std::endl;

    std::cout << "Test State Init totalCellNbr : ";
    std::cout << (etat->getCellNbr() == 29 ? "OK" : "KO") << std::endl<< std::endl;

    std::cout << "FIN TESTS STATE" << std::endl << std::endl;
}

}
