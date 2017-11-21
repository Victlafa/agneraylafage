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
    
    ElementTab::ElementTab(TypeID type, size_t width, size_t height) : tabType(type), list(width*height) {
        //std::cout << "Appel du constructeur ElementTab" << std::endl;
        this->width = width;
        this->height = height;
        init();
        
    }
    
    ElementTab::~ElementTab() {
        //std::cout << "Appel du destructeur ElementTab" << std::endl;
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
        return list.at(i*width + j);
    }
    
    const std::unique_ptr<Element>& ElementTab::getByNumber (int number) const{
        return list.at(number);
    }
    
    void ElementTab::set (Element* elem, int i, int j){
        list.at(i*width + j).reset(elem);
        list.at(i*width + j)->setX(i);
        list.at(i*width + j)->setY(j);
    }
    
    const std::unique_ptr<Element>& ElementTab::operator()(int i, int j) const{
        return list.at(i*width + j);
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
            throw std::runtime_error("Erreur dans le choix du type de tableau !");
        
        //std::cout << "Fin remplissage tableau d'éléments" << std::endl;
        
    }
    
    void ElementTab::initCells (){


        std::cout << "Positionnement des Cellules Speciales" << std::endl;
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

        //std::cout << "Positionnement des Cellules Simples" << std::endl;
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
            std::cout << "fin boucles" << std::endl;
        }     
        
    }
    
    void ElementTab::initCreatures (){
        
        // On fera en sorte en début de partie que chaque joueur dispose de trois groupes de 2 cratures disposées sur la carte
        // Cette liste permettra de stocker temporairement les coordonnees deja tirees
        std::vector<int> intRand(12);
        // Coordonnees pour creatures du joueur 1
        int rand_i, rand_j;
        // Pour celles du joueur 2
        //int rand_i_J2, rand_j_J2;
        
        bool verifJ1;
        //bool verifJ2;
        bool verifCaseJ1;
        //bool verifCaseJ2;

        // On va tirer au sort des coordonnees pour placer 6 groupes de creatures
        
        for (int j = 0; j < 6; j++) {
            
            // On fait les tirages des deux joueurs 
            do {
                rand_i = rand() % height;
                rand_j = rand() % width;
                // On verifie la validite des coordonnees : ont-elles deja été tirees ? Correspondent-elles à des cases interdites ?
                verifJ1 = verifUnicite(intRand,rand_i,rand_j);
                verifCaseJ1 = verifValiditeCase(rand_i,rand_j);
                
            } while (verifJ1 || !verifCaseJ1);
            
//            do {
//                
//                rand_i_J2 = rand() % height;
//                rand_j_J2 = rand() % width;
//                // On verifie la validite des coordonnees : ont-elles deja été tirees ? Correspondent-elles à des cases interdites ?
//                verifJ2 = verifUnicite(rand_i_J2, rand_j_J2);
//                verifCaseJ2 = verifValiditeCase(rand_i_J2, rand_j_J2);
//                
//            } while (verifJ2 || !verifCaseJ2);

            intRand[2*j] = rand_i;
            intRand[2*j + 1] = rand_j;
            //intRand[2*j + 6] = rand_i_J1;
            //intRand[2*j + 7] = rand_j_J1;

            this->set(new CreaturesGroup(ID::BLACKSMITH, 2, NULL), rand_i, rand_j);
        }

    }
    
    // Renvoie true si les coordonnees entrees sont deja presentes dans la liste listeTmp
    bool ElementTab::verifUnicite(std::vector<int> listeTmp, int i, int j){
        
        for (int i = 0; i < (int)(listeTmp.size()/2); i++)
        {
            if (listeTmp[2*i] == i && listeTmp[2*i + 1] == j)
                return true;
        }
        
        return false;
            
    }
    
    // Renvoie true si les coordonnees entrees ne correspondent pas à une case interdite de la grille
    bool ElementTab::verifValiditeCase (unsigned int i, unsigned int j){
        if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) || (i == height - 1 && j == width - 1) || (i == height - 1 && j == width - 2) || (i == height - 2 && j == width - 1))
            return false;
        else
            return true;
    }
    
    void ElementTab::moveElement (int i_elem, int j_elem, int new_i_elem, int new_j_elem, int fight){
        
        std::cout << "Entrée dans MoveElement" << std::endl;
        std::cout << "Coordonnees : (" << i_elem << "," << j_elem << ") " << std::endl;
        std::cout << "Groupe de creatures selectionne : " << this->get(i_elem,j_elem).get() << std::endl;
        std::cout << "Nombre de creatures du groupe : " << this->get(i_elem,j_elem)->getCreaturesNbr() << std::endl;
        
        // Nbre de creatures de la cellule attaquante
        int creaNbrAtt = list.at(i_elem*width + j_elem)->getCreaturesNbr();
        
        // Nbre de creatures de la cellule destination
        int creaNbrDef = 0;
        // A definir seulement si la case de destination est non vide !
        if (list.at(new_i_elem*width + new_j_elem) != NULL)
            creaNbrDef = list.at(new_i_elem*width + new_j_elem)->getCreaturesNbr();
        
        // On verifie si le deplacement est possible ou non
        
        // La case destination est-elle autorisée ?
        if (verifValiditeCase(new_i_elem,new_j_elem))
        {
            // La case destination est-elle vide ?
            if (list.at(new_i_elem*width + new_j_elem) == NULL)
            {
                // Si c'est le cas, on procède au déplacement
                
                // On fixe le nbre de creatures de la case attaquante à 1
                list.at(i_elem*width + j_elem)->setCreaturesNbr(1);
                // On cree un nouveau groupe que l'on place dans la case vide avec N - 1 creatures
                Element* newGroup = new CreaturesGroup(list.at(i_elem*width + j_elem)->getElemType(),list.at(i_elem*width + j_elem)->getCreaturesNbr() - 1,list.at(i_elem*width + j_elem)->getPlayer());
                this->set(newGroup,new_i_elem,new_j_elem);
                std::cout << "Ancienne case : " << list.at(i_elem*width + j_elem).get() << std::endl;
                std::cout << "Nombre de creatures ancienne case : " << list.at(i_elem*width + j_elem)->getCreaturesNbr() << std::endl;
            }
            
            // Est-elle occupée par le joueur qui se déplace ou par l'adversaire ?
            else 
            {
                
                if (fight >= 0 && fight < 4) {
                    
                    // On fixe le nbre de creatures de la case attaquante à 1
                    list.at(i_elem * width + j_elem)->setCreaturesNbr(1);
                    
                    // La case destination est occupée par le joueur qui se deplace
                    if (fight == 0)
                        // On fixe le nbre de creatures de la case destination
                        list.at(new_i_elem * width + new_j_elem)->setCreaturesNbr((creaNbrDef + creaNbrAtt - 1) % 5);
                    
                    // L'attaquant a gagné le combat
                    else if (fight == 1) 
                        // On detruit les creatures de la case defense en on remplaçant par celles de l'attaquant
                        this->set(new CreaturesGroup(list.at(i_elem * width + j_elem)->getElemType(), (creaNbrAtt - 1) % 5, NULL), new_i_elem, new_j_elem);
                    
                    // Si fight = 2 le defenseur a gagné le combat, si fight = 3 il y a egalité mais on considere que c'est le defenseur qui gagne
                    // Dans ce cas là on voit juste le nombre de creatures de la case attaquante tomber à 1
                }
                
                else
                {
                    throw std::runtime_error("Le déplacement n'a pas pu etre effectué !");
                }
                
            }
                
            
        }
        
        else
            throw std::runtime_error("Le déplacement n'a pas pu etre effectué car la case de destination est interdite !");
        
        
    }
    
    void ElementTab::poisonCell(bool poison, int i, int j)
    {
        if (poison)
        {
            get(i,j)->setCellState(CellState::POISONED);
            
            //(Cell)(*pCell,CellState::POISONED); //.setCellState(CellState::POISONED);
            std::cout << "etat de la cellule : " << this->get(i,j)->getCellState() << std::endl;
            std::cout << "La case (" << i << "," << j << ") a normalement ete empoisonnee\n" << std::endl;
        }
        
        else
        {
            get(i,j)->setCellState(CellState::NORMAL);
        }
    }
    
    bool ElementTab::isPoisoned(int i, int j){
        if (get(i,j)->getCellState() == CellState::POISONED)
            return true;
        else
            return false;
    }
    
    bool ElementTab::isOccupiedByOpp(int i, int j, Player* joueur){
        
        if (this->tabType == TypeID::CREATURESGROUP)
        {
            if ((this->get(i,j).get() != NULL) && get(i,j)->getPlayer() != joueur)
                return true;
            else
                return false;
        }
        
        else
            throw std::runtime_error("Cette methode ne doit pas etre utilisee pour les cellules !");
        
    }
    
};