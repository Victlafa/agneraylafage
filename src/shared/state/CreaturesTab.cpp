/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CreaturesTab.h"
#include "CreaturesID.h"
#include "CreaturesGroup.h"
#include "ID.h"
#include <iostream>

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
    
    // Effectue un deplacement entre deux cellules et renvoie les nombres de creatures qu'elles possedaient avant le deplacement
    std::vector<int> CreaturesTab::moveElement (int i_elem, int j_elem, int new_i_elem, int new_j_elem, int fight)
    {
        std::vector<int> oldCreaNbr(2);
        
        // Nbre de creatures de la cellule attaquante
        int creaNbrAtt = 0;
        Player* fighter = nullptr;
        if (this->get(i_elem,j_elem) != NULL && this->get(i_elem,j_elem)->getCreaturesNbr() != 0)
        {
            creaNbrAtt = this->get(i_elem,j_elem)->getCreaturesNbr();
            fighter = this->get(i_elem,j_elem)->getPlayer();
        }
            
        else
            throw std::runtime_error("CreaturesTab::moveElement - Il n'y a pas de groupe de creatures dans la cellule designee comme attaquante !");
                
        // Nbre de creatures de la cellule destination
        int creaNbrDef = 0;
        Player* defender = nullptr;
        if (this->get(new_i_elem,new_j_elem) != NULL)
        {
            creaNbrDef = this->get(new_i_elem,new_j_elem)->getCreaturesNbr();
            defender = this->get(new_i_elem,new_j_elem)->getPlayer();
        }
           
        oldCreaNbr[0] = creaNbrAtt;
        oldCreaNbr[1] = creaNbrDef;
        
        std::cout << "CreaturesTab::moveElement - Nombre de creatures de la cellule de départ avant deplacement : " << creaNbrAtt << std::endl;
        std::cout << "CreaturesTab::moveElement - Nombre de creatures de la cellule de destination avant deplacement : " << creaNbrDef << std::endl;
        
        // On verifie si le deplacement est possible ou non
        
        // La case destination est-elle autorisée ?
        if (isEnable(new_i_elem,new_j_elem))
        {      
            // La case destination est-elle vide ?
            if (this->get(new_i_elem,new_j_elem) == NULL)
            {
                // Si c'est le cas, on procède au déplacement
                Element* newGroup;
                // On cree un nouveau groupe que l'on place dans la case vide avec N - 1 creatures SAUF si la case de depart n'en contenait qu'une !
                if (creaNbrAtt > 1)
                {
                    newGroup = new CreaturesGroup(this->get(i_elem, j_elem)->getElemType(),creaNbrAtt - 1,fighter);
                    // On fixe le nbre de creatures de la case attaquante à 1
                    this->get(i_elem,j_elem)->setCreaturesNbr(1);
                    // On augmente le nombre de cellules du joueur attaquant
                    fighter->setCellNbr(fighter->getCellNbr() + 1);
                    // On augmente le nbre de creatures restant pour phase de renfort du joueur
                    fighter->setCreaturesLeft(fighter->getCreaturesLeft() + 1);
                }
                
                else
                {
                    newGroup = new CreaturesGroup(this->get(i_elem, j_elem)->getElemType(),1,fighter);
                    // On detruit le groupe de creatures de la cellule attaquante
                    this->set(nullptr,i_elem,j_elem);
                    // Ici on ne modifie pas le nombre de cellules du joueur attaquant car il en perd une en prenant la cellule destination vide
                    
                    if (this->get(i_elem,j_elem).get() != nullptr)
                        throw std::runtime_error("CreaturesTab::moveElement ligne 70 - la cellule attaquante n'a pas ete detruite !");
                        
                }
                
                this->set(newGroup,new_i_elem,new_j_elem);
                
                // On verifie si le deplacement a ete effectue
                if (this->get(new_i_elem,new_j_elem) == NULL && this->get(new_i_elem,new_j_elem)->getCreaturesNbr() != 0)
                    throw std::runtime_error("CreaturesTab::moveElement - le déplacement vers une case vide n'a pas été effectué !");
                
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
                        
                        // Nbre futur de creatures sur la case defense - cas où la case d'attaque comporte plusieurs creatures
                        int newDef_several = ((creaNbrDef + creaNbrAtt - 1) <= 5) ? (creaNbrDef + creaNbrAtt - 1) : 5;
                        // Nbre futur de creatures sur la case defense - cas où la case d'attaque comporte une seule creature
                        int newDef_one = ((creaNbrDef + 1) <= 5) ? (creaNbrDef + 1) : 5;
                        
                        // On fixe le nbre de creatures de la case destination
                        (creaNbrAtt != 1) ? this->get(new_i_elem,new_j_elem)->setCreaturesNbr(newDef_several) : this->get(new_i_elem,new_j_elem)->setCreaturesNbr(newDef_one);
                        
                        // Si la case d'attaque va etre detruite, on decremente le nombre de cellules de l'attaquant
                        if (creaNbrAtt == 1)
                        {
                            fighter->setCellNbr(fighter->getCellNbr() - 1);
                            fighter->decreaseCreaLeft();
                        }
                            
                        // On fixe le nouveau nbre de creatures de la case de depart (on la detruit si elle est videe lors du deplacement)
                        (creaNbrAtt != 1) ? this->get(i_elem,j_elem)->setCreaturesNbr(creaNbrAtt - newDef_several + creaNbrDef) : this->set(nullptr,i_elem,j_elem);
                        
                    }
                        
                    // Le joueur 1 ou le joueur 2 a gagné le combat sans aucune pitie en etant l'attaquant
                    else if (fight == 1 || fight == 2)
                    {
                        // On decremente le nombre de cellules appartenant au joueur defenseur avant de detruire sa cellule
                        defender->setCellNbr(defender->getCellNbr() - 1);
                        // On detruit les creatures de la case defense en les remplaçant par celles de l'attaquant
                        (creaNbrAtt != 1) ? this->set(new CreaturesGroup(this->get(i_elem, j_elem)->getElemType(), creaNbrAtt - 1, this->get(i_elem, j_elem)->getPlayer()), new_i_elem, new_j_elem) : this->set(new CreaturesGroup(this->get(i_elem, j_elem)->getElemType(),1, this->get(i_elem, j_elem)->getPlayer()), new_i_elem, new_j_elem);
                        
                        // On fixe le nouveau nbre de creatures de la case de depart. Si la case de depart est destinee a etre videe, on la detruit
                        (creaNbrAtt != 1) ? this->get(i_elem,j_elem)->setCreaturesNbr(1) : this->set(nullptr,i_elem,j_elem);
                        // Si la case d'attaque n'est pas detruite, on incremente le nombre de cellules de l'attaquant
                        if (creaNbrAtt != 1)
                        {
                            fighter->setCellNbr(fighter->getCellNbr() + 1);
                            // On augmente le nbre de creatures restant pour phase de renfort du joueur
                            fighter->setCreaturesLeft(fighter->getCreaturesLeft() + 1);
                        }
                        
                        defender->decreaseCreaLeft();
                            
                    }
                        
                    // Le defenseur a gagné ou il y a egalite : dans ce cas là le nombre de creatures en attaque tombe à 1 (et les nbres de cellules ne sont pas modifies)
                    else
                        this->get(i_elem, j_elem)->setCreaturesNbr(1);

                }
                
                else
                    throw std::runtime_error("CreaturesTab::moveElement - Le déplacement n'a pas pu etre effectué (mauvaise valeur de l'argument fight, doit etre egal à 0,1,2 ou 3 !");
            }
        }
        
        else
            throw std::runtime_error("CreaturesTab::moveElement - Le déplacement n'a pas pu etre effectué car la case de destination est interdite !"); 
        
        return oldCreaNbr;
        
    }
    
    void CreaturesTab::placeElement (int new_i_elem, int new_j_elem, ID creaType)
    {
                
        // La case destination est-elle autorisée ?
        if (isEnable(new_i_elem,new_j_elem))
        {
            // La case destination est-elle vide ?
            if (this->get(new_i_elem,new_j_elem) == NULL)
            {
                // Si c'est le cas, on procède au placement
                
                // On cree un nouveau groupe que l'on place dans la case vide avec 1 creature
                Element* newGroup = new CreaturesGroup(creaType,1,NULL);
                this->set(newGroup,new_i_elem,new_j_elem);
                
                // On verifie que le placement a bien ete effectue
                if (this->get(new_i_elem,new_j_elem) == NULL)
                    throw std::runtime_error("CreaturesTab::placeElement - Le placement dans une case vide n'a pas ete effectue !");
                
            }
            
            // Elle est occupee par le joueur qui souhaite placer une creature
            else if ((ID)(this->get(new_i_elem,new_j_elem))->getPlayer()->getClanName() == creaType)
            {
                // On ajoute une creature au groupe existant
                int nbrCrea = this->get(new_i_elem, new_j_elem)->getCreaturesNbr();
                this->get(new_i_elem, new_j_elem)->setCreaturesNbr(nbrCrea + 1);
                
                // On verifie que le placement a bien ete effectue
                if (this->get(new_i_elem,new_j_elem) == nullptr)
                    throw std::runtime_error("CreaturesTab::placeElement - Le placement d'une creature du joueur dans une de ses cases n'a pas ete effectue !"); 
            }
            
            // Elle est occupee par l'adversaire
            else
                throw std::runtime_error("CreaturesTab::placeElement - Le joueur ne peut pas placer de creatures de sa reserve dans une cellule adverse !");
        }
        
        else
            throw std::runtime_error("CreaturesTab::placeElement - Le placement n'a pas pu etre effectué car la case de destination est interdite !");
        
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
    
    // renvoie les coordonnees des cellules vides de la grille
    std::vector<int> CreaturesTab::getFreeCells()
    {
        std::vector<int> freeCells;
        
        for (unsigned int i = 0; i < height; i++)
        {
            for (unsigned int j = 0; j < width; j++)
            {
                if (isEnable(i,j) && get(i,j) == nullptr)
                {
                    freeCells.push_back(i);
                    freeCells.push_back(j);
                }
            }
        }
        
        return freeCells;
    }
    
    // On cherche les coordonnees de toutes les cellules appartenant au joueur donne en argument
    std::vector<int> CreaturesTab::getPlayerCells(Player* player)
    {
        std::vector<int> coordonnees;
        
        // On parcourt toutes les cellules de la grille
        for (unsigned int i = 0; i < height; i++) 
        {
            for (unsigned int j = 0; j < width; j++) 
            {
                // Si la case est autorisee et qu'une creature y est presente
                if (isEnable(i,j) && get(i,j).get() != nullptr)
                {
                    // Si ce groupe appartient au joueur designe
                    if (get(i,j)->getPlayer() == player)
                    {
                        //std::cout << "AI::playerCellResearch - la cellule (" << i << "," << j << ") appartient au joueur " << moteur.getPlayer(player).get() << std::endl;
                        // On ajoute les coordonnees à la liste
                        coordonnees.push_back(i);
                        coordonnees.push_back(j);
                    }
                }

            }
        }
        
        return coordonnees;
    }
    
    // renvoie true si le joueur en argument ne peut plus placer de creatures dans ses propres cases
    bool CreaturesTab::isSaturated(Player* player)
    {
        //std::cout << "Entree dans CreaturesTab::isSaturated" << std::endl;
        
        std::vector<int> playerCells = getPlayerCells(player);
        
        // On etudie les nombres de creatures de tous les groupes du joueur
        // Si on en trouve au moins un qui comporte moins de 5 creatures, on sort de la boucle for en renvoyant false
        for (int i = 0; i < (int)(playerCells.size()/2); i++)
        {
            if (get(playerCells[2*i],playerCells[2*i+1])->getCreaturesNbr() != 5)
            {
                //std::cout << "Sortie false de CreaturesTab::isSaturated" << std::endl;
                return false;
            }
                
        }
        
        //std::cout << "Sortie true de CreaturesTab::isSaturated" << std::endl;
        return true;
    }
}