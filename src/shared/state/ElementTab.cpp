/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ElementTab.h"
#include "CreaturesID.h"
#include "Cell.h"
#include "SimpleCell.h"
#include "CreaturesGroup.h"
#include <iostream>

namespace state
{
    // Constructor :

    ElementTab::ElementTab(TypeID type, size_t width, size_t height) {
        this->width = width;
        this->height = height;
        tabType = type;

        this->list = std::vector<std::unique_ptr < Element >> (width * height);

        list.resize(width * height);

        /*
        if (type == TypeID::CELL)
        {
            for (int i = 0; i < (int)(width*height); i++)
            {
                //this->list.push_back(std::move(std::unique_ptr<Element>(new Element())));
                list.at(i).reset(new SimpleCell(SimpleCellID::SAND, "wood", 0, 0, 0));
                //this->list.at(i) = std::unique_ptr<Cell>(new Cell());
                //std::cout << list[i].get() << std::endl;

            }
                
        }*/

        srand(time(NULL));

        if (type == TypeID::CELL) {

            std::map<int, state::Cell> map_cell;
            std::map<int, int> map_cell_text;

            std::cout << "Positionnement des Cellules Spéciales" << std::endl;
            //Positionnement des Cellules Spéciales
            std::vector<state::SpecialCell> l_SpeC;
            std::vector<state::SpecialCellID> l_SpeCID = {state::SpecialCellID::BARBECUE, state::SpecialCellID::CANDY, state::SpecialCellID::POOL, state::SpecialCellID::SKY};
            std::vector<int> li = {0, 0, 0, 0}; //liste des ordonnées des cellules spéciales
            std::vector<int> lj = {0, 0, 0, 0}; //liste des absisses des cellules simples

            int i = 0;
            int j = 0;

            //On détermine les coordonnées des 4 cellules spéciales
            for (int sc = 0; sc < 4; sc++) {

                i = 0;
                j = 0;
                bool trouve = true;

                // On s'assure que les coordonnées trouvées sont dans la grille voulue
                // et qu'elle ne se superpose pas à une autre cellule spéciale
                while (((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) || (i == 4 && j == 6) || (i == 4 && j == 5) || (i == 3 && j == 6)) || trouve) {
                    // Sinon on détermine de nouvelles coordonnées
                    trouve = false;
                    i = rand() % 5;
                    j = rand() % 7;
                    for (int k = 0; k < 4; k++) {
                        if (i == li[k] && j == lj[k]) {
                            trouve = true;
                        }
                    }
                }


                std::string restype;
                int resNbr;
                switch (sc) {
                    case 0:
                        restype = "stone";
                        resNbr = 3;
                        break;
                    case 1:
                        restype = "wood";
                        resNbr = 3;
                        break;
                    case 2:
                        restype = "wood";
                        resNbr = 3;
                        break;
                    case 3:
                        restype = "wood";
                        resNbr = 5;
                        break;
                    default:
                        std::cout << "erreur ElementTab restype" << std::endl;
                        break;
                }

                state::SpecialCell *spec = new state::SpecialCell(l_SpeCID[sc], restype, resNbr, i, j);
                l_SpeC.push_back(*spec);
                li[sc] = i;
                lj[sc] = j;

                //map_cell(i,j)=*spec;
                //on adapte les coordonnées de la cellule à la liste des textures
                if (i * 7 + j < 7) {
                    map_cell[i * 7 + j - 2] = *spec;
                    map_cell_text[i * 7 + j - 2] = sc + 3;
                } else
                    if (i * 7 + j < 27) {
                    map_cell[i * 7 + j - 3] = *spec;
                    map_cell_text[i * 7 + j - 3] = sc + 3;
                } else
                    if (i * 7 + j < 33) {
                    map_cell[i * 7 + j - 4] = *spec;
                    map_cell_text[i * 7 + j - 4] = sc + 3;
                } else
                    if (i * 7 + j < 34) {
                    map_cell[i * 7 + j - 5] = *spec;
                    map_cell_text[i * 7 + j - 5] = sc + 3;
                } else {
                    map_cell[i * 7 + j - 6] = *spec;
                    map_cell_text[i * 7 + j - 6] = sc + 3;
                }



                std::cout << "i:" << i << " j:" << j << " sc:" << sc << " i*7+j:" << i * 7 + j << std::endl;

            }


            std::cout << "Positionnement des Cellules Simples" << std::endl;
            // On remplit map_cell avec des cellules simples
            std::vector<state::SimpleCellID> l_SimCID = {state::SimpleCellID::DIRT, state::SimpleCellID::GRASS, state::SimpleCellID::SAND};

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 7; j++) {
                    if (!((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) || (i == 4 && j == 6) || (i == 4 && j == 5) || (i == 3 && j == 6) || (i == li[0] && j == lj[0]) || (i == li[1] && j == lj[1]) || (i == li[2] && j == lj[2]) || (i == li[3] && j == lj[3]))) {
                        std::string restype = "wood";
                        //map_cell(i,j)= state::SimpleCell(l_SimCID[rand()%3],restype,4,i,j);
                        int iid = rand() % 3;
                        state::SimpleCellID id = l_SimCID[iid];
                        //on adapte les coordonnées de la cellule à la liste des textures
                        if (i * 7 + j < 7) {
                            map_cell[i * 7 + j - 2] = state::SimpleCell(id, restype, 4, i, j);
                            map_cell_text[i * 7 + j - 2] = iid;
                        } else
                            if (i * 7 + j < 27) {
                            map_cell[i * 7 + j - 3] = state::SimpleCell(id, restype, 4, i, j);
                            map_cell_text[i * 7 + j - 3] = iid;
                        } else
                            if (i * 7 + j < 33) {
                            map_cell[i * 7 + j - 4] = state::SimpleCell(id, restype, 4, i, j);
                            map_cell_text[i * 7 + j - 4] = iid;
                        } else
                            if (i * 7 + j < 34) {
                            map_cell[i * 7 + j - 5] = state::SimpleCell(id, restype, 4, i, j);
                            map_cell_text[i * 7 + j - 5] = iid;
                        } else {
                            map_cell[i * 7 + j - 6] = state::SimpleCell(id, restype, 4, i, j);
                            map_cell_text[i * 7 + j - 6] = iid;
                        }

                    }
                }
            }
        }

        else if (type == TypeID::CREATURESGROUP) {
            this->list.reserve(width * height);
            int** intRand1 = new int*[3];
            int rand11;
            int rand12;

            // On va tirer au sort des coordonnees pour placer des creatures :
            for (int j = 0; j < 3; j++) {
                intRand1[j] = new int[2];

                do {
                    rand11 = rand() % height;
                    rand12 = rand() % width;
                } while (rand11 == intRand1[j][0] || rand12 == intRand1[j][1]);

                intRand1[j][0] = rand11;
                intRand1[j][1] = rand12;

                this->set(std::unique_ptr<CreaturesGroup>(new CreaturesGroup(CreaturesID::BLACKSMITH)).get(), rand11, rand12);
            }
        }
        
        else
        {
            std::cout << "Erreur dans le choix du type de tableau !" << std::endl;
        }
        
    }
    
    ElementTab::~ElementTab() {
//        for (auto elem : list)     
//            delete elem;
    }
    
    // Getters and setters :
    
    size_t ElementTab::getWidth () const{
        return this->width;
    }
    
    size_t ElementTab::getHeight () const{
        return this->height;
    }
    
    void ElementTab::resize (size_t width, size_t height){
        this->width = width;
        this->height = height;
    }
    
    const std::unique_ptr<Element>& ElementTab::get (int i, int j) const{
        return this->list.at(i*width + j);
    }
    
    void ElementTab::set (Element* elem, int i, int j){
        this->list.at(i*width + j) = std::unique_ptr<Element>(elem);
    }
    
    Element& ElementTab::operator()(int i, int j) const{
        return *(list.at(i*width + j));
    }
    
    TypeID ElementTab::getTabType() const{
        return this->tabType;
    }
    
    void ElementTab::setTabType(TypeID tabType){
        this->tabType = tabType;
    }
    
    
    
    
};