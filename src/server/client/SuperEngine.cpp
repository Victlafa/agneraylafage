/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "./engine.h"
#include <iostream>

using namespace engine;

namespace client {

    void SuperEngine::addCommand (int priority, std::shared_ptr<engine::Command> cmd) 
    {
        
        std::cout << "Entree dans SuperEngine::addCommand" << std::endl;
        // On ajoute une commande :
        this->currentCommands.emplace(priority,cmd);
        
        
        Json::Value placeCommand;
        placeCommand["type"] = "CommandTypeID::PLACE";
        placeCommand["finalPos[0]"] = finalPos[0];
        placeCommand["finalPos[1]"] = finalPos[1];
        placeCommand["creaType"] = Element::translateType(creaType);
        placeCommand["player"] = player;
        
        // Connexion au serveur
        sf::Http* Http = new sf::Http("http://localhost",8080);
        Http->setHost("http://localhost",8080);
        
        // Mise en place de la requete
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Put);
        request.setUri("/game");
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        
        request.setBody(placeCommand.asString());

        // Envoi de la requete
        sf::Http::Response answer = Http->sendRequest(request);
        
        // la map trie automatiquement les clés dans l'ordre croissant (en principe, à vérifier)
        // Ajout de commandes automatiques
        addPassiveCommands();
        
    }
    
    std::string SuperEngine::convertCommandTypeToString (CommandTypeID commandType)
    {
        if (commandType == CommandTypeID::NEWGAME)
            return "CommandTypeID::NEWGAME";
        else if (commandType == CommandTypeID::MOVE)
            return "CommandTypeID::MOVE";
        else if (commandType == CommandTypeID::PLACE)
            return "CommandTypeID::PLACE";
        else if (commandType == CommandTypeID::POISON)
            return "CommandTypeID::POISON";
        else if (commandType == CommandTypeID::PROTECTED)
            return "CommandTypeID::PROTECTED";
        else if (commandType == CommandTypeID::SPECIAL)
            return "CommandTypeID::SPECIAL";
        else
            throw std::runtime_error("SuperEngine::convertCommandTypeToString - l'arguement d'entrée n'est pas valide !");
        
    }

}

