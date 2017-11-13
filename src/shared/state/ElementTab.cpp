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
    
    ElementTab::ElementTab(TypeID type, size_t width, size_t height) : list(width*height), tabType(type) {
        this->width = width;
        this->height = height;
        init();
        
    }
    
    ElementTab::~ElementTab() {
        for(unsigned int i=0; i<height*width; i++){
            list[i] = nullptr;
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
    
    const std::unique_ptr<Element>& ElementTab::getByNumber (int number) const
    {
        return list.at(number);
    }
    
    void ElementTab::set (Element* elem, int i, int j){
        list.at(i*width + j).reset(elem);
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
    
    
    void ElementTab::init(){
        
        srand(time(NULL));

        if (tabType == TypeID::CELL)
            initCells();

        else if (tabType == TypeID::CREATURESGROUP)
            initCreatures();
        
        else
            std::cout << "Erreur dans le choix du type de tableau !" << std::endl;
        
    }
    
    void ElementTab::initCells (){

        std::cout << "Positionnement des Cellules Speciales" << std::endl;
        // Positionnement des Cellules Speciales

        std::vector<SpecialCellID> typesSpeciales;
        typesSpeciales.push_back(SpecialCellID::BARBECUE);
        typesSpeciales.push_back(SpecialCellID::CANDY);
        typesSpeciales.push_back(SpecialCellID::POOL);
        typesSpeciales.push_back(SpecialCellID::SKY);

        std::vector<unsigned int> ordSpeciales; // liste des ordonnées des cellules speciales
        std::vector<unsigned int> absSpeciales; // liste des abscisses des cellules speciales

        for (int a = 0; a < 4; a++) {
            ordSpeciales.push_back(0);
            absSpeciales.push_back(0);
        }

        unsigned int i = 0, j = 0;
        bool trouve = false;
        
        // On détermine les coordonnées des 4 cellules speciales
        for (int cptSpec = 0; cptSpec < 4; cptSpec ++) {

            do
            {
                // On tire au hasard des coordonnees
                i = rand() % height;
                j = rand() % width;
                
                for (int k = 0; k < 4; k++) {
                    // si les coordonnees tirees ont deja ete tirees
                    if (i == ordSpeciales[k] && j == absSpeciales[k])
                    {
                        trouve = false;
                        break;
                    }
                    // sinon
                    else
                        trouve = true;
                      
                }
            }
            // On s'assure que les coordonnées trouvées sont dans la grille voulue
            // et qu'elle ne se superposent pas à une autre cellule spéciale
            while ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) || (i == height - 1 && j == width - 1) || (i == height - 1 && j == width - 2) || (i == height - 2 && j == width - 1) || !trouve);
            
            //Une fois un couple de coordonnées trouvé, on les ajoute à
            // la liste d'indices
            ordSpeciales[cptSpec] = i;
            absSpeciales[cptSpec] = j;

        }

        std::cout << "Positionnement des Cellules Simples" << std::endl;
        // On remplit map_cell avec des cellules simples
        std::vector<state::SimpleCellID> typesSimples;
        typesSimples.push_back(state::SimpleCellID::DIRT);
        typesSimples.push_back(state::SimpleCellID::GRASS);
        typesSimples.push_back(state::SimpleCellID::SAND);

        std::vector<std::string> nomsRessources;
        nomsRessources.push_back("stone");
        nomsRessources.push_back("food");
        nomsRessources.push_back("wood");
        nomsRessources.push_back("metal");


        for (unsigned int i = 0; i < height; i++) {

            for (unsigned int j = 0; j < width; j++) {

                // On vérifie que la cellule visée est bien dans le tableau 
                // voulu et ne se superpose pas à une cellule spéciale
                if (!((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) || (i == height - 1 && j == width - 1) || (i == height - 1 && j == width - 2) || (i == height - 2 && j == width - 1))) {

                    // Cas où on tombe sur les cellules speciales :
                    if (i == ordSpeciales[0] && j == absSpeciales[0])
                        this->set(new SpecialCell(typesSpeciales[0], nomsRessources[0], 3, ordSpeciales[0], absSpeciales[0]), i, j);
                    else if (i == ordSpeciales[1] && j == absSpeciales[1])
                        this->set(new SpecialCell(typesSpeciales[1], nomsRessources[1], 3, ordSpeciales[1], absSpeciales[1]), i, j);
                    else if (i == ordSpeciales[2] && j == absSpeciales[2])
                        this->set(new SpecialCell(typesSpeciales[2], nomsRessources[2], 3, ordSpeciales[2], absSpeciales[2]), i, j);
                    else if (i == ordSpeciales[3] && j == absSpeciales[3])
                        this->set(new SpecialCell(typesSpeciales[3], nomsRessources[3], 5, ordSpeciales[3], absSpeciales[3]), i, j);

                        // Autres cas :
                    else if (!((i == ordSpeciales[0] && j == absSpeciales[0]) || (i == ordSpeciales[1] && j == absSpeciales[1]) || (i == ordSpeciales[2] && j == absSpeciales[2]) || (i == ordSpeciales[3] && j == absSpeciales[3]))) {
                        int ind = rand();
                        this->set(new SimpleCell(typesSimples[ind % 3], nomsRessources[ind % 4], rand() % 3, j, i), i, j);
                    }

                }

            }

        }
        
        std::cout << "Fin remplissage tableau d'éléments" << std::endl;
    }
    
    void ElementTab::initCreatures (){

        list.reserve(width * height);
        int** intRand = new int*[3];
        unsigned int rand_i;
        unsigned int rand_j;

        // On va tirer au sort des coordonnees pour placer 3 groupes de creatures :
        for (int j = 0; j < 3; j++) {
            intRand[j] = new int[2];
            intRand[j][0] = 0;
            intRand[j][1] = 0;

            do {
                rand_i = rand() % height;
                rand_j = rand() % width;
            } while ((rand_i == (unsigned int) intRand[j][0] && rand_j == (unsigned int) intRand[j][1]) || (rand_i == 0 && rand_j == 0) || (rand_i == 0 && rand_j == 1) || (rand_i == 1 && rand_j == 0) || (rand_i == height - 1 && rand_j == width - 1) || (rand_i == height - 1 && rand_j == width - 2) || (rand_i == height - 2 && rand_j == width - 1));

            intRand[j][0] = rand_i;
            intRand[j][1] = rand_j;

            this->set(new CreaturesGroup(CreaturesID::BLACKSMITH), rand_i, rand_j);
        }

    }
    
};