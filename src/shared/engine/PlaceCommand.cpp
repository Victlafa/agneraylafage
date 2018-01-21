/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <SFML/Network.hpp>
#include "PlaceCommand.h"
#include <iostream>
#include "../shared/state/CreaturesTab.h"
#include "PlaceAction.h"

using namespace std;
using namespace state;

namespace engine{
    
    //PlaceCommand::PlaceCommand () {}
    PlaceCommand::PlaceCommand (int i_final, int j_final, int player, state::ID type) : finalPos(2) {
        finalPos[0] = i_final;
        finalPos[1] = j_final;
        this->player = player;
        this->creaType = type;
        this->type = CommandTypeID::PLACE;
    }
    
    void PlaceCommand::execute (std::stack<std::shared_ptr<Action> >& pile, state::State& state){
        cout << "PlaceCommand::execute - entree methode" << endl;
        std::shared_ptr<Action> action(new PlaceAction(finalPos[0], finalPos[1], player, creaType));
        cout << "PlaceCommand::execute - ligne 30" << endl;
        // On verifie si la case de destination n'est pas occupee par l'adversaire
        if(!state.getCharacters()->isOccupiedByOpp(finalPos[0],finalPos[1],state.getPlayer(player).get())){
            cout << "PlaceCommand::execute - ligne 33" << endl;
            pile.push(action);
            cout << "PlaceCommand::execute - ligne 35" << endl;
            action->apply(state);
            cout << "PlaceCommand::execute - ligne 36" << endl;
        }
        else
            throw std::runtime_error("PlaceCommand::execute - La case de destination choisie appartient à l'adversaire !");
        
        cout << "PlaceCommand::execute - sortie methode" << endl;
    }
    
    void PlaceCommand::serialize (Json::Value& out, int nTour) const{
        // Connexion au serveur
        //sf::Http* Http = new sf::Http("http://localhost",8080);
        //Http->setHost("http://localhost",8080);
        
        Json::Value placeCommand;
        placeCommand["type"] = "CommandTypeID::PLACE";
        placeCommand["finalPos[0]"] = finalPos[0];
        placeCommand["finalPos[1]"] = finalPos[1];
        placeCommand["creaType"] = Element::translateType(creaType);
        placeCommand["player"] = player;
        out.append(placeCommand);
        
        // Mise en place de la requete
        /*sf::Http::Request request;
        request.setMethod(sf::Http::Request::Put);
        request.setUri("/game");
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        
        request.setBody(placeCommand.asString());

        // Envoi de la requete
        sf::Http::Response answer = Http->sendRequest(request);*/
        
    }
    
    PlaceCommand* PlaceCommand::deserialize (const Json::Value& in){
        
        int player = in.get("player",0).asInt();
        string typeString = in.get("creaType","").asString();
        ID creaturesType = Element::translateType(typeString);
        
        std::vector<int> finalPlace(2);
        finalPlace[0] = in.get("finalPos[0]",0).asInt();
        finalPlace[1] = in.get("finalPos[1]",0).asInt();
        
        return new PlaceCommand(finalPlace[0],finalPlace[1],player,creaturesType);
    }
    
    // Setters and Getters
    const std::vector<int>& PlaceCommand::getFinalPos() const {return finalPos;}
    void PlaceCommand::setFinalPos(const std::vector<int>& pos) {this->finalPos = pos;}
    state::ID PlaceCommand::getCreaType() const {return creaType;}
    void PlaceCommand::setCreaType(state::ID creaType) {this->creaType = creaType;}
}