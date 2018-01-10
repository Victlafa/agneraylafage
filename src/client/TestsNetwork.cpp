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
            throw std::runtime_error("TestsNetwork - translateType (CreaturesID -> string) - utilisation d'un argument non valable");
    }
    
    int getPlayerNbr(sf::Http* serveur)
    {
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Get);
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        request.setUri("/user/0");
        sf::Http::Response answer = serveur->sendRequest(request);
        string reponse = answer.getBody();
        
        // On recupere la partie utile contenue dans la reponse du serveur
        int tailleReponse = reponse.size();
        string nombre = reponse.substr(tailleReponse - 4,1);
        // On convertit le nombre de joueur string en int
        return stoi(nombre);
    }
    
    void affichageListe()
    {
        // Connexion au serveur
        sf::Http* serveur = new sf::Http("http://localhost",8080);
        
        // Mise en place de la requete
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Get);
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        int nbJoueurs = -1;
        
        // Reponse suite à la requete
        sf::Http::Response answer;
        
        // On effectue une premiere requete pour savoir combien de joueurs sont presents sur le serveur
        nbJoueurs = getPlayerNbr(serveur);
        
        // On affiche un à un les joueurs
        for (int i = 1; i <= nbJoueurs; i++)
        {
            request.setUri("/user/" + std::to_string(i));
            answer = serveur->sendRequest(request);
            cout << "Statut de la reponse : " << answer.getStatus() << endl;
            cout << "Utilisateur demandé : " << answer.getBody() << endl;
        }
         
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
        newUser["creatures"] = translateType((CreaturesID)type);
        
        string data = newUser.toStyledString();
        request.setBody(data);
        
        // Envoi de la requete
        sf::Http::Response answer = Http.sendRequest(request);
        cout << "Statut de la reponse : " << answer.getStatus() << endl;
     
     }
    
    void suppressionUser(string nbr) {
             
        // Connexion au serveur
        sf::Http Http;
        Http.setHost("http://localhost",8080);
        
        // Mise en place de la requete
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Delete);
        request.setUri("/user/" + nbr);
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        
        // Envoi de la requete
        sf::Http::Response answer = Http.sendRequest(request);
        cout << "Statut de la reponse : " << answer.getStatus() << endl;
     
     }
    
    void TestsNetwork()
    {
        cout << "OOOOOOOOOOOOOOOOO Affichage des joueurs presents sur le serveur OOOOOOOOOOOOOOOOO" << endl;
        affichageListe();
        
        cout << "OOOOOOOOOOOOOOOOO Demande d'ajout d'un utilisateur sur le serveur OOOOOOOOOOOOOOOOO" << endl;
        ajoutUser();
        
        cout << "OOOOOOOOOOOOOOOOO Affichage des joueurs presents sur le serveur OOOOOOOOOOOOOOOOO" << endl;
        affichageListe();
        
        cout << "OOOOOOOOOOOOOOOOO Demande de suppression d'un utilisateur sur le serveur OOOOOOOOOOOOOOOOO" << endl;
        suppressionUser("2");
        
        cout << "OOOOOOOOOOOOOOOOO Affichage des joueurs presents sur le serveur OOOOOOOOOOOOOOOOO" << endl;
        affichageListe();
        
        
    }
    
}

// REQUETES console client :
// curl -X DELETE http://localhost:8080/user/1
// curl -X PUT -d '{"name":"pika"}' http://localhost:8080/user
// curl -X GET http://localhost:8080/user/1
// curl -X POST -d '{"name":"pikachu"}' http://localhost:8080/user/2
