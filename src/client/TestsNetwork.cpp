/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TestsNetwork.h"
#include "./client.h"
#include "client/SuperEngine.h"
//#include "engine/Engine.h"


using namespace std;

namespace server{
    
    // Pour gestion multi-thread
    mutex notre_mutex;
    condition_variable cond;
    int creaturesChoisies = 0;
    int creaAdversary = 0;
    int tour = 0;
    // numéro du joueur 
    int numPlayer = 0;
    // numero du joueur qui commence en premier
    int beginner = 0;
    int compteurCommandesDebutTour = 0;
    int compteurCommandesFinTour = 0;
    int commandesLastTour = 0;
    
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
    
    int getServerInfo(sf::Http* serveur, std::string uri)
    {
        cout << "getServerInfo - entree methode" << endl;
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Get);
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        request.setUri(uri);
        sf::Http::Response answer = serveur->sendRequest(request);
        string reponse = answer.getBody();
        
        // On recupere la partie utile contenue dans la reponse du serveur
        int tailleReponse = reponse.size();
        string nombre;
        
        // Si on cherche à recuperer le numero de la partie tirée au hasard par le serveur ou le compteur de commandes envoyées sur le serveur
        if (uri == "/game/0" || uri == "/game/3")
        {
            // si le nombre ne comporte pas 3 chiffres (on verifie que la conversion de string en int est possible)
            if (!strtol(reponse.substr(tailleReponse - 6,3).c_str(),nullptr,10))
            {
                // si le nombre n'en comporte pas 2
                if (!(strtol(reponse.substr(tailleReponse - 5,2).c_str(),nullptr,10)))
                    // alors il en comporte un seul
                    nombre = reponse.substr(tailleReponse - 4,1);
                else
                    nombre = reponse.substr(tailleReponse - 5,2);
            }
            else
                nombre = reponse.substr(tailleReponse - 6,3);
                
        }
        // On souhaite d'autres infos de la part du serveur
        else
            nombre = reponse.substr(tailleReponse - 4,1);
        
        cout << "getServerInfo - sortie methode" << endl;
        
        // On convertit le nombre de joueur string en int
        return stoi(nombre);
    }
    
    int getCreaOtherPlayer(sf::Http* serveur)
    {
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Get);
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        if(numPlayer==1) request.setUri("/user/2");
        else if(numPlayer==2) request.setUri("/user/1");
        sf::Http::Response answer = serveur->sendRequest(request);
        string reponse = answer.getBody();
        
        // On recupere la partie utile contenue dans la reponse du serveur
        string nombre = reponse.substr(19,1);
        
        //std::cout << "getCreaOtherPlayer - type crea : " << nombre << std::endl;
        
        // On convertit le numero du joueur string en int
        return stoi(nombre);
    }

    void setOccupedPlayer(sf::Http* serveur, int num)
    {
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Post);
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        request.setUri("/game/2");
        Json::Value player;
        player["player"] = num;
        request.setBody(player.toStyledString());
        sf::Http::Response answer = serveur->sendRequest(request);
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
        nbJoueurs = getServerInfo(serveur,"/user/0");
        
        // On affiche un à un les joueurs
        for (int i = 1; i <= nbJoueurs; i++)
        {
            request.setUri("/user/" + std::to_string(i));
            answer = serveur->sendRequest(request);
            cout << "Statut de la reponse : " << answer.getStatus() << endl;
            cout << "Utilisateur demandé : " << answer.getBody() << endl;
        }
         
    }
    
    bool ajoutUser() {
                
        // On vide le buffer d'entrée
        cin.clear();        
        // On vide le buffer de sortie
        cout.clear();
        
        // Connexion au serveur
        sf::Http* Http = new sf::Http("http://localhost",8080);
        Http->setHost("http://localhost",8080);
        
        // On recupere nbre de joueurs presents sur le serveur
        int nbr = getServerInfo(Http,"/user/0");
        // Si aucun joueur n'est present, celui qui se connecte devient le numéro 1, s'il y a un joueur présent, il sera le numero 2
        numPlayer = nbr + 1;
        cout << "AjoutUser - numPlayer : " << numPlayer << endl;
        
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
            int type = 0;
            while (type < 1 || type > 4)
            {
                std::cout << "Quel type de creatures souhaitez-vous jouer ?\n" << std::endl;
                std::cout << "Cuisinier : 1\nForgeron : 2\nBûcheron : 3\nMineur : 4\n" << std::endl;
                cin >> type;
                if (type < 1 || type > 4) cout << "Veuillez choisir un chiffre entre 1 et 4 inclus !" << endl;
            }
            
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
            
            return true;
        }
        else
        {
            cout << "Le serveur de jeu est complet, impossible d'ajouter un nouveau joueur !" << endl;
            return false;
        }
            
        
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
        //cout << "Statut de la reponse : " << answer.getStatus() << endl;
     
    }
    
    bool verifAdversaryCommands(sf::Http* serveur)
    {
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Get);
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        request.setUri("/game/" + std::to_string(compteurCommandesDebutTour + 4));
        sf::Http::Response answer = serveur->sendRequest(request);
        string reponse = answer.getBody();
        //cout << "verifAdversaryCommands - reponse du serveur" << reponse << endl;
        
        Json::Value commande;
        Json::Reader reader;
        reader.parse(reponse,commande);
        
        if (commande.isMember("commande"))
        {
            cout << "verifAdversaryCommands - sortie true" << endl;
            return true;
        }
            
        else if (commande.isMember("fin_liste"))
        {
            cout << "verifAdversaryCommands - sortie false" << endl;
            return false;
        }
        else
            throw runtime_error("verifAdversaryCommands - probleme avec verif de la presence des commandes sur le serveur");
        
        
    }
    
    Json::Value getAdversaryCommands(sf::Http* serveur)
    {
        cout << "getAdversaryCommands - entree methode" << endl;
        
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Get);
        request.setHttpVersion(1, 1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        request.setUri("/game/" + std::to_string(compteurCommandesDebutTour + 4));
        sf::Http::Response answer = serveur->sendRequest(request);
        string reponse = answer.getBody();
        //cout << "getAdversaryCommands - reponse du serveur" << reponse << endl;
        
        Json::Value commande;
        Json::Reader reader;
        reader.parse(reponse,commande);
        
        return commande;
    }
    
    void nouvellePartie(int party, int beginner)
    {
        cout << "TestsNetwork::nouvellePartie ligne 228 - numPlayer : " << numPlayer << endl;
        
        // On prend possession du mutex
        std::unique_lock<std::mutex> lock(notre_mutex);
        
        // On initialise graine aleatoire correspondant à la partie selectionnée par le serveur
        srand(party);
        
        // Connexion au serveur
        sf::Http* serveur = new sf::Http("http://localhost",8080);
        
        // On initialise un moteur à partir du type de creatures choisies par le joueur
        client::SuperEngine moteur((numPlayer==1) ? (CreaturesID)creaturesChoisies : (CreaturesID)getCreaOtherPlayer(serveur), (numPlayer==2) ? (CreaturesID)creaturesChoisies : (CreaturesID)getCreaOtherPlayer(serveur));
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
        
        while (gameWindow.isOpen() && tour < 4) {
            
            sf::sleep(sf::seconds(1.0f));
            
            while (gameWindow.pollEvent(event)) {
                // Fermeture de la fenetre ?
                if (event.type == sf::Event::Closed) gameWindow.close();
            }
            
            int totalCellNbr = ia.getMoteur()->getState().getCellNbr();
            bool is_IA_winner = (totalCellNbr == ia.getMoteur()->getPlayer(numPlayer)->getCellNbr() || ia.getMoteur()->getPlayer(3 - numPlayer)->getCellNbr() == 0);
            bool is_IA_loser = (totalCellNbr == ia.getMoteur()->getPlayer(3 - numPlayer)->getCellNbr() || ia.getMoteur()->getPlayer(numPlayer)->getCellNbr() == 0);
            
            // Si aucune des IAs n'a gagné pour le moment
            if (!is_IA_winner && !is_IA_loser)
            {
                cout << "TestsNetwork::nouvellePartie - joueur en cours : " << getServerInfo(serveur, "/game/2") << endl;

                // si c'est au tour du joueur
                if (getServerInfo(serveur, "/game/2") == numPlayer) {
                    
                    cout << "TestsNetwork::nouvellePartie - debut du tour du joueur" << endl;

                    tour++;
                    std::cout << "\n--------------    Tour n°" << tour / 2 + 1 << " - ";

                    // Tour de l'IA
                    std::cout << "C'est à l'IA n°" << numPlayer << " de jouer    --------------" << std::endl << std::endl;
                    
                    // On recupere les commandes de l'adversaire et on les execute
                    for (int k = 0; k < (getServerInfo(serveur,"/game/3") - compteurCommandesFinTour); k++)
                    {
                        cout << "nouvellePartie - commande adverse n°" << k << endl;
                        if (verifAdversaryCommands(serveur)) 
                        {
                            Json::Value commande = getAdversaryCommands(serveur);
                            cout << "nouvellePartie - ligne 353 - Json::Value : " << commande.toStyledString() << endl;
                            Command* newCommand = Command::deserialize(commande["commande"]);
                            moteur.Engine::addCommand(1, std::shared_ptr<Command>(std::move(newCommand)));
                            std::cout << "nouvellePartie - avant moteur.update()" << std::endl;
                            moteur.update();
                            std::cout << "nouvellePartie - apres moteur.update()" << std::endl;
                            compteurCommandesDebutTour += 1;
                        }
                        else
                            throw std::runtime_error("nouvellePartie - probleme avec recup des commandes adverses");
                    }
                    
                    sf::sleep(sf::seconds(1.0f));
                    
                    if (compteurCommandesDebutTour != getServerInfo(serveur,"/game/3"))
                        throw runtime_error("Probleme avec comptage des commandes");
                    
                    // On attend que le moteur ait executé les commandes
                    cond.wait(lock);
                    
                    cout << "TestsNetwork::nouvellePartie - le moteur a fini d'executer les commandes" << endl;
                    
                    // On recupere le nombre total de commandes enregistrees sur le serveur
                    ia.getMoteur()->increaseTour();

                    // On verifie si l'un des deux joueurs a gagné ou non la partie
                    is_IA_winner = (totalCellNbr == ia.getMoteur()->getPlayer(numPlayer)->getCellNbr() || ia.getMoteur()->getPlayer(3 - numPlayer)->getCellNbr() == 0);
                    is_IA_loser = (totalCellNbr == ia.getMoteur()->getPlayer(3 - numPlayer)->getCellNbr() || ia.getMoteur()->getPlayer(numPlayer)->getCellNbr() == 0);

                    // Une fois son tour achevé on signale au serveur que l'adversaire peut debuter son tour
                    setOccupedPlayer(serveur, 3 - numPlayer);

                    //cout << "TestsNetwork::nouvellePartie - fin du tour du joueur" << endl;
                }

                // si c'est à l'adversaire de jouer
                else if (getServerInfo(serveur,"/game/2") == 3 - numPlayer) cout << "\n>>>>>>>>>>>>>>>>> TOUR DE L'ADVERSAIRE <<<<<<<<<<<<<<<<<" << endl;
                
            }
            
            // On verifie si l'IA en cours a gagné ou non la partie
            if (moteur.getState().getCellNbr() == moteur.getPlayer(numPlayer)->getCellNbr() || moteur.getPlayer(3 - numPlayer)->getCellNbr() == 0)
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
        
    }
    
    void* routine_thread(void* ia,void* gameWindow)
    {
        sf::RenderWindow* adrWindow = (sf::RenderWindow*)gameWindow;
        
        while (adrWindow->isOpen() && tour < 4)
        {
            if (tour != 0)
            {
                cout << "TestsNetwork::routine_thread - avant execution des commandes" << endl;
                std::unique_lock<std::mutex> lock(notre_mutex);
                
                HeuristicAI* adrIA = (HeuristicAI*) ia;

                adrIA->run(numPlayer);
                commandesLastTour = adrIA->getMoteur()->nbrLastCommands;
                adrIA->getMoteur()->nbrLastCommands = 0;
                compteurCommandesFinTour += commandesLastTour;
                compteurCommandesDebutTour = compteurCommandesFinTour;

                cout << "TestsNetwork::routine_thread - apres execution des commandes" << endl;
                sf::sleep(sf::seconds(1.0f));
                cond.notify_all();
            }
            
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
        if (ajoutUser())
        {
            cout << "OOOOOOOOOOOOOOOOO Affichage des joueurs presents sur le serveur OOOOOOOOOOOOOOOOO" << endl;
            affichageListe();

            // On reste sur le serveur tant qu'un deuxieme joueur n'a pas rejoint la partie
            while (getServerInfo(serveur, "/user/0") != 2) {
                cout << "En attente d'un deuxieme joueur" << endl;
                sf::sleep(sf::seconds(2.0f));
            }

            // Les deux joueurs sont connectés, la partie peut commencer
            int beginner = getServerInfo(serveur, "/game/1");
            int party = getServerInfo(serveur, "/game/0");
            cout << "Joueur qui commence la partie : " << beginner << endl;
            cout << "Numero de la partie : " << party << endl;
            cout << "----------->> La partie va commencer <<-----------" << endl;

            nouvellePartie(party, beginner);

            std::cout << "\n----------->> Fin de la partie <<-----------" << std::endl;
        }
        
        else
            cout << "Impossible de démarrer une partie" << endl;
        
        
        
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
