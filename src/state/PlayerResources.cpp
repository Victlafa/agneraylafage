/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PlayerResources.h"

namespace state{
        
    int PlayerResources::GetResource(std::string type)
    {
        switch(type)
        {
            case "wood":
                return PlayerResources.wood;
                break;
            case "stone":
                return PlayerResources.stone;
                break;
            case "metal":
                return PlayerResources.metal;
                break;
            case "food":
                return PlayerResources.food;
                break;
            default:
                throw std::invalid_argument("Le nom entré n'est pas valide ! Impossible d'accéder aux ressources du joueur !");
                break;
        }
    }
    
    
};