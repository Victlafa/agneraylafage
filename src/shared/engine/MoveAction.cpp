/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MoveAction.h"
#include <iostream>
#include "../state/CreaturesGroup.h"

using namespace state;

namespace engine{
    
    MoveAction::MoveAction() {}
    MoveAction::MoveAction (int init_i, int init_j, int final_i, int final_j, int player) : initCreaturesNbr(2), initPos(2), finalPos(2) {
        initPos[0] = init_i;
        initPos[1] = init_j;
        finalPos[0] = final_i;
        finalPos[1] = final_j;
        this->player = player;
        fight.reset(new Fight(init_i,init_j,final_i,final_j,player));
        isThereFight = false;
        
        
    }
    bool MoveAction::getIsThereFight () { return isThereFight; }
    const std::vector<int>& MoveAction::getInitCreaturesNbr () const { return initCreaturesNbr; }
    void MoveAction::apply (state::State& state) {

        // Si la case de destination est occupée par l'adversaire, on engage un combat
        if (state.getCharacters()->isOccupiedByOpp(finalPos[0], finalPos[1], state.getPlayer(player).get())) {
            std::cout << "MoveAction::apply - Un combat commence !" << std::endl;
            fight->apply(state);
            initCreaturesNbr = state.getCharacters()->moveElement(initPos[0], initPos[1], finalPos[0], finalPos[1], fight->getWinner());
            isThereFight = true;
        } 
        else
        {
            std::cout << "MoveAction::apply - Il y a déplacement sans combat !" << std::endl;
            // S'il n'y a pas combat on procede directement au deplacement
            initCreaturesNbr = state.getCharacters()->moveElement(initPos[0], initPos[1], finalPos[0], finalPos[1], 0);
        }


        // On associe la case d'arrivée au joueur gagnant
        if (fight->getWinner() == 1 || fight->getWinner() == 2) {
            //std::cout << "MoveCommand::execute - Joueur gagnant : " << state.getPlayer(fight->getWinner()).get() << std::endl;
            std::cout << "MoveAction::apply - Joueur gagnant du combat : " << fight->getWinner() << std::endl;
            state.getCharacters()->get(finalPos[0], finalPos[1])->setPlayer(state.getPlayer(fight->getWinner()).get());
        }
            
    }
    
    void MoveAction::undo (state::State& etat) 
    {
        // On replace les creatures sur les deux cases telles qu'elles etaient avant le combat
        
        // Joueur qui se deplaçait
        // S'il y a un groupe sur la cellule de depart
        Element* attGroup = etat.getCharacters()->get(initPos[0],initPos[1]).get();
        if (attGroup)
        {
            //std::cout << "MoveAction::undo - La case de depart est occupee" << std::endl;
            // On lui associe le joueur concerne
            attGroup->setPlayer(etat.getPlayer(player).get());
            // On lui restitue le bon nombre de creatures
            attGroup->setCreaturesNbr(initCreaturesNbr[0]);
        }
        // Si la case est vide, on créé un nouveau groupe
        else
        {
            //std::cout << "MoveAction::undo - La case de depart n'est plus occupee" << std::endl;
            CreaturesGroup* newGroup = new CreaturesGroup((ID)etat.getPlayer(player)->getClanName(),initCreaturesNbr[0],etat.getPlayer(player).get());
            etat.getCharacters()->set(newGroup,initPos[0],initPos[1]);
        }

        // Si la cellule d'arrivee est occupee apres deplacement
        Element* defGroup = etat.getCharacters()->get(finalPos[0],finalPos[1]).get();
        if (defGroup)
        {
            //std::cout << "MoveAction::undo - La case de destination est occupee" << std::endl;
            // Si elle appartenait à l'adversaire avant deplacement/combat
            if (fight->getCreasDefender() != 0)
            {
                //std::cout << "MoveAction::undo - La case de destination appartenait à l'adversaire" << std::endl;
                // On lui restitue ses creatures
                CreaturesGroup* newGroup = new CreaturesGroup((ID)etat.getPlayer(3-player)->getClanName(),initCreaturesNbr[1],etat.getPlayer(3-player).get());
                etat.getCharacters()->set(newGroup,finalPos[0],finalPos[1]);
            }
            // Si elle appartenait au joueur en cours (il n'y a donc pas eu combat)
            else if (fight->getCreasDefender() == 0 && initCreaturesNbr[1] != 0)
            {
                //std::cout << "MoveAction::undo - La case de destination appartenait au joueur en cours" << std::endl;
                // On lui restitue ses creatures
                defGroup->setPlayer(etat.getPlayer(player).get());
                defGroup->setCreaturesNbr(initCreaturesNbr[1]);
            }
            // Si elle etait vide
            else
            {
                //std::cout << "MoveAction::undo - La case de destination etait vide" << std::endl;
                // On detruit le groupe qui se trouve actuellement dessus
                etat.getCharacters()->set(nullptr,finalPos[0],finalPos[1]);
                
            }
                
                
        }
        // Si elle est vide
        else
        {
            CreaturesGroup* newGroup2;
            
            // Si elle appartenait à l'adversaire avant deplacement/combat
            if (fight->getCreasDefender() != 0)
            {
                // On lui restitue ses creatures
                newGroup2 = new CreaturesGroup((ID)etat.getPlayer(3-player)->getClanName(),fight->getCreasDefender(),etat.getPlayer(3-player).get());
                etat.getCharacters()->set(newGroup2,finalPos[0],finalPos[1]);
            }
            // Si elle appartenait au joueur en cours (il n'y a donc pas eu combat)
            else if (fight->getCreasDefender() == 0 && initCreaturesNbr[1] != 0)
            {
                // On lui restitue ses creatures
                newGroup2 = new CreaturesGroup((ID)etat.getPlayer(player)->getClanName(),initCreaturesNbr[1],etat.getPlayer(player).get());
                etat.getCharacters()->set(newGroup2,finalPos[0],finalPos[1]);
            }
        }  
        
        
    };
    
    // Setters and Getters
    const std::shared_ptr<Fight>& MoveAction::getFight() const {return fight;}
    void MoveAction::setFight(const std::shared_ptr<Fight>& fight) {this->fight = fight;}
    const std::vector<int>& MoveAction::getInitPos() const {return initPos;}
    void MoveAction::setInitPos(const std::vector<int>& initPos) {this->initPos = initPos;}
    const std::vector<int>& MoveAction::getFinalPos() const {return finalPos;}
    void MoveAction::setFinalPos(const std::vector<int>& finalPos) {this->finalPos = finalPos;}
    int MoveAction::getPlayer() const {return player;}
    void MoveAction::setPlayer(int player) {this->player = player;}
    
    
}
