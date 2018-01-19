/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mikhan
 *
 * Created on 14 décembre 2017, 10:26
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <microhttpd.h>
#include <string.h>
#include <SFML/Network.hpp>

#include "../shared/state.h"
#include "../shared/engine.h"
#include "../shared/ai.h"
#include "../server/server.h"

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;
using namespace server;


class Request {
public:
    struct MHD_PostProcessor *pp = nullptr;
    string data;
    ~Request() {
        if (pp) MHD_destroy_post_processor (pp);
    }
};

// Fonction pour gérer les données importantes en upload (non implanté ici)
static int post_iterator(void *cls,
        enum MHD_ValueKind kind,
        const char *key,
        const char *filename,
        const char *content_type,
        const char *transfer_encoding,
        const char *data, uint64_t off, size_t size) 
{
    return MHD_NO;
}

// Détruit les données d'une requête
static void request_completed (void *cls, struct MHD_Connection *connection, void **con_cls, enum MHD_RequestTerminationCode toe)
{
  Request *request = (Request*)*con_cls;
  if (request) {
      delete request;
      *con_cls = nullptr;
  }
}

// Gestionnaire principal
static int
main_handler (void *cls,      
          struct MHD_Connection *connection,
          const char *url, // 
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr) 
{
    // Données pour une requête (en plusieurs appels à cette fonction)
    Request *request = (Request*)*ptr;

    // Premier appel pour cette requête
    if (!request) { 
        request = new Request();
        if (!request) {
            return MHD_NO;
        }
        *ptr = request;
        if (strcmp(method, MHD_HTTP_METHOD_POST) == 0
         || strcmp(method, MHD_HTTP_METHOD_PUT) == 0) {
            request->pp = MHD_create_post_processor(connection,1024,&post_iterator,request);
            if (!request->pp) {
                cerr << "Failed to setup post processor for " << url << endl;
                return MHD_NO;
            }
        }
        return MHD_YES;
    }    
    
    // Cas où il faut récupérer les données envoyées par l'utilisateur
    if (strcmp(method, MHD_HTTP_METHOD_POST) == 0
     || strcmp(method, MHD_HTTP_METHOD_PUT) == 0) {
        MHD_post_process(request->pp,upload_data,*upload_data_size);
        if (*upload_data_size != 0) {
            //cout << "Donnees envoyées par l'utilisateur : " << upload_data << endl;
            request->data = upload_data;
            *upload_data_size = 0;
            return MHD_YES;
        }    
    }

    HttpStatus status;
    string response;
    try {

        ServicesManager *manager = (ServicesManager*) cls;
        status = manager->queryService(response,request->data,url,method);
    }
    catch(ServiceException& e) {
        status = e.status();
        response = e.what();
        response += "\n";
    }
    catch(exception& e) {
        status = HttpStatus::SERVER_ERROR;
        response = e.what();
        response += "\n";
    }
    catch(...) {
        status = HttpStatus::SERVER_ERROR;
        response = "Unknown exception\n";
    }

    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(response.size(),(void *)response.c_str(),MHD_RESPMEM_MUST_COPY);
    if (strcmp(method,MHD_HTTP_METHOD_GET) == 0) {
        MHD_add_response_header(mhd_response,"Content-Type","application/json; charset=utf-8");
    }
    int ret = MHD_queue_response(connection, status, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}


int main(int argc, char** argv) {

    if (argc >= 2 && (string) argv[1] == "record"){
        
        cout << "XXXXXXXXXXXXXXXX      ENREGISTREMENT D'UNE PARTIE      XXXXXXXXXXXXXXXX\n" << endl;
        
        srand(2);

        // On initialise un moteur, on choisit les mineurs pour le joueur 1
        engine::Engine moteur(state::CreaturesID::MINERS, state::CreaturesID::COOKERS);
        // On initialise une ia
        ai::HeuristicAI ia(&moteur, 2);

        std::ofstream file("./src/replay.txt", std::ios::out);
        //file.open("../replay.txt");
        if(file.bad()){
            std::cout << "Erreur avec le fichier replay.txt" << std::endl;
            return 1;
        }
        
        Json::Value jsonArray(Json::arrayValue);
        //ia.setJsonFile(jsonArray);

        Json::StyledWriter styledWriter;
        
        //On sauvegarde l'état initial du jeu
        Json::Value etatInit(Json::arrayValue);
        
        // On fait le tour de toutes les cellules de la carte
        for(int i=0; i<5; i++){
            for(int j=0; j<7; j++){
                // Si la cellule selectionnee est non vide
                if(moteur.getState().getCharacters()->get(i,j)!=NULL){
                    Json::Value elem;
                    // Si la cellule appartient au joueur 1
                    if (moteur.getPlayer(1).get() == moteur.getState().getCharacters()->get(i,j)->getPlayer())
                        elem["joueur"] = 1;
                    else
                        elem["joueur"] = 2;
                    elem["creature"] = moteur.getState().getCharacters()->get(i,j)->getElemType();
                    elem["nbrCrea"] = moteur.getState().getCharacters()->get(i,j)->getCreaturesNbr();
                    elem["i"] = i;
                    elem["j"] = j;
                    etatInit.append(elem);
                }
            }
        }
        
        jsonArray.append(etatInit);
        moteur.setRecord(jsonArray);

        int tour = 0;

        std::cout << "Ici s'affrontent deux IAs heuristiques qui peuvent pour le moment seulement se déplacer et combattre avec les quelques créatures qu'elles ont au départ de la partie. Elles peuvent aussi ajouter des creatures lors d'une phase de renfort." << std::endl;
        std::cout << "La démonstration se fera sur 20 tours." << std::endl;
        std::cout << "De plus nous avons donné la priorité aux combats. Il est donc possible que des groupes de creatures ne cherchent pas à se disperser tant qu'elles n'ont pas d'ennemies à proximité." << std::endl;
        std::cout << "(APPUYER sur une touche de clavier pour passer à l'étape suivante)" << std::endl;

        while(tour!=2){
            std::cout << "\n--------------    Tour n°" << tour/2 + 1 << ", c'est à l'IA n°" << tour%2 + 1 << " de jouer    --------------" << std::endl << std::endl;

            // Tour de l'IA n°1
            if(tour%2==0) ia.run(1);
            // Tour de l'IA n°2
            else ia.run(2);
            // Execution des commandes demandées par les IA
            //moteur.update();
            //t2 = clock();

            //std::cout << "Temps execution jeu sans thread : " << (float)(t2 - t1)/CLOCKS_PER_SEC << std::endl;
            cout << "TestsHeuristicIA - Nombre de cellules du joueur 1 : " << moteur.getPlayer(1)->getCellNbr() << endl;
            cout << "TestsHeuristicIA - Nombre de cellules du joueur 2 : " << moteur.getPlayer(2)->getCellNbr() << endl;

            tour++;
            moteur.increaseTour();

            if (moteur.getState().getCellNbr() == moteur.getPlayer(1)->getCellNbr() || moteur.getPlayer(2)->getCellNbr() == 0)
            {
                cout << "L'IA n°1 a conquit toute la carte ou a éliminé son adversaire !" << endl;
                break;
            }

            else if (moteur.getState().getCellNbr() == moteur.getPlayer(2)->getCellNbr() || moteur.getPlayer(1)->getCellNbr() == 0)
            {
                cout << "L'IA n°2 a conquit toute la carte ou a éliminé son adversaire !" << endl;
                break;
            }

            ///std::cout << styledWriter.write(ia.getJsonFile()) << std::endl;
        }

        file << styledWriter.write(ia.getMoteur()->getRecord());

        //std::cout << styledWriter.write(ia.getJsonFile()) << std::endl;

        file.close();
    }
    
    else if (argc >= 2 && (string) argv[1] == "listen"){
        
        srand(time(NULL));
        
        try {
            ServicesManager servicesManager;
            servicesManager.registerService(std::move(std::unique_ptr<VersionService>(new VersionService())));
            servicesManager.registerService(std::move(std::unique_ptr<GameService>(new GameService())));

            UserGame userGame;
            //userGame.addUser(std::move(std::unique_ptr<User>(new User("Paul",state::CreaturesID::MINERS))));
            servicesManager.registerService(std::move(std::unique_ptr<UserService>(new UserService(userGame))));

            struct MHD_Daemon *d;
            d = MHD_start_daemon(// MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG | MHD_USE_POLL,
                    MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
                    // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG | MHD_USE_POLL,
                    // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
                    8080,
                    NULL, NULL, 
                    &main_handler, (void*) &servicesManager,
                    MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
                    MHD_OPTION_END);
            if (d == NULL)
                return 1;
            cout << "Pressez <entrée> pour arrêter le serveur" << endl;
            (void) getc(stdin);
            MHD_stop_daemon(d);
        }
        catch(exception& e) {
            cerr << "Exception: " << e.what() << endl;
        }
    
    }
    
    return 0;
}

