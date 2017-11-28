#include "ElementTab.h"
#include "CreaturesID.h"
#include "Cell.h"
#include "SimpleCell.h"
#include "SpecialCell.h"
#include "CreaturesGroup.h"
#include "Player.h"
#include <iostream>
#include <map>

namespace state
{
    // Constructor :
    ElementTab::ElementTab(TypeID type, size_t width, size_t height) : tabType(type), list(width*height) {
        this->width = width;
        this->height = height;
        init();
        
    }
    
    ElementTab::~ElementTab() {}
    
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
        //if(list.at(i*width+j)!=NULL)
        //    std::cout << "ElementTab.cpp get : getelemtype :" << list.at(i*width + j)->getElemType() << std::endl;
        return list.at(i*width + j);
    }
    
    const std::unique_ptr<Element>& ElementTab::getByNumber (int number) const{
        return list.at(number);
    }
    
    void ElementTab::set (Element* elem, int i, int j){
        list.at(i*width + j).reset(elem);
        //std::cout << "ElementTab : set : getElemType : " << elem->getElemType() << std::endl;
        
        if (elem != nullptr)
        {
            list.at(i*width + j)->setX(i);
            list.at(i*width + j)->setY(j);
        }
        
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
        
        else
            if (tabType != TypeID::CREATURESGROUP)
                throw std::runtime_error("Erreur dans le choix du type de tableau !");
        
    }
    
    void ElementTab::initCells (){

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
    
    // Renvoie false si les coordonnees entrees sont deja presentes dans la liste listeTmp
    bool ElementTab::verifUnicite(std::vector<int> listeTmp, int i, int j){
        
        for (int k = 0; k < (int)(listeTmp.size()/2); k++)
        {
            if (listeTmp[2*k] == i && listeTmp[2*k + 1] == j)
                return false;
        }
        
        return true;
            
    }
    
    // Renvoie true si les coordonnees entrees ne correspondent pas à une case interdite de la grille
    bool ElementTab::verifValiditeCase (unsigned int i, unsigned int j){
        if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) || (i == height - 1 && j == width - 1) || (i == height - 1 && j == width - 2) || (i == height - 2 && j == width - 1))
            return false;
        else
            return true;
    }
    
    void ElementTab::moveElement (int i_elem, int j_elem, int new_i_elem, int new_j_elem, int fight){
        
        // Nbre de creatures de la cellule attaquante
        int creaNbrAtt = this->get(i_elem,j_elem)->getCreaturesNbr();
        
        // Nbre de creatures de la cellule destination
        int creaNbrDef = 0;
        // A definir seulement si la case de destination est non vide !
        if (this->get(new_i_elem,new_j_elem) != NULL)
            creaNbrDef = this->get(new_i_elem,new_j_elem)->getCreaturesNbr();
        
        // On verifie si le deplacement est possible ou non
        
        // La case destination est-elle autorisée ?
        if (verifValiditeCase(new_i_elem,new_j_elem))
        {
                        
            // La case destination est-elle vide ?
            if (this->get(new_i_elem,new_j_elem) == NULL)
            {
                // Si c'est le cas, on procède au déplacement
                
                // On cree un nouveau groupe que l'on place dans la case vide avec N - 1 creatures SAUF si la case de depart n'en contenait qu'une !
                if (creaNbrAtt > 1)
                {
                    Element* newGroup = new CreaturesGroup(this->get(i_elem, j_elem)->getElemType(),creaNbrAtt - 1,this->get(i_elem, j_elem)->getPlayer());
                    this->set(newGroup,new_i_elem,new_j_elem);
                    // On fixe le nbre de creatures de la case attaquante à 1
                    this->get(i_elem,j_elem)->setCreaturesNbr(1);
                }
                
                else
                {
                    Element* newGroup = new CreaturesGroup(this->get(i_elem, j_elem)->getElemType(),1,this->get(i_elem, j_elem)->getPlayer());
                    this->set(newGroup,new_i_elem,new_j_elem);
                    // On fixe le nbre de creatures de la case attaquante à 0
                    this->get(i_elem,j_elem)->setCreaturesNbr(0);
                }
                
                // On verifie que le mouvement a bien été effectué
                if (this->get(new_i_elem,new_j_elem) != nullptr)
                {
                    // Si c'est le cas on veut savoir si la case est speciale ou non
                    std::cout << "ElementTab::moveElement - appel isSpecial ligne 242" << std::endl;
                    
                    // si la cellule obtenue est speciale, on ajoute le nom du type à la liste de noms du joueur
                    if (isSpecial(new_i_elem, new_j_elem))
                        this->assignSpecialCell(this->get(new_i_elem, new_j_elem)->getPlayer(), nullptr, this->get(new_i_elem, new_j_elem)->getElemType());
                }
                else
                    throw std::runtime_error("Le deplacement vers une case vide ne s'est pas deroulé correctement, la case est toujours vide");
                
            }
            
            // Est-elle occupée par le joueur qui se déplace ou par l'adversaire ?
            else 
            {
                
                if (fight >= 0 && fight < 4) {
                    
                    // La case destination est occupée par le joueur qui se deplace
                    if (fight == 0)
                    {
                        // On definit ces variables afin de tenir compte du fait que chaque cellule doit contenir au maximum 5 creatures
                        // On doit aussi tenir compte du fait que si la cellule de depart comporte une creature, celle-ci se deplace en laissant sa case vide
                        // Dans les autres cas, on doit laisser au moins une creature sur la case de depart lors du deplacement
                        int oldDef = creaNbrDef;
                        int newDef_several = ((creaNbrDef + creaNbrAtt - 1) <= 5) ? (creaNbrDef + creaNbrAtt - 1) : 5;
                        int newDef_one = ((creaNbrDef + 1) <= 5) ? (creaNbrDef + 1) : 5;
                        
                        // On fixe le nbre de creatures de la case destination
                        (creaNbrAtt != 1) ? this->get(new_i_elem,new_j_elem)->setCreaturesNbr(newDef_several) : this->get(new_i_elem,new_j_elem)->setCreaturesNbr(newDef_one);
                        // On fixe le nouveau nbre de creatures de la case de depart
                        (creaNbrAtt != 1) ? this->get(i_elem,j_elem)->setCreaturesNbr(creaNbrAtt - newDef_several + oldDef) : this->get(i_elem,j_elem)->setCreaturesNbr(creaNbrAtt - newDef_one + oldDef);
                    }
                        
                    // Le joueur 1 ou le joueur 2 a gagné le combat sans aucune pitie en etant l'attaquant
                    else if (fight == 1 || fight == 2)
                    {
                        // On veut savoir si la case est speciale ou non
                        std::cout << "ElementTab::moveElement - appel isSpecial ligne 271" << std::endl;
                        
                        // si la cellule attaquee est speciale, on ajoute/supprime le nom du type à la liste de noms des joueurs
                        if (isSpecial(new_i_elem, new_j_elem))
                            this->assignSpecialCell(this->get(i_elem,j_elem)->getPlayer(),this->get(new_i_elem,new_j_elem)->getPlayer(),this->get(new_i_elem,new_j_elem)->getElemType());
                        
                        // On fixe le nouveau nbre de creatures de la case de depart
                        (creaNbrAtt != 1) ? this->get(i_elem,j_elem)->setCreaturesNbr(1) : this->get(i_elem,j_elem)->setCreaturesNbr(0);
                        
                        // On detruit les creatures de la case defense en on remplaçant par celles de l'attaquant
                        (creaNbrAtt != 1) ? this->set(new CreaturesGroup(this->get(i_elem, j_elem)->getElemType(), (creaNbrAtt - 1) % 5, this->get(i_elem, j_elem)->getPlayer()), new_i_elem, new_j_elem) : this->set(new CreaturesGroup(this->get(i_elem, j_elem)->getElemType(),1, this->get(i_elem, j_elem)->getPlayer()), new_i_elem, new_j_elem);
                        
                    }
                        
//                    else
//                        std::cout << "Le defenseur a gagne" << std::endl;
                    // Si fight = 3 ie le defenseur a gagne, on detruit seulement les creatures envoyées au combat par l'attaquant
                    // Dans ce cas là on voit juste le nombre de creatures de la case attaquante tomber à 1
                }
                
                else
                    throw std::runtime_error("Le déplacement n'a pas pu etre effectué !");
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
    
    void ElementTab::placeElement (int new_i_elem, int new_j_elem, ID creaType){
        
        // La case destination est-elle autorisée ?
        if (verifValiditeCase(new_i_elem,new_j_elem))
        {
            std::cout << "ElementTab::placeElement - appel isSpecial ligne 332" << std::endl;
            // On veut aussi savoir si la case destination est speciale ou pas
            bool isSpe = isSpecial(new_i_elem,new_j_elem);
            
            // La case destination est-elle vide ?
            if (list.at(new_i_elem*width + new_j_elem) == NULL)
            {
                // Si c'est le cas, on procède au placement
                
                // On cree un nouveau groupe que l'on place dans la case vide avec 1 creature
                Element* newGroup = new CreaturesGroup(creaType,1,NULL);
                this->set(newGroup,new_i_elem,new_j_elem);
                
                // On verifie que le placement a bien ete effectue
                if (this->get(new_i_elem,new_j_elem) != NULL && this->get(new_i_elem,new_j_elem)->getCreaturesNbr() == 1)
                {
                    std::cout << "Une creature de l'IA a bien ete placee dans la grille" << std::endl;
                    
                    // si la cellule obtenue est speciale, on ajoute le nom du type à la liste de noms du joueur
                    if (isSpe)
                        this->assignSpecialCell(this->get(new_i_elem,new_j_elem)->getPlayer(),nullptr,this->get(new_i_elem,new_j_elem)->getElemType());
                }
                    
                
                else
                    throw std::runtime_error("Le placement d'une creature de l'IA dans une case vide n'a pas ete effectue !");
            }
            
            // Elle est occupee par le joueur qui souhaite placer une creature
            else if ((ID)list.at(new_i_elem*width + new_j_elem)->getPlayer()->getClanName() == creaType)
            {
                // On ajoute une creature au groupe existant
                int nbrCrea = list.at(new_i_elem*width + new_j_elem)->getCreaturesNbr();
                list.at(new_i_elem*width + new_j_elem)->setCreaturesNbr(nbrCrea + 1);
                
                // On verifie que le placement a bien ete effectue
                if (this->get(new_i_elem,new_j_elem) != NULL && this->get(new_i_elem,new_j_elem)->getCreaturesNbr() == nbrCrea + 1)
                    std::cout << "Une creature de l'IA a bien ete placee dans la grille" << std::endl;
                
                else
                    throw std::runtime_error("Le placement d'une creature du joueur dans une de ses cases n'a pas ete effectue !");
            }
            
            // Elle est occupee par l'adversaire
            else
                throw std::runtime_error("Le joueur ne peut pas placer de creatures de sa reserve dans une cellule adverse !");
        }
        
        else
            throw std::runtime_error("Le placement n'a pas pu etre effectué car la case de destination est interdite !");
        
    }
    
    // Lorsqu'il y a combat et que la conquete/perte d'une cellule special est en jeu, on met à jour les listes des joueurs en conséquence
    void ElementTab::assignSpecialCell(Player* winner, Player* loser, ID type)
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
        if (winner != nullptr)
            winner->modifySpeCellsNames(stringType,true);
        
        // Mise à jour de la liste du perdant :
        if (loser != nullptr)
            loser->modifySpeCellsNames(stringType,false);
    }
    
    // Renvoie true si la cellule definie par les coordonnees d'entrée est speciale
    bool ElementTab::isSpecial(int i, int j)
    {
        ID typeCell = this->get(i,j)->getElemType();
        std::cout << "ElementTab::isSpecial - coords ("  << i << "," << j << ") - type : " << typeCell << std::endl;
        
        if (typeCell == ID::BARBECUE || typeCell == ID::CANDY || typeCell == ID::POOL || typeCell == ID::SKY)
            return true;
        else
            return false;
    }
    
};