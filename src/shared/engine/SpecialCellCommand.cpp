/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SpecialCellCommand.h"
#include <iostream>

namespace engine
{
    SpecialCellCommand::SpecialCellCommand (int init_i, int init_j, int final_i, int final_j, int player, std::string type) : initPos(2), finalPos(2)
    {
        initPos[0] = init_i;
        initPos[1] = init_j;
        finalPos[0] = final_i;
        finalPos[1] = final_j;
        this->player = player;
        this->type = type;
        fight.reset(new Fight(init_i,init_j,final_i,final_j,player));
        
    }
    
    bool SpecialCellCommand::isSpecial (state::State& state)
    {
        // On verifie si la cellule est speciale ou pas
        int elemtype = (int)state.getGrid()->get(initPos[0],initPos[1])->getElemType();
        if (elemtype >= 8 && elemtype <= 11)
            return true;
        else
            return false;
    }
    
    CommandTypeID SpecialCellCommand::getTypeID () const { return CommandTypeID::SPECIAL; }
    
    void SpecialCellCommand::execute (state::State& state)
    {
        if (type == "sky")
            skyPower(state);
        else if (type == "candy")
            sugarPower(state);
        else if (type == "barbecue" || type == "pool")
            bbqPoolPower(state);
        else
            throw std::runtime_error("Le type de cellule speciale donné en argument de SpecialCellCommand::execute est erroné");
    }
    
    // Setters and Getters
    const std::vector<int>& SpecialCellCommand::getInitPos() const { return initPos; }
    void SpecialCellCommand::setInitPos(const std::vector<int>& initPos) {
        this->initPos[0] = initPos[0];
        this->initPos[1] = initPos[1];
    }
    const std::vector<int>& SpecialCellCommand::getFinalPos() const { return finalPos; }
    void SpecialCellCommand::setFinalPos(const std::vector<int>& finalPos)
    {
        this->finalPos[0] = finalPos[0];
        this->finalPos[1] = finalPos[1];
    }
    int SpecialCellCommand::getPlayer() const { return player; }
    void SpecialCellCommand::setPlayer(int player) { this->player = player; }
    
    // On peut engager un combat contre l'adversaire sans que sa case soit adjacente à la notre
    void SpecialCellCommand::skyPower (state::State& state)
{
        // Si la case de destination est occupée par l'adversaire, on engage un combat
        if (state.getCharacters()->isOccupiedByOpp(finalPos[0], finalPos[1], state.getPlayer(player).get())) {
            fight->execute(state);
            // On deplace l'attaquant s'il est gagnant
            state.getCharacters()->moveElement(initPos[0], initPos[1], finalPos[0], finalPos[1], fight->getWinner());
        } 
        // S'il n'y a pas d'adversaire sur la case destination, on procede directement à un deplacement
        else
            state.getCharacters()->moveElement(initPos[0], initPos[1], finalPos[0], finalPos[1], 0);

        // On associe la case d'arrivée au joueur gagnant
        if (fight->getWinner() == 1 || fight->getWinner() == 2) {
            std::cout << "Joueur gagnant : " << state.getPlayer(fight->getWinner()).get() << std::endl;
            state.getCharacters()->get(finalPos[0], finalPos[1])->setPlayer(state.getPlayer(fight->getWinner()).get());
        }
    }
    
    // On ajoute trois groupes de creatures dans la reserve du joueur utilisant le pouvoir, groupes qu'il pourra deployer lors de sa prochaine phase de renfort
    void SpecialCellCommand::sugarPower (state::State& state) 
    {
        state.getPlayer(player)->setCreaturesLeft(state.getPlayer(player)->getCreaturesLeft() + 3);
    }
    
    void SpecialCellCommand::bbqPoolPower (state::State& state) 
    {
        // Si la case de destination est occupée par l'adversaire, on engage un combat
        if (state.getCharacters()->isOccupiedByOpp(finalPos[0], finalPos[1], state.getPlayer(player).get())) {
            
            fight->execute(state);
            
        // On deplace l'attaquant s'il est gagnant
            state.getCharacters()->moveElement(initPos[0], initPos[1], finalPos[0], finalPos[1], fight->getWinner());

            // On associe la case d'arrivée au joueur gagnant
            if (fight->getWinner() == 1 || fight->getWinner() == 2) {
                std::cout << "Joueur gagnant : " << state.getPlayer(fight->getWinner()).get() << std::endl;
                state.getCharacters()->get(finalPos[0], finalPos[1])->setPlayer(state.getPlayer(fight->getWinner()).get());
            }
            
        } 
        // S'il n'y a pas d'adversaire sur la case destination, on le signale au joueur attaquant
        else
            std::cout << "La case choisie pour appliquer le pouvoir barbecue/piscine ne contient pas de creatures adverses !" << std::endl;
           

        
    }
}