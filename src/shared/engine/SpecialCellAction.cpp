/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SpecialCellAction.h"
#include <iostream>

namespace engine
{
    SpecialCellAction::SpecialCellAction (int init_i, int init_j, int final_i, int final_j, int player, std::string type) : initPos(2), finalPos(2)
    {
        initPos[0] = init_i;
        initPos[1] = init_j;
        finalPos[0] = final_i;
        finalPos[1] = final_j;
        this->player = player;
        this->type = type;
        fight.reset(new Fight(init_i,init_j,final_i,final_j,player));
        
    }
    
    // On verifie si le joueur qui souhaite utiliser la capacite speciale detient bien cette capa !
    bool SpecialCellAction::isOwner (state::State& state)
    {
        std::vector<std::string> listeCapas = state.getPlayer(player)->getSpeCellsNames();
        
        // On parcourt la liste des capas speciales du joueur
        for (auto elem : listeCapas)
        {
            if (elem == type)
                return true;
        }
        
        return false;
    }
    
    void SpecialCellAction::apply (state::State& state)
    {
        // On verifie si le joueur utilisant la capa speciale en jeu dispose bien de cette capa !
        if (isOwner(state))
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
        
        else
            throw std::runtime_error("Le joueur ne peut pas utiliser la capa selectionnee !");
    }
    
    // On peut engager un combat contre l'adversaire sans que sa case soit adjacente à la notre
    void SpecialCellAction::skyPower (state::State& state)
    {
        std::cout << "SpecialCellCommand::skyPower - execution" << std::endl;
        
        // Si la case de destination est occupée par l'adversaire, on engage un combat
        if (state.getCharacters()->isOccupiedByOpp(finalPos[0], finalPos[1], state.getPlayer(player).get())) {
            fight->apply(state);
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
    void SpecialCellAction::sugarPower (state::State& state) 
    {
        std::cout << "SpecialCellCommand::sugarPower - execution" << std::endl;
        
        state.getPlayer(player)->setCreaturesLeft(state.getPlayer(player)->getCreaturesLeft() + 3);
    }
    
    // On supprime directement trois creatures d'un groupe de creatures adverse selectionné
    void SpecialCellAction::bbqPoolPower (state::State& state) 
    {
        std::cout << "SpecialCellCommand::bbqPoolPower - execution" << std::endl;
        
        // On verifie s'il existe bien un groupe de creatures dans la case selectionnee
        if (state.getCharacters()->isOccupiedByOpp(finalPos[0], finalPos[1], state.getPlayer(player).get()))
        {
            // Dans ce cas là on procède à l'elimination des creatures (paix à leur ame !)
            int oldNbr = state.getCharacters()->get(finalPos[0], finalPos[1])->getCreaturesNbr();
            
            // Si le groupe de creatures comporte 3 creatures ou plus
            if (oldNbr >= 3)
                // On enleve trois creatures
                state.getCharacters()->get(finalPos[0], finalPos[1])->setCreaturesNbr(oldNbr - 3);
            else
                // On fait tomber le nbre de creatures à zero
                state.getCharacters()->get(finalPos[0], finalPos[1])->setCreaturesNbr(0);
        }
        
        else
            throw std::runtime_error("SpecialCellCommand::bbqPoolPower - La case selectionnee ne contient pas de creatures !");
        
    }
    
    void SpecialCellAction::undo (state::State& etat)
    {
        
    }
    
    
    // Setters and Getters
    const std::shared_ptr<Fight>& SpecialCellAction::getFight() const { return fight; }
    void SpecialCellAction::setFight(const std::shared_ptr<Fight>& fight) {this->fight = fight; }
    const std::vector<int>& SpecialCellAction::getInitPos() const { return initPos; }
    void SpecialCellAction::setInitPos(const std::vector<int>& initPos) {
        this->initPos[0] = initPos[0];
        this->initPos[1] = initPos[1];
    }
    const std::vector<int>& SpecialCellAction::getFinalPos() const { return finalPos; }
    void SpecialCellAction::setFinalPos(const std::vector<int>& finalPos)
    {
        this->finalPos[0] = finalPos[0];
        this->finalPos[1] = finalPos[1];
    }
    int SpecialCellAction::getPlayer() const { return player; }
    void SpecialCellAction::setPlayer(int player) { this->player = player; }
    const std::string& SpecialCellAction::getType () const { return type; }
    void SpecialCellAction::setType(const std::string& type) {this->type = type; }
}