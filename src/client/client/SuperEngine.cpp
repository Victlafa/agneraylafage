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

    SuperEngine::SuperEngine (state::CreaturesID creaPl1, state::CreaturesID creaPl2) : Engine(creaPl1, creaPl2){
    }  
    
    void SuperEngine::addCommand (int priority, std::shared_ptr<engine::Command> cmd) {

        std::cout << "Entree dans SuperEngine::addCommand" << std::endl;
        // On ajoute une commande :
        this->currentCommands.emplace(priority,cmd);
        std::cout << "SuperEngine::addCommand emplace OK" << std::endl;
        
        Json::Value command;//(Json::arrayValue);
        
        std::cout << "SuperEngine::addCommand utilisation command" << std::endl;
        command["type"] = convertCommandTypeToString(cmd->getType());
        std::cout << "SuperEngine::addCommand type OK" << std::endl;
        command["player"] = cmd->getPlayer();
        std::cout << "SuperEngine::addCommand player OK" << std::endl;

        if(cmd->getType() == engine::CommandTypeID::MOVE)
        {
            engine::MoveCommand* mcmd = (engine::MoveCommand*)(cmd.get());
            command["initPos[0]"] = mcmd->getInitPos()[0];
            command["initPos[1]"] = mcmd->getInitPos()[1];
            std::cout << "SuperEngine::addCommand InitPos OK" << std::endl;
            command["finalPos[0]"] = mcmd->getFinalPos()[0];
            command["finalPos[1]"] = mcmd->getFinalPos()[1];
            std::cout << "SuperEngine::addCommand FinalPos OK" << std::endl;
        }
        else if(cmd->getType() == engine::CommandTypeID::PLACE)
        {
            engine::PlaceCommand* pcmd = (engine::PlaceCommand*)(cmd.get());
            command["finalPos[0]"] = pcmd->getFinalPos()[0];
            command["finalPos[1]"] = pcmd->getFinalPos()[1];
            std::cout << "SuperEngine::addCommand finalPos OK" << std::endl;
            command["creaType"] = state::Element::translateType(pcmd->getCreaType());
            std::cout << "SuperEngine::addCommand creaType OK" << std::endl;
        }

        // Connexion au serveur
        sf::Http* Http = new sf::Http("http://localhost",8080);
        Http->setHost("http://localhost",8080);
        
        // Mise en place de la requete
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Put);
        request.setUri("/game");
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        
        request.setBody(command.toStyledString());

        // Envoi de la requete
        sf::Http::Response answer = Http->sendRequest(request);
        
        // la map trie automatiquement les clés dans l'ordre croissant (en principe, à vérifier)
        // Ajout de commandes automatiques
        addPassiveCommands();
        
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


