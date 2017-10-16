/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Player.h"
#include <iostream>

namespace state{
    
    /// Builder :
      
      Player::Player()
      {
          cellNbr = 0;
          zonesNbr = 0;
          conquestPoints = 0;
          creaturesLeft = 0;
          xLastCell = 0;
          yLastCell = 0;
          
          try
          {
              speCellsNames = new std::vector<std::string>();
              allCreatures = new std::vector<CreaturesGroup>();
          }
          
          catch(std::bad_alloc &e)
          {
              std::cerr << e.what() << std::endl;
          }
          
          //std::cout << "Le joueur a été initialisé correctement." << std::endl;
      }
      
        Player::~Player(){
            delete this;
        }
    
    /// Setters and Getters :
      
        int Player::getCellsNbr() const{
            return cellNbr;
        }

        int Player::getZonesNbr() const{
            return zonesNbr;
        }

        int Player::getConquestPoints() const{
            return conquestPoints;
        }

        int Player::getCreaturesLeft() const{
            return creaturesLeft;
        }

        std::vector<std::string>* Player::getSpeCellsNames() const{
            return speCellsNames;
        }

        int Player::getXLastCell() const{
            return xLastCell;
        }

        int Player::getYLastCell() const{
            return yLastCell;
        }
        
        std::vector<CreaturesGroup>* Player::getAllCreatures () const{
            return this->allCreatures;
        }

        void Player::setCellsNbr(int count) {
            cellNbr = count;
        }

        void Player::setZonesNbr(int count) {
            zonesNbr = count;
        }

        void Player::setConquestPts(int count) {
            conquestPoints = count;
        }

        void Player::setCreaLeft(int count) {
            creaturesLeft = count;
        }

        void Player::decreaseCreaLeft() {
            creaturesLeft -= 1;
        }

        /// modifySpeCellsNames : 
        /// Permet de modifier la liste des noms des cellules spéciales que le joueur détient. (ajout ou retrait)
        /// Args d'entrée : nom de la cellule (name) et un booléen (add).
        void Player::modifySpeCellsNames(std::string name, bool add) {
            size_t initSize = speCellsNames->size();

            // Si on souhaite ajouter un nom dans la liste :
            if (add)
                speCellsNames->push_back(name);

            // Si au contraire on souhaite retirer un nom de la liste :
            else if (!add && speCellsNames->size() != 0) {
                
                // On doit chercher le nom correspondant dans la liste :

                for (int i = 0; i < (int)initSize; i++) {
                    if (speCellsNames->at(i) == name) {
                        // Quand on a trouvé le bon nom, on le remplace par "" et on sort de la boucle for :
                        speCellsNames->erase(speCellsNames->begin()+(i-1),speCellsNames->begin()+i);
                        std::cout << "Un element a ete retire de la liste" << std::endl;
                        break;
                    }
                }

                // Si on a pas trouvé d'index correspondant, on lève une exception :
                if (speCellsNames->size() == initSize)
                    throw std::invalid_argument("Aucun nom n'a été supprimé de la liste !");

            }
            else {
                // On arrive ici seulement si la liste est vide et qu'on veut supprimer un élément, on lève donc une exception :
                throw std::length_error("Impossible de supprimer un nom de la liste car elle est vide !");
            }

        }

        void Player::setXLastCell(int x) {
            xLastCell = x;
        }

        void Player::setYLastCell(int y) {
            yLastCell = y;
        }
        
        void Player::setAllCreatures (std::vector<CreaturesGroup>* creaList){
            this->allCreatures = creaList;
        }
        
        void Player::setAllCreatures (bool add, CreaturesGroup group){
            size_t initSize = allCreatures->size();

            // Si on souhaite ajouter un groupe de créatures dans la liste :
            if (add)
                allCreatures->push_back(group);

            // Si au contraire on souhaite retirer un groupe de la liste :
            else if (!add && allCreatures->size() != 0) {
                
                // On doit chercher le groupe correspondant dans la liste :

                for (auto Iter = allCreatures->begin(); Iter != allCreatures->end(); Iter++) {
                    if (*Iter == group) {
                        // Quand on a trouvé le bon groupe, on le supprime et on sort de la boucle for :
                        allCreatures->erase(Iter);
                        break;
                    }
                }

                // Si on a pas trouvé d'index correspondant, on lève une exception :
                if (allCreatures->size() == initSize)
                    throw std::invalid_argument("Aucun groupe n'a été supprimé de la liste !");

            }
            else {
                // On arrive ici seulement si la liste est vide et qu'on veut supprimer un élément, on lève donc une exception :
                throw std::length_error("Impossible de supprimer un groupe de la liste car elle est vide !");
            }

        }
        
        
        CreaturesID Player::getClanName() const {
            return this->clanName;
        }

        void Player::setClanName(CreaturesID Identify) {
            this->clanName = Identify;
        }
    
};