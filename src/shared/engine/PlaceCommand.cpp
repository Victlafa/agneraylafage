/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PlaceCommand.h"
#include <iostream>

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
            // Si la case de destination est occupée par l'adversaire, on leve une exception
            if (state.getCharacters()->isOccupiedByOpp(finalPos[0], finalPos[1], state.getPlayer(player).get()))
                throw std::runtime_error("La case où le joueur souhaite placer sa creature est occupée par l'adversaire !");
                // De meme si la case de destination appartient au joueur mais qu'elle comporte deja 5 creatures
            else if (state.getCharacters()->get(finalPos[0], finalPos[1])->getCreaturesNbr() == 5)
                throw std::runtime_error("La case où le joueur souhaite placer sa creature possède deja 5 creatures !");
                // Dans les autres cas, on peut placer une nouvelle creature
            else {
                // On place la creature dans la grille
                state.getCharacters()->placeElement(finalPos[0], finalPos[1], creaType);
                // On lui associe le joueur qui l'a placee
                state.getCharacters()->get(finalPos[0], finalPos[1])->setPlayer(state.getPlayer(player).get());
            }
        }
        // Sinon, on leve une exception
        else
            throw std::runtime_error("Le joueur ne dispose plus dans son stock de creatures à placer !");
        
    }
    
    // Setters and Getters
    const std::vector<int>& PlaceCommand::getFinalPos() const { return finalPos; }
    void PlaceCommand::setFinalPos(const std::vector<int>& finalPos) {
        this->finalPos[0] = finalPos[0];
        this->finalPos[1] = finalPos[1];
    }
    int PlaceCommand::getPlayer() const {return player;}
    void PlaceCommand::setPlayer(int player) { this->player = player;}
    state::ID PlaceCommand::getCreaType() const { return creaType; }
    void PlaceCommand::setCreaType(state::ID creaType) {this->creaType = creaType; }
}