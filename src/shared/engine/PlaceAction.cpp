/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PlaceAction.h"
#include <iostream>
#include "../state/CreaturesTab.h"
#include "../state/State.h"

using namespace state;
using namespace std;

namespace engine{
    
    PlaceAction::PlaceAction (int i_final, int j_final, int player, state::ID type) : finalPos(2) {
        finalPos[0] = i_final;
        finalPos[1] = j_final;
        this->player = player;
        this->creaType = type;
    }
    
    void PlaceAction::apply (state::State& state) {
        
        // On verifie que le joueur dispose encore en stock de creatures à placer sur la grille
        if (state.getPlayer(player)->getCreaturesLeft() > 0)
        {
            cout << "PlaceAction::apply - nombre de creatures à placer : " << state.getPlayer(player)->getCreaturesLeft() << endl;
            
            // Si c'est le cas on cherche à placer une creature
            CreaturesTab* creaTab = state.getCharacters().get();
            
            // Si la case de destination est occupée par l'adversaire, on leve une exception
            if (creaTab->isOccupiedByOpp(finalPos[0], finalPos[1], state.getPlayer(player).get()))
                throw std::runtime_error("PlaceCommand::execute - La case où le joueur souhaite placer sa creature est occupée par l'adversaire !");
                // De meme si la case de destination appartient au joueur mais qu'elle comporte deja 5 creatures
            else if (creaTab->get(finalPos[0], finalPos[1]).get() != NULL && creaTab->get(finalPos[0], finalPos[1])->getCreaturesNbr() == 5)
                throw std::runtime_error("PlaceCommand::execute - La case où le joueur souhaite placer sa creature possède deja 5 creatures !");
                // Dans les autres cas, on peut placer une nouvelle creature
            else {
                // On place la creature dans la grille
                creaTab->placeElement(finalPos[0], finalPos[1], creaType);
                // On lui associe le joueur qui l'a placee
                creaTab->get(finalPos[0], finalPos[1])->setPlayer(state.getPlayer(player).get());
                //cout << "PlaceCommand::execute - Une creature du joueur " << state.getPlayer(player).get() << "a été placée en " << finalPos[0] << "," << finalPos[1] << endl;
                // On diminue le nombre restant de creatures du joueur
                state.getPlayer(player)->decreaseCreaLeft();
                //cout << "Nombre de creatures restantes : " << state.getPlayer(player)->getCreaturesLeft() << endl;
                // Si la cellule ne contient qu'une creature, cela signifie que le joueur vient de prendre possession de la cellule
                // On augmente donc le nombre de cellules du joueur concerne 
                if (creaTab->get(finalPos[0], finalPos[1])->getCreaturesNbr() == 1)
                {
                    int cellNbr = creaTab->get(finalPos[0], finalPos[1])->getPlayer()->getCellNbr();
                    creaTab->get(finalPos[0], finalPos[1])->getPlayer()->setCellNbr(cellNbr + 1);
                }
                
            }
            
            cout << "PlaceAction::apply - un placement a été effectué !" << endl;
        }
        // Sinon, on leve une exception
        else
            throw std::runtime_error("PlaceCommand::execute - Le joueur ne dispose plus dans son stock de creatures à placer !");
        
    }
    
    void PlaceAction::undo (state::State& etat)
    {
        // On supprime une creature du groupe de la cellule concernée
        // On verifie que la cellule est bien non vide
        if (etat.getCharacters()->get(finalPos[0],finalPos[1]).get())
        {
            int creaNbr = etat.getCharacters()->get(finalPos[0],finalPos[1])->getCreaturesNbr();
            etat.getCharacters()->get(finalPos[0],finalPos[1])->setCreaturesNbr(creaNbr - 1);
            
            // Si la cellule ainsi modifiee devient vide
            if (etat.getCharacters()->get(finalPos[0],finalPos[1])->getCreaturesNbr() <= 0)
            {
                // On supprime definitivement le groupe de creatures
                etat.getCharacters()->set(NULL,finalPos[0],finalPos[1]);
                // On diminue le nbre de cellules du joueur qui perd sa cellule
                etat.getPlayer(player)->setCellNbr(etat.getPlayer(player)->getCellNbr() - 1);
            }
            
            // On augmente le nombre restant de creatures du joueur
            etat.getPlayer(player)->setCreaturesLeft(etat.getPlayer(player)->getCreaturesLeft() + 1);
                
        }
        else
            throw std::runtime_error("PlaceAction::undo - impossible de supprimer une creature de la cellule car celle-ci est deja vide !");
    }
    
    // Setters and Getters
    const std::vector<int>& PlaceAction::getFinalPos() const { return finalPos; }
    void PlaceAction::setFinalPos(const std::vector<int>& finalPos) {
        this->finalPos[0] = finalPos[0];
        this->finalPos[1] = finalPos[1];
    }
    int PlaceAction::getPlayer() const {return player;}
    void PlaceAction::setPlayer(int player) { this->player = player;}
    state::ID PlaceAction::getCreaType() const { return creaType; }
    void PlaceAction::setCreaType(state::ID creaType) {this->creaType = creaType; }
}