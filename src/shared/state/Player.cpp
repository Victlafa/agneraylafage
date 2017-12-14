/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Player.h"
#include <iostream>

namespace state{
    
    /// Builder :
      
      Player::Player() : speCellsNames()
      {
          cellNbr = 0;
          zonesNbr = 0;
          conquestPoints = 0;
          creaturesLeft = 0;
          xLastCell = 0;
          yLastCell = 0;
      }
      
      Player::Player(CreaturesID type) : clanName(type), speCellsNames()
      {
          cellNbr = 3;
          zonesNbr = 0;
          conquestPoints = 0;
          creaturesLeft = 3;
          xLastCell = 0;
          yLastCell = 0;
      }
      
        Player::~Player(){
        //std::cout << "Appel du destructeur de Player" << std::endl;
        }
    
    /// Setters and Getters :
      
        int Player::getCellNbr() const{
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

        const std::vector<std::string>& Player::getSpeCellsNames() const{
            return speCellsNames;
        }

        int Player::getXLastCell() const{
            return xLastCell;
        }

        int Player::getYLastCell() const{
            return yLastCell;
        }

        void Player::setCellNbr(int count) {
            cellNbr = count;
        }

        void Player::setZonesNbr(int count) {
            zonesNbr = count;
        }

        void Player::setConquestPoints(int count) {
            conquestPoints = count;
        }

        void Player::setCreaturesLeft(int count) {
            creaturesLeft = (count > 6) ? 6 : count;
        }

        void Player::decreaseCreaLeft() {
            creaturesLeft -= 1;
        }

        /// modifySpeCellsNames : 
        /// Permet de modifier la liste des noms des cellules spéciales que le joueur détient. (ajout ou retrait)
        /// Args d'entrée : nom de la cellule (name) et un booléen (add).
        void Player::modifySpeCellsNames(std::string name, bool add) {
            size_t initSize = speCellsNames.size();

            // Si on souhaite ajouter un nom dans la liste :
            if (add)
                speCellsNames.push_back(name);

            // Si au contraire on souhaite retirer un nom de la liste :
            else if (!add && speCellsNames.size() != 0) {
                
                // On doit chercher le nom correspondant dans la liste :

                for (int i = 0; i < (int)initSize; i++) {
                    if (speCellsNames.at(i) == name) {
                        // Quand on a trouvé le bon nom, on le remplace par "" et on sort de la boucle for :
                        speCellsNames.erase(speCellsNames.begin()+i);
                        break;
                    }
                }

                // Si on a pas trouvé d'index correspondant, on lève une exception :
                if (speCellsNames.size() == initSize)
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
        
        CreaturesID Player::getClanName() const {
            //std::cout << "Player.cpp : clan du joueur : " << (CreaturesID)this->clanName << std::endl;
            return this->clanName;
        }

        void Player::setClanName(CreaturesID Identify) {
            this->clanName = Identify;
        }
        
        void Player::setSpeCellsNames(const std::vector<std::string>& speCellsNames)
        {
            // On vide la liste initiale des noms de cellules speciales
            this->speCellsNames.clear();
            
            // On ajoute les nouveaux
            for (auto elem : speCellsNames)
            {
                this->speCellsNames.push_back(elem);
            }
        }
    
};