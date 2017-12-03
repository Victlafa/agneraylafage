/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CreaturesTab.h"
#include "CreaturesID.h"
#include "CreaturesGroup.h"

namespace state
{
    CreaturesTab::CreaturesTab (size_t width, size_t height) : ElementTab(width,height) { setTabType(TypeID::CREATURESGROUP); }
    CreaturesTab::~CreaturesTab () {}
    
    bool CreaturesTab::isOccupiedByOpp (int i, int j, Player* joueur)
    {
        if ((this->get(i,j).get() != NULL) && get(i,j)->getPlayer() != joueur)
                return true;
        else
            return false;
    }
    
    void CreaturesTab::moveElement (int i_elem, int j_elem, int new_i_elem, int new_j_elem, int fight)
    {
                
        // Nbre de creatures de la cellule attaquante
        int creaNbrAtt = this->get(i_elem,j_elem)->getCreaturesNbr();
        
        // Nbre de creatures de la cellule destination
        int creaNbrDef = 0;
        // A definir seulement si la case de destination est non vide !
        if (this->get(new_i_elem,new_j_elem) != NULL)
            creaNbrDef = this->get(new_i_elem,new_j_elem)->getCreaturesNbr();
        
        // On verifie si le deplacement est possible ou non
        
        // La case destination est-elle autorisée ?
        if (isEnable(new_i_elem,new_j_elem))
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
//                if (this->get(new_i_elem,new_j_elem) != nullptr)
//                {
//                    // Si c'est le cas on veut savoir si la case est speciale ou non
//                    //std::cout << "ElementTab::moveElement - appel isSpecial ligne 242" << std::endl;
//                    
//                    // si la cellule obtenue est speciale, on ajoute le nom du type à la liste de noms du joueur
//                    if (isSpecial(new_i_elem, new_j_elem))
//                        this->assignSpecialCell(this->get(new_i_elem, new_j_elem)->getPlayer(), nullptr, this->get(new_i_elem, new_j_elem)->getElemType());
//                }
//                else
//                    throw std::runtime_error("Le deplacement vers une case vide ne s'est pas deroulé correctement, la case est toujours vide");
//                
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
                        //std::cout << "ElementTab::moveElement - appel isSpecial ligne 271" << std::endl;
                        
                        // si la cellule attaquee est speciale, on ajoute/supprime le nom du type à la liste de noms des joueurs
//                        if (isSpecial(new_i_elem, new_j_elem))
//                            this->assignSpecialCell(this->get(i_elem,j_elem)->getPlayer(),this->get(new_i_elem,new_j_elem)->getPlayer(),this->get(new_i_elem,new_j_elem)->getElemType());
//                        
                        // On fixe le nouveau nbre de creatures de la case de depart
                        (creaNbrAtt != 1) ? this->get(i_elem,j_elem)->setCreaturesNbr(1) : this->get(i_elem,j_elem)->setCreaturesNbr(0);
                        
                        // On detruit les creatures de la case defense en les remplaçant par celles de l'attaquant
                        (creaNbrAtt != 1) ? this->set(new CreaturesGroup(this->get(i_elem, j_elem)->getElemType(), creaNbrAtt - 1, this->get(i_elem, j_elem)->getPlayer()), new_i_elem, new_j_elem) : this->set(new CreaturesGroup(this->get(i_elem, j_elem)->getElemType(),1, this->get(i_elem, j_elem)->getPlayer()), new_i_elem, new_j_elem);
                        
                    }
                        
                    else
                    {
                        this->get(i_elem, j_elem)->setCreaturesNbr(1);
                        // std::cout << "Le defenseur a gagne" << std::endl;
                        // Si fight = 3 ie le defenseur a gagne, on detruit seulement les creatures envoyées au combat par l'attaquant
                        // Dans ce cas là on voit juste le nombre de creatures de la case attaquante tomber à 1
//                        if (this->get(i_elem, j_elem)->getCreaturesNbr() != 1)
//                            this->get(i_elem, j_elem)->setCreaturesNbr(1);
//                        else
                            
                    }

                }
                
                else
                    throw std::runtime_error("Le déplacement n'a pas pu etre effectué !");
            }
        }
        
        else
            throw std::runtime_error("Le déplacement n'a pas pu etre effectué car la case de destination est interdite !");
        
    }
    
    void CreaturesTab::placeElement (int new_i_elem, int new_j_elem, ID creaType)
    {
        
        // La case destination est-elle autorisée ?
        if (isEnable(new_i_elem,new_j_elem))
        {
            //std::cout << "ElementTab::placeElement - appel isSpecial ligne 332" << std::endl;
            // On veut aussi savoir si la case destination est speciale ou pas
            //bool isSpe = isSpecial(new_i_elem,new_j_elem);
            
            // La case destination est-elle vide ?
            if (this->get(new_i_elem,new_j_elem) == NULL)
            {
                // Si c'est le cas, on procède au placement
                
                // On cree un nouveau groupe que l'on place dans la case vide avec 1 creature
                Element* newGroup = new CreaturesGroup(creaType,1,NULL);
                this->set(newGroup,new_i_elem,new_j_elem);
                
                // On verifie que le placement a bien ete effectue
//                if (this->get(new_i_elem,new_j_elem) != NULL && this->get(new_i_elem,new_j_elem)->getCreaturesNbr() == 1)
//                {
//                    //std::cout << "Une creature de l'IA a bien ete placee dans la grille" << std::endl;
//                    
//                    // si la cellule obtenue est speciale, on ajoute le nom du type à la liste de noms du joueur
//                    if (isSpe)
//                        this->assignSpecialCell(this->get(new_i_elem,new_j_elem)->getPlayer(),nullptr,this->get(new_i_elem,new_j_elem)->getElemType());
//                }
                    
                
//                else
//                    throw std::runtime_error("Le placement d'une creature de l'IA dans une case vide n'a pas ete effectue !");
            }
            
            // Elle est occupee par le joueur qui souhaite placer une creature
            else if ((ID)(this->get(new_i_elem,new_j_elem))->getPlayer()->getClanName() == creaType)
            {
                // On ajoute une creature au groupe existant
                int nbrCrea = this->get(new_i_elem, new_j_elem)->getCreaturesNbr();
                this->get(new_i_elem, new_j_elem)->setCreaturesNbr(nbrCrea + 1);
                
                // On verifie que le placement a bien ete effectue
                if (this->get(new_i_elem,new_j_elem) == nullptr)
                    throw std::runtime_error("Le placement d'une creature du joueur dans une de ses cases n'a pas ete effectue !");
            }
            
            // Elle est occupee par l'adversaire
            else
                throw std::runtime_error("Le joueur ne peut pas placer de creatures de sa reserve dans une cellule adverse !");
        }
        
        else
            throw std::runtime_error("Le placement n'a pas pu etre effectué car la case de destination est interdite !");
        
    }
    
    bool CreaturesTab::isEnable (unsigned int i, unsigned int j)
    {
        if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) || (i == height - 1 && j == width - 1) || (i == height - 1 && j == width - 2) || (i == height - 2 && j == width - 1))
            return false;
        else
            return true;
    }
    bool CreaturesTab::isUnique (std::vector<int>& listeTmp, int i, int j)
    {
        for (int k = 0; k < (int)(listeTmp.size()/2); k++)
        {
            if (listeTmp[2*k] == i && listeTmp[2*k + 1] == j)
                return false;
        }
        
        return true;
    }
}