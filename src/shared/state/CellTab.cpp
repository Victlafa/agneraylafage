/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CellTab.h"
#include "Cell.h"
#include "SimpleCell.h"
#include "SpecialCell.h"

namespace state
{
    CellTab::CellTab (size_t width, size_t height) : ElementTab(width,height)
    {
        setTabType(TypeID::CELL);
        initCells();
    }
    CellTab::~CellTab () {}
    
    void CellTab::initCells ()
    {
        // Positionnement des Cellules Speciales

        std::vector<ID> typesSpeciales;
        typesSpeciales.push_back(ID::BARBECUE);
        typesSpeciales.push_back(ID::CANDY);
        typesSpeciales.push_back(ID::POOL);
        typesSpeciales.push_back(ID::SKY);

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

        // On remplit map_cell avec des cellules simples
        std::vector<state::ID> typesSimples;
        typesSimples.push_back(state::ID::DIRT);
        typesSimples.push_back(state::ID::GRASS);
        typesSimples.push_back(state::ID::SAND);

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
                    
                    else{
                        this->set(NULL,i,j);
                    }
                    
                }
                
            }
            
        }   
    }
    
    // Lorsqu'il y a combat et que la conquete/perte d'une cellule special est en jeu, on met à jour les listes des joueurs en conséquence
    void CellTab::assignSpecialCell (Player* winner, Player* loser, ID type)
    {
        std::string stringType;
        
        switch (type)
        {
            case ID::BARBECUE :
                stringType = "barbecue";
                break;
            case ID::CANDY :
                stringType = "candy";
                break;
            case ID::POOL :
                stringType = "pool";
                break;
            case ID::SKY :
                stringType = "sky";
                break;
            default :
                throw std::runtime_error("ElementTab::assignSpecialCell - le type donne en argument ne correspond pas à un type de cellule speciale");
                break;
        }
        
        // Mise à jour de la liste du gagnant :
        if (winner != NULL)
            winner->modifySpeCellsNames(stringType,true);
        
        // Mise à jour de la liste du perdant :
        if (loser != NULL)
            loser->modifySpeCellsNames(stringType,false);
    }
    
    // Renvoie true si la cellule definie par les coordonnees d'entrée est speciale
    bool CellTab::isSpecial (int i, int j)
    {
        ID typeCell = this->get(i,j)->getElemType();
        //std::cout << "ElementTab::isSpecial - coords ("  << i << "," << j << ") - type : " << typeCell << std::endl;
        
        if (typeCell == ID::BARBECUE || typeCell == ID::CANDY || typeCell == ID::POOL || typeCell == ID::SKY)
            return true;
        else
            return false;
    }
}