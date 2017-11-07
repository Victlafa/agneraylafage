/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ElementTab.h"
#include "CreaturesID.h"
#include "Cell.h"
#include "SimpleCell.h"
#include "SpecialCell.h"
#include "CreaturesGroup.h"
#include <iostream>
#include <map>

namespace state
{
    // Constructor :

    ElementTab::ElementTab(TypeID type, size_t width, size_t height) : list(width*height) {
        this->width = width;
        this->height = height;
        tabType = type;


        srand(time(NULL));

        if (type == TypeID::CELL) {

            //std::map<int, state::Cell> map_cell;
            //std::map<int, int> map_cell_text;

            std::cout << "Positionnement des Cellules Speciales" << std::endl;
            //Positionnement des Cellules Speciales
            
            std::vector<SpecialCellID> l_SpeCID = std::vector<SpecialCellID>();
            l_SpeCID.push_back(SpecialCellID::BARBECUE);
            l_SpeCID.push_back(SpecialCellID::CANDY);
            l_SpeCID.push_back(SpecialCellID::POOL);
            l_SpeCID.push_back(SpecialCellID::SKY);
            
            std::vector<unsigned int> li = std::vector<unsigned int>(); //liste des ordonnées des cellules speciales
            std::vector<unsigned int> lj = std::vector<unsigned int>(); //liste des abscisses des cellules speciales
            
            for (int gh=0; gh < 4; gh++)
            {
                li.push_back(0);
                lj.push_back(0);
            }
           
            unsigned int i = 0, j = 0;

            //On détermine les coordonnées des 4 cellules speciales
            for (int sc = 0; sc < 4; sc++) {

                i = 0;j = 0;
                bool trouve = true;

                // On s'assure que les coordonnées trouvées sont dans la grille voulue
                // et qu'elle ne se superpose pas à une autre cellule spéciale
                while (((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) || (i == height-1 && j == width-1) || (i == height-1 && j == width-2) || (i == height-2 && j == width-1)) || trouve) {
                    // Sinon on détermine de nouvelles coordonnées
                    trouve = false;
                    i = rand() % height;
                    j = rand() % width;
                    for (int k = 0; k < 4; k++) {
                        if (i == li[k] && j == lj[k]) {
                            trouve = true;
                        }
                    }
                }

                //Une fois un couple de coordonnées trouvées, on les ajoute à
                // la liste d'indices
                li[sc] = i;
                lj[sc] = j;

            }


            std::cout << "Positionnement des Cellules Simples" << std::endl;
            // On remplit map_cell avec des cellules simples
            std::vector<state::SimpleCellID> l_SimCID = std::vector<state::SimpleCellID>();
            l_SimCID.push_back(state::SimpleCellID::DIRT);
            l_SimCID.push_back(state::SimpleCellID::GRASS);
            l_SimCID.push_back(state::SimpleCellID::SAND);
            
            std::vector<std::string> l_Res = std::vector<std::string>();
            l_Res.push_back("stone");
            l_Res.push_back("food");
            l_Res.push_back("wood");
            l_Res.push_back("metal");
          
            
            for (unsigned int i = 0; i < height; i++) {

                for (unsigned int j = 0; j < width; j++) {

                    // On vérifie que la cellule visée est bien dans le tableau 
                    // voulu et ne se superpose pas à une cellule spéciale
                    if (!((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) || (i == height-1 && j == width-1) || (i == height-1 && j == width-2) || (i == height-2 && j == width-1))) {

                        // Cas où on tombe sur les cellules speciales :
                        if(i == li[0] && j == lj[0])
                            this->set(new SpecialCell(l_SpeCID[0], l_Res[0], 3, li[0], lj[0]),i,j);
                        else if(i == li[1] && j == lj[1])
                            this->set(new SpecialCell(l_SpeCID[1], l_Res[1], 3, li[1], lj[1]),i,j);
                        else if(i == li[2] && j == lj[2])
                            this->set(new SpecialCell(l_SpeCID[2], l_Res[2], 3, li[2], lj[2]),i,j);
                        else if(i == li[3] && j == lj[3])
                            this->set(new SpecialCell(l_SpeCID[3], l_Res[3], 5, li[3], lj[3]),i,j);
                        
                        // Autres cas :
                        else if(!((i == li[0] && j == lj[0]) || (i == li[1] && j == lj[1]) || (i == li[2] && j == lj[2]) || (i == li[3] && j == lj[3]))){
                            int ind = rand();
                            this->set(new SimpleCell(l_SimCID[ind%3],l_Res[ind%4],rand()%3,j,i),i,j);
                        }
                        
                    }
                    
                }
                
            }
            std::cout << "fin boucles" << std::endl;
        }

        else if (type == TypeID::CREATURESGROUP) {/*
            list.reserve(width * height);
            int** intRand1 = new int*[3];
            int rand11;
            int rand12;

            // On va tirer au sort des coordonnees pour placer des creatures :
            for (int k = 0; k < 6; k++) {
                intRand1[k] = new int[2];
                int i, j;
                do {
                    rand11 = rand() % height;
                    rand12 = rand() % width;
                    i=rand11;
                    j=rand12;
                } while ((rand11 == intRand1[j][0] && rand12 == intRand1[j][1]) || (i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) || (i == height-1 && j == width-1) || (i == height-1 && j == width-2) || (i == height-2 && j == width-1));

                intRand1[k][0] = rand11;
                intRand1[k][1] = rand12;
                
                this->set(new CreaturesGroup(CreaturesID::BLACKSMITH),rand11,rand12);
            }*/
        }
        
        else
        {
            std::cout << "Erreur dans le choix du type de tableau !" << std::endl;
        }
        
    }
    
    ElementTab::~ElementTab() {
        for(unsigned int i=0; i<height*width; i++){
            std::cout << "i=" << i << std::endl;
            list[i] = nullptr;
            //delete list[i];
        }
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
    
    const std::unique_ptr<Element>& ElementTab::get (int number) const
    {
        return list.at(number);
    }
    
    void ElementTab::set (Element* elem, int i, int j){
        list[i*width + j].reset(elem);
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