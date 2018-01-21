/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//#include "../engine.h"
#include <SFML/Network.hpp>
#include <iostream>
#include "SuperEngine.h"
#include "../../shared/state/Element.h"
#include "engine/PlaceCommand.h"

namespace client {

    SuperEngine::SuperEngine (state::CreaturesID creaPl1, state::CreaturesID creaPl2) : Engine(creaPl1, creaPl2){}  
    
    void SuperEngine::addCommand (int priority, std::shared_ptr<engine::Command> cmd) {
        

        //std::cout << "Entree dans SuperEngine::addCommand" << std::endl;
        // On ajoute une commande :
        this->currentCommands.emplace(priority,cmd);
        
        Json::Value command;//(Json::arrayValue);
        
        command["type"] = convertCommandTypeToString(cmd->getType());
        command["player"] = cmd->getPlayer();

        if(cmd->getType() == engine::CommandTypeID::MOVE)
        {
            engine::MoveCommand* mcmd = (engine::MoveCommand*)(cmd.get());
            command["initPos[0]"] = mcmd->getInitPos()[0];
            command["initPos[1]"] = mcmd->getInitPos()[1];
            command["finalPos[0]"] = mcmd->getFinalPos()[0];
            command["finalPos[1]"] = mcmd->getFinalPos()[1];
        }
        else if(cmd->getType() == engine::CommandTypeID::PLACE)
        {
            engine::PlaceCommand* pcmd = (engine::PlaceCommand*)(cmd.get());
            command["finalPos[0]"] = pcmd->getFinalPos()[0];
            command["finalPos[1]"] = pcmd->getFinalPos()[1];
            command["creaType"] = state::Element::translateType(pcmd->getCreaType());
        }
        
        // Connexion au serveur
        sf::Http* Http = new sf::Http("http://localhost",8080);
        
        // Mise en place de la requete
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Put);
        request.setUri("/game");
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        
        request.setBody(command.toStyledString());

        // Envoi de la requete
        sf::Http::Response answer = Http->sendRequest(request);
        
        // Ajout de commandes automatiques
        //addPassiveCommands();
        
        //std::cout << "SuperEngine::addCommand sortie methode OK" << std::endl;
        
    }
    

    std::string SuperEngine::convertCommandTypeToString (engine::CommandTypeID commandType)
    {
        if (commandType == engine::CommandTypeID::NEWGAME)
            return "CommandTypeID::NEWGAME";
        else if (commandType == engine::CommandTypeID::MOVE)
            return "CommandTypeID::MOVE";
        else if (commandType == engine::CommandTypeID::PLACE)
            return "CommandTypeID::PLACE";
        else if (commandType == engine::CommandTypeID::POISON)
            return "CommandTypeID::POISON";
        else if (commandType == engine::CommandTypeID::PROTECTED)
            return "CommandTypeID::PROTECTED";
        else if (commandType == engine::CommandTypeID::SPECIAL)
            return "CommandTypeID::SPECIAL";
        else
            throw std::runtime_error("SuperEngine::convertCommandTypeToString - l'arguement d'entrée n'est pas valide !");
        
    }

}


