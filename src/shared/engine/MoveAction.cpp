/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MoveAction.h"
#include <iostream>
#include "../state/CreaturesGroup.h"

using namespace state;
using namespace std;

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

        CreaturesTab* creaTab = state.getCharacters().get();
        
        std::cout << "MoveAction::apply - Depart de l'IA n°" << player << " : (" << initPos[0] << "," << initPos[1] << ")" << std::endl;
        std::cout << "MoveAction::apply - Destination de l'IA n°" << player << " : (" << finalPos[0] << "," << finalPos[1] << ")" << std::endl;
            
        // Si la case de destination est occupée par l'adversaire, on engage un combat
        if (creaTab->isOccupiedByOpp(finalPos[0], finalPos[1], state.getPlayer(player).get())) {
            std::cout << "MoveAction::apply - Un combat commence !" << std::endl;
            fight->apply(state);
            initCreaturesNbr = creaTab->moveElement(initPos[0], initPos[1], finalPos[0], finalPos[1], fight->getWinner());
            isThereFight = true;
        } 
        // Si la case de destination est vide
        else
        {
            std::cout << "MoveAction::apply - Il y a déplacement sans combat car la case de destination est vide !" << std::endl;
            // S'il n'y a pas combat on procede directement au deplacement
            initCreaturesNbr = creaTab->moveElement(initPos[0], initPos[1], finalPos[0], finalPos[1], 0);
        }


        // On associe la case d'arrivée au joueur gagnant
        if (fight->getWinner() == 1 || fight->getWinner() == 2) {
            //std::cout << "MoveCommand::execute - Joueur gagnant : " << state.getPlayer(fight->getWinner()).get() << std::endl;
            std::cout << "MoveAction::apply - Joueur gagnant du combat : " << fight->getWinner() << std::endl;
            creaTab->get(finalPos[0], finalPos[1])->setPlayer(state.getPlayer(fight->getWinner()).get());
        }
        
        if (creaTab->get(initPos[0], initPos[1]) != NULL)
            std::cout << "HeuristicAI::run - Nombre de creatures de la cellule de départ apres deplacement : " << creaTab->get(initPos[0], initPos[1])->getCreaturesNbr() << std::endl;
        else
            std::cout << "HeuristicAI::run - Nombre de creatures de la cellule de départ apres deplacement : 0" << std::endl;

        std::cout << "HeuristicAI::run - Nombre de creatures de la cellule de destination apres deplacement : " << creaTab->get(finalPos[0], finalPos[1])->getCreaturesNbr() << std::endl;
            
    }
    
    void MoveAction::undo (state::State& etat) 
    {
        // On replace les creatures sur les deux cases telles qu'elles etaient avant le combat
        
        // Joueur qui se deplaçait
        Player* oldFighter = etat.getPlayer(player).get();
        // Adversaire
        Player* oldDefender = etat.getPlayer(3-player).get();
        
        // S'il y a un groupe sur la cellule de depart
        Element* attGroup = etat.getCharacters()->get(initPos[0],initPos[1]).get();
        if (attGroup)
        {
            // Si ce groupe appartient à l'adversaire
            if (attGroup->getPlayer() == etat.getPlayer(3-player).get())
            {
                // On lui associe le joueur qui se deplacait lors du mouvement
                attGroup->setPlayer(oldFighter);
                // On augmente le nombre de cellules du joueur attaquant
                oldFighter->setCellNbr(oldFighter->getCellNbr() + 1);
                // On diminue le nombre de cellules du defenseur
                oldDefender->setCellNbr(oldDefender->getCellNbr() - 1);
            }
            //std::cout << "MoveAction::undo - La case de depart est occupee" << std::endl;
            
            // On lui restitue le bon nombre de creatures
            attGroup->setCreaturesNbr(initCreaturesNbr[0]);
            // Si la cellule appartient encore à l'attaquant, on ne touche pas aux nbres de cellules des joueurs
        }
        // Si la case est vide, on créé un nouveau groupe
        else
        {
            //std::cout << "MoveAction::undo - La case de depart n'est plus occupee" << std::endl;
            CreaturesGroup* newGroup = new CreaturesGroup((ID)oldFighter->getClanName(),initCreaturesNbr[0],oldFighter);
            etat.getCharacters()->set(newGroup,initPos[0],initPos[1]);
            // On augmente le nombre de cellules du joueur attaquant
            oldFighter->setCellNbr(oldFighter->getCellNbr() + 1);
        }

        // Si la cellule d'arrivee est occupee apres deplacement
        Element* defGroup = etat.getCharacters()->get(finalPos[0],finalPos[1]).get();
        if (defGroup)
        {
            //std::cout << "MoveAction::undo - La case de destination est occupee" << std::endl;
            // Si elle est actuellement occupee par l'ancien attaquant
            if (defGroup->getPlayer() == oldFighter) {
                // Si elle appartenait à l'adversaire avant deplacement/combat
                if (fight->getCreasDefender() != 0) {
                    //std::cout << "MoveAction::undo - La case de destination appartenait à l'adversaire avant le combat" << std::endl;
                    // On lui restitue ses creatures
                    CreaturesGroup* newGroup = new CreaturesGroup((ID)oldDefender->getClanName(), initCreaturesNbr[1], oldDefender);
                    etat.getCharacters()->set(newGroup, finalPos[0], finalPos[1]);
                    // On augmente le nbre de cellules du defenseur
                    oldDefender->setCellNbr(oldDefender->getCellNbr() + 1);
                    // On diminue le nombre de cellules du joueur attaquant
                    oldFighter->setCellNbr(oldFighter->getCellNbr() - 1);
                }                    
                // Si elle appartenait au joueur en cours (il n'y a donc pas eu combat)
                else if (fight->getCreasDefender() == 0 && initCreaturesNbr[1] != 0) {
                    //std::cout << "MoveAction::undo - La case de destination appartenait au joueur en cours" << std::endl;
                    // On lui restitue ses creatures
                    defGroup->setPlayer(oldFighter);
                    defGroup->setCreaturesNbr(initCreaturesNbr[1]);
                    // On n'a pas à modifier le nbre de cellules du joueur
                }                    
                // Si elle etait vide
                else {
                    //std::cout << "MoveAction::undo - La case de destination etait vide" << std::endl;
                    // On detruit le groupe qui se trouve actuellement dessus
                    etat.getCharacters()->set(nullptr, finalPos[0], finalPos[1]);
                    // On diminue le nbre de cellules de l'attaquant
                    oldFighter->setCellNbr(oldFighter->getCellNbr() - 1);
                }
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
                newGroup2 = new CreaturesGroup((ID)oldDefender->getClanName(),fight->getCreasDefender(),oldDefender);
                etat.getCharacters()->set(newGroup2,finalPos[0],finalPos[1]);
                // On augmente le nbre de cellules du defenseur
                oldDefender->setCellNbr(oldDefender->getCellNbr() + 1);
            }
            // Si elle appartenait au joueur en cours (attaque avec une seule creature ou simple deplacement d'une creature)
            else if (fight->getCreasDefender() == 0 && initCreaturesNbr[1] != 0)
            {
                // On lui restitue ses creatures
                newGroup2 = new CreaturesGroup((ID)oldFighter->getClanName(),initCreaturesNbr[1],oldFighter);
                etat.getCharacters()->set(newGroup2,finalPos[0],finalPos[1]);
                // On augmente le nbre de cellules de l'attaquant
                oldFighter->setCellNbr(oldFighter->getCellNbr() + 1);
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
