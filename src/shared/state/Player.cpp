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
              throw std::bad_alloc("L'attribut speCellsNames du joueur doit être instancié.");
          
          xLastCell = 0;
          yLastCell = 0;
          identify = 0;
          
          allCreatures = new std::vector<CreaturesGroup>();
          if (allCreatures == NULL)
              throw std::bad_alloc("L'attribut allCreatures du joueur doit être instancié.");
          
          creaturesToPlace = new std::vector<CreaturesGroup>();
          if (creaturesToPlace == NULL)
              throw std::bad_alloc("L'attribut creaturesToPlace du joueur doit être instancié.");
          
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
            return this->identify;
        }

        void Player::setIdentify(ClanNameID Identify) {
            this->identify = Identify;
        }
        
        void Player::setAllCreatures (std::vector<CreaturesGroup> creaList){
            this->allCreatures = creaList;
        }
        
        void Player::setAllCreatures (bool add, CreaturesGroup group){
                    // Si on souhaite ajouter un groupe de créatures dans la liste :
            if (add)
                allCreatures.push_back(group);

                // Si au contraire on souhaite retirer un groupe de la liste :
            else if (!add && allCreatures.size() != 0) {
                int index = 0;
                // On doit chercher l'index correspondant à ce groupe dans la liste :

                for (int i = 0; i < allCreatures.size(); i++) {
                    if (allCreatures.at(i) = group) {
                        index = i;
                        // Quand on a trouvé le bon index, on sort de la boucle for :
                        break;
                    }
                }

                // Si on a pas trouvé d'index correspondant, on lève une exception :
                if (index == 0)
                    throw std::invalid_argument("Le groupe de créatures que vous souhaitez supprimer de la liste ne s'y trouve pas !");

                allCreatures.erase(index);
            }
            else {
                // On arrive ici seulement si la liste est vide et qu'on veut supprimer un élément, on lève donc une exception :
                throw std::length_error("Impossible de supprimer un groupe de créatures de la liste car elle est vide !");
            }
        }
        
        void Player::setCreaToPlace (std::vector<CreaturesGroup> creaList)
        {
            this->creaturesToPlace = creaList;
        }
        
        void Player::setCreaToPlace (bool add, CreaturesGroup group){
            // Si on souhaite ajouter un groupe de créatures dans la liste :
            if (add)
                creaturesToPlace.push_back(group);

                // Si au contraire on souhaite retirer un groupe de la liste :
            else if (!add && creaturesToPlace.size() != 0) {
                int index = 0;
                // On doit chercher l'index correspondant à ce groupe dans la liste :

                for (int i = 0; i < creaturesToPlace.size(); i++) {
                    if (creaturesToPlace.at(i) = group) {
                        index = i;
                        // Quand on a trouvé le bon index, on sort de la boucle for :
                        break;
                    }
                }

                // Si on a pas trouvé d'index correspondant, on lève une exception :
                if (index == 0)
                    throw std::invalid_argument("Le groupe de créatures que vous souhaitez supprimer de la liste ne s'y trouve pas !");

                creaturesToPlace.erase(index);
            }
            else {
                // On arrive ici seulement si la liste est vide et qu'on veut supprimer un élément, on lève donc une exception :
                throw std::length_error("Impossible de supprimer un groupe de créatures de la liste car elle est vide !");
            }
        }
        
        const CreaturesGroup& Player::getPossess() const{
            return this->possess;
        }
        
        void Player::setPossess(const CreaturesGroup& possess){
            this->possess = possess;
        }
    
};