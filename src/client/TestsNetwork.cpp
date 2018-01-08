/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TestsNetwork.h"


namespace server{
    
    void TestsNetwork() {
        
        cout << "Demande d'ajout d'un joueur sur le serveur" << endl;
        // Connexion au serveur
        sf::Http Http;
        Http.setHost("http://localhost:8080");
        
        // Mise en place de la requete
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Put);
        request.setUri("/user");
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        string data = "\'{\"name\":\"pika\"}\'";
        request.setBody(data);
        
        // Envoi de la requete
        sf::Http::Response answer = Http.sendRequest(request);
        cout << "Statut de la reponse : " << answer.getStatus() << endl;
         
         
     }
    
}
