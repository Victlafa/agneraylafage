/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TestsState.h"

namespace state
{
    
void TestsElementTab()
{
    std::cout << "DEBUT TESTS ELEMENTTAB" << std::endl << std::endl;
    
    size_t a, b;
    a=3;b=4;
    
    std::shared_ptr<CellTab> elemTab ( new CellTab(a,b) );
    
    Element* elemTest = new Element();
    
    std::cout << "Test ElementTab - Init tableau : ";
    std::cout << ((NULL != elemTab->get(0,0)) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test ElementTab - Getters hauteur et largeur du tableau : ";
    std::cout << ((elemTab->getHeight()==4 && elemTab->getWidth()==3) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test ElementTab - Methode resize du tableau : ";
    elemTab->resize(6,8);
    std::cout << ((elemTab->getHeight()==8 && elemTab->getWidth()==6) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test ElementTab - Getters/Setters type de tableau : ";
    elemTab->setTabType(TypeID::CELL);
    std::cout << ((elemTab->getTabType()==TypeID::CELL) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test ElementTab - Setter/Getter Element du tableau : ";
    elemTab->set(elemTest, 1, 1);
    std::cout << ((elemTab->get(1,1).get() == elemTest) ? "OK" : "KO") << std::endl << std::endl;
    
    std::cout << "FIN TESTS ELEMENTTAB" << std::endl << std::endl;
    
}

void TestsCreaturesGroup()
{

    std::cout << "DEBUT TESTS CREATURESGROUP" << std::endl << std::endl;
    
    std::unique_ptr<CreaturesGroup> group(new CreaturesGroup(ID::COOKER));
    group->toPlace(2,2);
    
    std::cout << "Création d'un groupe de créatures : ";
    std::cout << ((NULL != group) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test getter du type de créatures : ";
    std::cout << ((group->getElemType() == ID::COOKER) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test getter/setter de placed : ";
    std::cout << ((group->getPlaced() == true) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test getter coordonnees : ";
    std::cout << ((group->getX() == 2 && group->getY() == 2) ? "OK" : "KO") << std::endl<< std::endl;
    
    std::cout << "FIN TESTS CREATURESGROUP" << std::endl << std::endl;
    
    group.reset(new CreaturesGroup(ID::COOKER));
}

void TestsPlayer()
{   
    std::cout << "DEBUT TESTS PLAYER" << std::endl << std::endl;
    std::unique_ptr<Player> p1(new Player());
   
    std::cout << "Création d'un joueur : ";
    std::cout << ((NULL!=p1) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test Player Init NbrCells : ";
    std::cout << ((p1->getCellNbr()==0) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test Player Init NbrZones ";
    std::cout << ((p1->getZonesNbr()==0) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Init ConquestPoints : ";
    std::cout << ((p1->getConquestPoints()==0) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test Player Init CreaturesLeft : ";
    std::cout << ((p1->getCreaturesLeft()==0) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Init speCellsNames : ";
    std::cout << ((p1->getSpeCellsNames().size() == 0) ? "OK" : "KO") << std::endl;
    
    //std::cout << "Test Player Init allCreatures : ";
    //std::cout << ((p1->getAllCreatures().size() == 0) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Init NbrZones : ";
    std::cout << ((p1->getZonesNbr()==0) ? "OK" : "KO") << std::endl;
     
    std::cout << "Test Player Getters/Setters NbrCells : ";
    p1->setCellNbr(12);
    std::cout << ((p1->getCellNbr()==12) ? "OK" : "KO") << std::endl;
      
    std::cout << "Test Player Getters/Setters NbrZones : ";
    p1->setZonesNbr(2);
    std::cout << ((p1->getZonesNbr()==2) ? "OK" : "KO") << std::endl;

    std::cout << "Test Player Getters/Setters ConquestPoints : ";
    p1->setConquestPoints(4);
    std::cout << ((p1->getConquestPoints() == 4) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player Getters/Setters CreaturesLeft : ";
    p1->setCreaturesLeft(5);
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
    std::cout << ((p1->getSpeCellsNames().at(0) == "NomCellule") ? "OK" : "KO") << std::endl;
    
    std::cout << "Test Player modifySpeCellsNames - retrait nom : ";
    size_t listSize = p1->getSpeCellsNames().size();
    p1->modifySpeCellsNames("NomCellule",false);
    std::cout << ((p1->getSpeCellsNames().size() == listSize - 1) ? "OK" : "KO") << std::endl;

    std::cout << "FIN TESTS PLAYER"  << std::endl<< std::endl;

    p1.reset(new Player());
    
}

void TestsCell()
{
    std::cout << "DEBUT TESTS CELL" << std::endl << std::endl;
    
    std::cout << "Création d'une cellule Cell : ";
    std::unique_ptr<Cell> c1(new Cell());
    std::cout << ((c1!=NULL) ? "OK" : "KO") << std::endl;
    /*
    std::cout << "Test Cell Getters/Setters state : ";
    c1->setCellState(CellState::POISONED);
    std::cout << ((c1->getCellState()==CellState::POISONED) ? "OK" : "KO") << std::endl;
    */
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
    
    c1.reset(new Cell());
    
}

void TestsSpecialCell()
{
    std::cout << "DEBUT TESTS SPECIALCELL" << std::endl << std::endl;
	
    std::cout << "Création d'une cellule spéciale SpecialCell : ";
    std::unique_ptr<SpecialCell> cs(new SpecialCell(ID::SKY, "stone", 2, 4, 4));
    std::cout << ((cs!=NULL) ? "OK" : "KO") << std::endl;

    std::cout << "Test SpecialCell Initialisation id : ";
    std::cout << ((cs->getElemType()==ID::SKY) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test SpecialCell Initialisation resType : ";
    std::cout << ((cs->getResType()=="stone") ? "OK" : "KO") << std::endl;
    
    std::cout << "Test SpecialCell Initialisation resNbr : ";
    std::cout << ((cs->getResNbr()==2) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test SpecialCell Initialisation x : ";
    std::cout << ((cs->getX()==4) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test SpecialCell Initialisation y : ";
    std::cout << ((cs->getY()==4) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test SpecialCell Getters/Setters SpecialCellType : ";
    cs->setElemType(ID::POOL);
    std::cout << ((cs->getElemType()==ID::POOL) ? "OK" : "KO") << std::endl << std::endl;
	
    std::cout << "FIN TESTS SPECIALCELL" << std::endl << std::endl;
    
    cs.reset(new SpecialCell(ID::SKY, "stone", 2, 4, 4));
}

void TestsSimpleCell()
{
    std::cout << "DEBUT TESTS SIMPLECELL" << std::endl << std::endl;
	
    std::cout << "Création d'une cellule simple SimpleCell : ";
    std::unique_ptr<SimpleCell> cs(new SimpleCell(ID::GRASS, "stone", 2, 4, 4));
    std::cout << ((cs!=NULL) ? "OK" : "KO") << std::endl;

    std::cout << "Test SimpleCell Initialisation id : ";
    std::cout << ((cs->getElemType()==ID::GRASS) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test SimpleCell Initialisation resType : ";
    std::cout << ((cs->getResType()=="stone") ? "OK" : "KO") << std::endl;
    
    std::cout << "Test SimpleCell Initialisation resNbr : ";
    std::cout << ((cs->getResNbr()==2) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test SimpleCell Initialisation x : ";
    std::cout << ((cs->getX()==4) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test SimpleCell Initialisation y : ";
    std::cout << ((cs->getY()==4) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test SimpleCell Getters/Setters SimpleCellType : ";
    cs->setElemType(ID::DIRT);
        std::cout << ((cs->getElemType()==ID::DIRT) ? "OK" : "KO") << std::endl<< std::endl;
    
    std::cout << "FIN TESTS SIMPLECELL" << std::endl << std::endl;
    
    cs.reset(new SimpleCell(ID::GRASS, "stone", 2, 4, 4));
	
}

void TestsState()
{
    std::unique_ptr<State> etat(new State(CreaturesID::BLACKSMITHS, state::CreaturesID::MINERS));
    
    std::cout << "DEBUT TESTS STATE" << std::endl << std::endl;
   
    std::cout << "Création d'un état : ";
    std::cout << ((NULL!=etat) ? "OK" : "KO") << std::endl;
        
    std::cout << "Test State Init player : ";
    std::cout << (NULL != &(etat->getPlayer(1)) ? "OK" : "KO") << std::endl;
    std::cout << (NULL != &(etat->getPlayer(2)) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test State Init grid : ";
    std::cout << (NULL != etat->getGrid()->get(0,0) ? "OK" : "KO") << std::endl;
    
    std::cout << "Test State Init characters : ";
    std::cout << (NULL != etat->getCharacters()->get(0,0) ? "OK" : "KO") << std::endl;

    std::cout << "Test State Init totalCellNbr : ";
    std::cout << (etat->getCellNbr() == 29 ? "OK" : "KO") << std::endl<< std::endl;

    std::cout << "FIN TESTS STATE" << std::endl << std::endl;
    
    etat.reset(nullptr);
}

}
