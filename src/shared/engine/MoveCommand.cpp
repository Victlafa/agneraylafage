/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MoveCommand.h"
#include <iostream>
#include "MoveAction.h"

namespace engine{
    
    MoveCommand::MoveCommand (int init_i, int init_j, int final_i, int final_j, int player) : initPos(2), finalPos(2) {
        //std::cout << "Entree dans MoveCommand::MoveCommand" << std::endl;
        initPos[0] = init_i;
        initPos[1] = init_j;
        finalPos[0] = final_i;
        finalPos[1] = final_j;
        this->player = player;
        this->type = CommandTypeID::MOVE;
        
    }
    
    void MoveCommand::execute (std::stack<std::shared_ptr<Action>>& pile, state::State& state) {
        
        //std::cout << "Entree dans MoveCommand::execute" << std::endl;
        
        // On verifie si la case de destination est adjacente à celle de departs
        bool verif1 = ((finalPos[0] == initPos[0] - 1) && finalPos[1] == initPos[1]);
        bool verif2 = ((finalPos[0] == initPos[0] - 1) && (finalPos[1] == initPos[1] + 1));
        bool verif3 = (finalPos[0] == initPos[0] && (finalPos[1] == initPos[1] + 1));
        bool verif4 = ((finalPos[0] == initPos[0] + 1) && finalPos[1] == initPos[1]);
        bool verif5 = ((finalPos[0] == initPos[0] + 1) && (finalPos[1] == initPos[1] - 1));
        bool verif6 = (finalPos[0] == initPos[0] && (finalPos[1] == initPos[1] - 1));
        
        if (verif1 || verif2 || verif3 || verif4 || verif5 || verif6)
        {
            //prendre en compte le joueur
            std::shared_ptr<Action> action;
            action.reset(new MoveAction(initPos[0], initPos[1], finalPos[0], finalPos[1],player));
            //std::cout << "taille avant push : " << pile.size() << std::endl;
            pile.push(action);
            action->apply(state);
            //std::cout << "taille après push : " << pile.size() << std::endl;
        }
        else
            throw std::runtime_error("MoveCommand::execute - La case de destination doit etre adjacente à celle de depart !");
        
    }
    
    void MoveCommand::serialize (Json::Value& out, int nTour) const{
        Json::Value moveCommandNM;
        moveCommandNM["type"] = "CommandTypeID::MOVE";
        moveCommandNM["initPos[0]"] = initPos[0];
        moveCommandNM["initPos[1]"] = initPos[1];
        moveCommandNM["finalPos[0]"] = finalPos[0];
        moveCommandNM["finalPos[1]"] = finalPos[1];
        (out[nTour]).append(moveCommandNM);
        
        Json::StyledWriter styledWriter;
        std::cout << styledWriter.write(moveCommandNM) << std::endl;
        
    }
    
    MoveCommand* MoveCommand::deserialize (const Json::Value& in){
        
        int player = in.get("player",0).asInt();
        std::vector<int> initPlace(2);
        std::vector<int> finalPlace(2);
        
        initPlace[0] = in.get("initPos[0]",0).asInt();
        initPlace[1] = in.get("initPos[1]",0).asInt();
        finalPlace[0] = in.get("finalPos[0]",0).asInt();
        finalPlace[1] = in.get("finalPos[1]",0).asInt();
        
        return new MoveCommand(initPlace[0],initPlace[1],finalPlace[0],finalPlace[1],player);
        
    }
    
    // Setters and Getters
    const std::vector<int>& MoveCommand::getInitPos() const { return initPos; }
    void MoveCommand::setInitPos(const std::vector<int>& initPos) { this->initPos = initPos; }
    const std::vector<int>& MoveCommand::getFinalPos() const { return finalPos; }
    void MoveCommand::setFinalPos(const std::vector<int>& finalPos) {this->finalPos = finalPos; }
    
}
