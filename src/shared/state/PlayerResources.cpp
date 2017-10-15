/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PlayerResources.h"

namespace state{
        
    int PlayerResources::getResource(std::string type) const
    {
            if (type == "wood")
                return wood;
            else if (type == "stone")
                return stone;
            else if (type == "metal")
                return metal;
            else if (type == "food")
                return food;
            else
                throw "La ressource que vous voulez récupérer n'existe pas !";
    }
    
    /// setResource :
    /// Incrémente la ressource désignée de 1 si increase = true, sinon la décrémente de 1.
    /// Renvoie -1 si le type de nourriture entré ne correspond pas aux quatre types présents.
    void PlayerResources::setResource (std::string type, int quantity, bool increase)
    {
        if (increase)
        {
            if (type == "wood")
                wood += 1;
            else if (type == "stone")
                stone += 1;
            else if (type == "metal")
                metal += 1;
            else if (type == "food")
                food += 1;
            else
                throw "La ressource que vous voulez mettre à jour n'existe pas !";
        }
        
        else
        {
            if (type == "wood")
                wood -= 1;
            else if (type == "stone")
                stone -= 1;
            else if (type == "metal")
                metal -= 1;
            else if (type == "food")
                food -= 1;
            else
                throw "La ressource que vous voulez mettre à jour n'existe pas !";
        }

    }
    
    
};