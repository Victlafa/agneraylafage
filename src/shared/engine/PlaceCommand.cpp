/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PlaceCommand.h"
#include <iostream>
#include "../shared/state/CreaturesTab.h"

using namespace std;
using namespace state;

namespace engine{
    
    //PlaceCommand::PlaceCommand () {}
    PlaceCommand::PlaceCommand (int i_final, int j_final, int player, state::ID type) : finalPos(2) {
        finalPos[0] = i_final;
        finalPos[1] = j_final;
        this->player = player;
        this->creaType = type;
    }
    CommandTypeID PlaceCommand::getTypeID () const { return CommandTypeID::PLACE; }
    
    void PlaceCommand::execute (state::State& state) {
        
        // On verifie que le joueur dispose encore en stock de creatures à placer sur la grille
        if (state.getPlayer(player)->getCreaturesLeft() > 0)
        {
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
        }
        // Sinon, on leve une exception
        else
            throw std::runtime_error("PlaceCommand::execute - Le joueur ne dispose plus dans son stock de creatures à placer !");
        
    }
    
    // Setters and Getters
    int getPos() const {return pos;}
    void setPos(int pos) {this->pos = pos;}
}