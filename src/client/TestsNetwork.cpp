/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TestsNetwork.h"


namespace server{
    
    string translateType (CreaturesID typeElement)
    {
        if (typeElement == CreaturesID::BLACKSMITHS)
            return "BLACKSMITHS";
        else if (typeElement == CreaturesID::COOKERS) 
            return "COOKERS";
        else if (typeElement == CreaturesID::LUMBERJACKS)
            return "LUMBERJACKS";
        else if (typeElement == CreaturesID::MINERS)
            return "MINERS";
        else
            throw std::runtime_error("translateType (CreaturesID -> string) - utilisation d'un argument non valable");
    }
    
    void affichageListe()
    {
        // Connexion au serveur
        sf::Http Http;
        Http.setHost("http://localhost",8080);
        
        // Mise en place de la requete
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Get);
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        int nbJoueurs = 1;
        
        // Reponse suite à la requete
        sf::Http::Response answer;
        
        // Tant que le serveur effectue la requete, on affiche un joueur present sur le serveur
        do
        {
            request.setUri("/user/" + std::to_string(nbJoueurs));
            answer = Http.sendRequest(request);
            cout << "Statut de la reponse : " << answer.getStatus() << endl;
            cout << "Utilisateur demandé : " << answer.getBody() << endl;
            nbJoueurs ++;
        }
        while (answer.getStatus() == sf::Http::Response::Status::Accepted);
         
    }
    
    void ajoutUser() {
              
        // On vide le buffer d'entrée
        cin.clear();        
        // On vide le buffer de sortie
        cout.clear();
        
        // Connexion au serveur
        sf::Http Http;
        Http.setHost("http://localhost",8080);
        
        // Mise en place de la requete
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Put);
        request.setUri("/user");
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        
        cout << "Veuillez entrer un pseudo." << endl;
        string name;
        getline(cin,name);
        
        // On demande au joueur quel type de creatures il souhaite jouer
        int type;
        std::cout << "Quel type de creatures souhaitez-vous jouer ?\n" << std::endl;
        std::cout << "Cuisinier : 1\nForgeron : 2\nBûcheron : 3\nMineur : 4\n" << std::endl;
        cin >> type;
        
        // On souhaite ajouter un nouvel utilisateur
        Json::Value newUser;
        newUser["name"] = name;
        newUser["id"] = 4;
        newUser["creatures"] = translateType((CreaturesID)type);
        
        //string data = "-d \'{\"name\":\"pika\"}\'";
        string data = newUser.toStyledString();
        request.setBody(data);
        
        // Envoi de la requete
        sf::Http::Response answer = Http.sendRequest(request);
        cout << "Statut de la reponse : " << answer.getStatus() << endl;
         
         
     }
    
    void TestsNetwork()
    {
        cout << "Affichage des joueurs presents sur le serveur : " << endl;
        affichageListe();
        
        cout << "Demande d'ajout d'un utilisateur sur le serveur : " << endl;
        ajoutUser();
        
        cout << "Affichage des joueurs presents sur le serveur : " << endl;
        affichageListe();
        
    }
    
}

// REQUETES console client :
// curl -X DELETE http://localhost:8080/user/1
// curl -X PUT -d '{"name":"pika"}' http://localhost:8080/user
// curl -X GET http://localhost:8080/user/1
// curl -X POST -d '{"name":"pikachu"}' http://localhost:8080/user/2
