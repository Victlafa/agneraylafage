/** 
 * @file ServicesManager.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "ServicesManager.hpp"
#include "ServicesManager.h"

using namespace std;
using namespace server;

void ServicesManager::registerService (std::unique_ptr<AbstractService> service) {
    // Ajout du service à la liste
    services.push_back(std::move(service));
}

AbstractService* ServicesManager::findService (const std::string& url) const {
    // On explore la liste des services
    for (auto& service : services) {
        // On recupere pour chaque service son pattern
        const std::string& pattern(service->getPattern());
        // Si le pattern ne fait pas partie de l'url ...
        if (url.find(pattern) != 0)
            // On passe à l'étude du service suivant
            continue;
        // Si l'url est plus longue que le pattern et si l'url ne contient pas "/" au bon endroit ...
        if (url.size() > pattern.size() && url[pattern.size()] != '/')
            // On passe à l'étude du service suivant
            continue;
        // Dans les autres cas, on retourne le service voulu
        return service.get();
    }
    // Si aucun service approprié n'a été trouvé, on renvoie nullptr
    return nullptr;
}

HttpStatus ServicesManager::queryService (std::string& out, const std::string& in, const std::string& url, const std::string& method) { 
        
    //cerr << "ServicesManager::queryService - requete avec contenu : " << in << endl;
    
    // On cherche le service approprie
    AbstractService* service = findService(url);
    if (!service)
        throw ServiceException(HttpStatus::NOT_FOUND,"Service "+url+" non trouvé");
    
    // Recherche un éventuel id (ex: /mon/service/<id>)
    const std::string& pattern(service->getPattern());
    int id = 0;
    
    // Si l'url est plus longue que le pattern
    if (url.size() > pattern.size()) {
        // On recupere la fin de l'url
        string end = url.substr(pattern.size());
        
        if (end[0] != '/')
            throw ServiceException(HttpStatus::BAD_REQUEST,"Url malformée (forme attendue: <service>/<nombre>)");
        end = end.substr(1);
        if (end.empty())
            throw ServiceException(HttpStatus::BAD_REQUEST,"Url malformée (forme attendue: <service>/<nombre>)");
        try {
            size_t pos = 0;
            // on convertit "end" en entier
            id = stoi(end,&pos);
            if (pos != end.size())
                throw ServiceException(HttpStatus::BAD_REQUEST,"Url malformée: '"+end+"' n'est pas un nombre");
        }
        catch(...) {
            throw ServiceException(HttpStatus::BAD_REQUEST,"Url malformée: '"+end+"' n'est pas un nombre");
        }
    }
    
    // Traite les différentes méthodes
    if (method == "GET") {
        cerr << "Requête GET " << pattern << " avec id=" << id << endl;
        Json::Value jsonOut;
        HttpStatus status = service->get(jsonOut,id);
        out = jsonOut.toStyledString();
        return status;
    }
    else if (method == "POST") {
        std::cerr.clear();
        std::cout.clear();
        
        cerr << "Requête POST " << pattern << " avec contenu: " << in << endl;
        Json::Reader jsonReader;
        Json::Value jsonIn;
        if (!jsonReader.parse(in,jsonIn))
            throw ServiceException(HttpStatus::BAD_REQUEST,"Données invalides: "+jsonReader.getFormattedErrorMessages());
        return service->post(jsonIn,id);
    }
    else if (method == "PUT") {
        cerr << "Requête PUT " << pattern << " avec contenu: " << in << endl;
        Json::Reader jsonReader;
        Json::Value jsonIn;
        if (!jsonReader.parse(in,jsonIn))
            throw ServiceException(HttpStatus::BAD_REQUEST,"Données invalides: "+jsonReader.getFormattedErrorMessages());
        Json::Value jsonOut;
        HttpStatus status = service->put(jsonOut, jsonIn);
        out = jsonOut.toStyledString();
        return status;
    }
    else if (method == "DELETE") {
        cerr << "Requête DELETE" << endl;
        return service->remove(id);
    }
    throw ServiceException(HttpStatus::BAD_REQUEST,"Méthode "+method+" invalide");
}


