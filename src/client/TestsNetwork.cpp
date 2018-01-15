/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TestsNetwork.h"


namespace server{
    
    // Pour gestion multi-thread
    mutex notre_mutex;
    int creaturesChoisies = 0;
    int tour = 0;
    // numéro du joueur 
    int numPlayer = 0;
    // numero du joueur qui commence en premier
    int beginner = 0;
    
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
    
    int getPartyNbr(sf::Http* serveur)
    {
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Get);
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        request.setUri("/game/1");
        sf::Http::Response answer = serveur->sendRequest(request);
        string reponse = answer.getBody();
        
        // On recupere la partie utile contenue dans la reponse du serveur
        int tailleReponse = reponse.size();
        string nombre = reponse.substr(tailleReponse - 4,1);
        // On convertit le nombre de joueur string en int
        return stoi(nombre);
    }
    
    int getPartyBeginner(sf::Http* serveur)
    {
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Get);
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        request.setUri("/game/0");
        sf::Http::Response answer = serveur->sendRequest(request);
        string reponse = answer.getBody();
        
        // On recupere la partie utile contenue dans la reponse du serveur
        int tailleReponse = reponse.size();
        string nombre = reponse.substr(tailleReponse - 4,1);
        // On convertit le numero du joueur string en int
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
        sf::Http* Http = new sf::Http("http://localhost",8080);
        Http->setHost("http://localhost",8080);
        
        // On recupere nbre de joueurs presents sur le serveur
        int nbr = getPlayerNbr(Http);
        // Si aucun joueur n'est present, celui qui se connecte devient le numéro 1, s'il y a un joueur présent, il sera le numero 2
        numPlayer = nbr + 1;
        
        // S'il y a dejà deux joueurs présents sur le serveur, on ne peut pas ajouter de nouveau joueur
        
        if (nbr < 2)
        {
            // Mise en place de la requete
            sf::Http::Request request;
            request.setMethod(sf::Http::Request::Put);
            request.setUri("/user");
            request.setHttpVersion(1, 1);
            request.setField("Content-Type", "application/x-www-form-urlencoded");

            cout << "Veuillez entrer un pseudo." << endl;
            string name;
            getline(cin, name);

            // On demande au joueur quel type de creatures il souhaite jouer
            int type;
            std::cout << "Quel type de creatures souhaitez-vous jouer ?\n" << std::endl;
            std::cout << "Cuisinier : 1\nForgeron : 2\nBûcheron : 3\nMineur : 4\n" << std::endl;
            cin >> type;
            creaturesChoisies = type;

            // On souhaite ajouter un nouvel utilisateur
            Json::Value newUser;
            newUser["name"] = name;
            newUser["creatures"] = translateType((CreaturesID) type);

            string data = newUser.toStyledString();
            request.setBody(data);

            // Envoi de la requete
            sf::Http::Response answer = Http->sendRequest(request);
            cout << "Statut de la reponse : " << answer.getStatus() << endl;
        }
        else
            cout << "Le serveur de jeu est complet, impossible d'ajouter un nouveau joueur !" << endl;
        
        
     
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
    
    void nouvellePartie(int party, int beginner)
    {
        // Connexion au serveur
        sf::Http* serveur = new sf::Http("http://localhost",8080);
        
        // On prend possession du mutex
        notre_mutex.lock();
        srand(party);
        
        // On initialise un moteur à partir du type de creatures choisies par le joueur
        engine::Engine moteur((CreaturesID)creaturesChoisies);
        // On initialise l'ia
        HeuristicAI ia(&moteur, party);
        
        // On crée un Layer qui permettra de gerer l'affichage des cellules
        CellTabLayer cellLayer(*(moteur.getState().getGrid().get()));
        // On crée un Layer qui permettra de gerer l'affichage des creatures
        CreaturesTabLayer charsLayer(*(moteur.getState().getCharacters().get()));
        
        sf::Event event;
        
        // Declaration de la fenetre
        sf::RenderWindow gameWindow(sf::VideoMode(1024, 720), "Garden Tensions");
        
        // On créé le thread lie à l'utilisation de l'ia et du moteur
        thread threadIA(routine_thread,(void*)&ia,(void*)&gameWindow);
        
        while (gameWindow.isOpen()) {
            
            while (gameWindow.pollEvent(event)) {
                // Fermeture de la fenetre ?
                if (event.type == sf::Event::Closed) gameWindow.close();
                notre_mutex.unlock();
            }
           
            // On verifie si l'IA en cours a gagné ou non la partie
            if (moteur.getState().getCellNbr() == moteur.getPlayer(numPlayer)->getCellNbr() || moteur.getPlayer(2 - numPlayer)->getCellNbr() == 0)
            {
                cout << "L'IA n°" << numPlayer << " a conquit toute la carte ou a totalement eliminé son adversaire !" << endl;
                break;
            }
            
            // On met à jour l'affichage
            cellLayer.initSurface();
            charsLayer.initSurface();
            
            gameWindow.clear();
            cellLayer.getSurface()->draw(gameWindow);
            charsLayer.getSurface()->draw(gameWindow);
            
            gameWindow.display();
        }
        
        // Attente de la fin du thread
        threadIA.join();
        std::cout << "\nNotre démonstration est terminée :)" << std::endl;
    }
    
    void* routine_thread(void* ia,void* gameWindow)
    {
        HeuristicAI* adrIA = (HeuristicAI*) ia;
        sf::RenderWindow* adrGameWindow = (sf::RenderWindow*)gameWindow;
        bool is_IA_winner = (adrIA->getMoteur()->getState().getCellNbr() == adrIA->getMoteur()->getPlayer(numPlayer)->getCellNbr() || adrIA->getMoteur()->getPlayer(2 - numPlayer)->getCellNbr() == 0);
        bool is_IA_loser = (adrIA->getMoteur()->getState().getCellNbr() == adrIA->getMoteur()->getPlayer(2 - numPlayer)->getCellNbr() || adrIA->getMoteur()->getPlayer(numPlayer)->getCellNbr() == 0);
        
        // On reste dans cette boucle tant que le joueur n'a pas gagné ou perdu
        while(!is_IA_winner && !is_IA_loser && adrGameWindow->isOpen())
        {
            std::lock_guard<std::mutex> lock (notre_mutex);
            
            std::cout << "\n--------------    Tour n°" << tour / 2 + 1 << " - "; 
            
            // Tour de l'IA
            std::cout << "C'est à l'IA n°" << numPlayer << " de jouer    --------------" << std::endl << std::endl;
            adrIA->run(numPlayer);
            
            tour++;
            adrIA->getMoteur()->increaseTour();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            
            // On verifie si l'un des deux joueurs a gagné ou non la partie
            is_IA_winner = (adrIA->getMoteur()->getState().getCellNbr() == adrIA->getMoteur()->getPlayer(numPlayer)->getCellNbr() || adrIA->getMoteur()->getPlayer(2 - numPlayer)->getCellNbr() == 0);
            is_IA_loser = (adrIA->getMoteur()->getState().getCellNbr() == adrIA->getMoteur()->getPlayer(2 - numPlayer)->getCellNbr() || adrIA->getMoteur()->getPlayer(numPlayer)->getCellNbr() == 0);
            
        }
        
        return 0;
    }
    
    void TestsNetwork()
    {
        // Connexion au serveur
        sf::Http* serveur = new sf::Http("http://localhost",8080);
        
        cout << "OOOOOOOOOOOOOOOOO Affichage des joueurs presents sur le serveur OOOOOOOOOOOOOOOOO" << endl;
        affichageListe();
        
        cout << "OOOOOOOOOOOOOOOOO Demande d'ajout d'un utilisateur sur le serveur OOOOOOOOOOOOOOOOO" << endl;
        ajoutUser();
        
        cout << "OOOOOOOOOOOOOOOOO Affichage des joueurs presents sur le serveur OOOOOOOOOOOOOOOOO" << endl;
        affichageListe();
        
        // On reste sur le serveur tant qu'un deuxieme joueur n'a pas rejoint la partie
        while (getPlayerNbr(serveur) != 2) 
        { 
            cout << "En attente d'un deuxieme joueur" << endl;
            sf::sleep(sf::seconds(2.0f));
        }
        
        // Les deux joueurs sont connectés, la partie peut commencer
        int beginner = getPartyBeginner(serveur);
        int party = getPartyNbr(serveur);
        cout << "Joueur qui commence la partie : " << beginner << endl;
        cout << "Numero de la partie : " << party << endl;
        nouvellePartie(party,beginner);
        
        nouvellePartie();
        
//        cout << "OOOOOOOOOOOOOOOOO Demande de suppression d'un utilisateur sur le serveur OOOOOOOOOOOOOOOOO" << endl;
//        suppressionUser("2");
//        
//        cout << "OOOOOOOOOOOOOOOOO Affichage des joueurs presents sur le serveur OOOOOOOOOOOOOOOOO" << endl;
//        affichageListe();
        
    }
    
}

// REQUETES console client :
// curl -X DELETE http://localhost:8080/user/1
// curl -X PUT -d '{"name":"pika"}' http://localhost:8080/user
// curl -X GET http://localhost:8080/user/1
// curl -X POST -d '{"name":"pikachu"}' http://localhost:8080/user/2
