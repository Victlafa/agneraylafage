/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Player.h"

namespace state{
    
    /// Builder :
      
      Player::Player()
      {
          cellNbr = 0;
          zonesNbr = 0;
          conquestPoints = 0;
          creaturesLeft = 0;
          speCellsNames = new std::vector<std::string>(4);
          if (speCellsNames == NULL)
              throw std::bad_alloc("L'attribut speCellsNames du joueur doit être instanciée.");
          xLastCell = 0;
          yLastCell = 0;
          Identify = 0;
          std::cout << "Le joueur a été initialisé correctement." << std::endl;
      }
    
    /// Setters and Getters :
      
        int Player::getCellsNbr() {
            return cellNbr;
        }

        int Player::getZonesNbr() {
            return zonesNbr;
        }

        int Player::getConquestPoints() {
            return conquestPoints;
        }

        int Player::getCreaturesLeft() {
            return creaturesLeft;
        }

        std::vector<std::string> Player::getSpeCellsNames() {
            return speCellsNames;
        }

        int Player::getXLastCell() {
            return xLastCell;
        }

        int Player::getYLastCell() {
            return yLastCell;
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

            // Si on souhaite ajouter un nom dans la liste :
            if (add)
                speCellsNames.push_back(name);

                // Si au contraire on souhaite retirer un nom de la liste :
            else if (!add && speCellsNames.size() != 0) {
                int index = 0;
                // On doit chercher l'index correspondant à ce nom dans la liste :

                for (int i = 0; i < speCellsNames.size(); i++) {
                    if (speCellsNames.at(i) = name) {
                        index = i;
                        // Quand on a trouvé le bon index, on sort de la boucle for :
                        break;
                    }
                }

                // Si on a pas trouvé d'index correspondant, on lève une exception :
                if (index == 0)
                    throw std::invalid_argument("Le nom que vous souhaitez supprimer de la liste ne s'y trouve pas !");

                speCellsNames.erase(index);
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

        ClanNameID Player::getIdentify() const {
            return Identify;
        }

        void Player::setIdentify(ClanNameID Identify) {
            Identify = Identify;
        }
    
};