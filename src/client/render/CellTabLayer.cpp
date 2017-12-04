/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CellTabLayer.h"
#include "CellTileSet.h"
#include <iostream>

namespace render
{
    CellTabLayer::CellTabLayer (const state::CellTab& tab) : ElementTabLayer(tab)
    {
        this->tileset = std::shared_ptr<CellTileSet>(new CellTileSet());
        this->initSurface();
        this->surface->loadTexture("hexa.png");
    }
    void CellTabLayer::initSurface ()
    {
        int x = 311;
        int y = 187;
        int shift = 0;
        int halfWidth = 0;
        this->surface->initQuads();

        //this->surface->loadTexture("hexa.png");
        halfWidth = 51;

        // Listes temporaires qui permettront d'initialiser les Surface
        std::vector<int> listXTextCell = std::vector<int>();
        listXTextCell.reserve(29);
        std::vector<int> listYTextCell = std::vector<int>();
        listYTextCell.reserve(29);


        // On recupere les coordonnees des textures cellules dans l'image de texture associee
        // selon les types de cellules presents dans le tableau de cellules
        for(unsigned int i=0; i<tab.getHeight(); i++){

            for(unsigned int j=0; j<tab.getWidth(); j++){

                if(NULL!=tab.get(i,j)){

                    switch(tab.get(i,j)->getElemType()){
                        case state::ID::SAND :
                            listXTextCell.push_back(71);
                            listYTextCell.push_back(81);
                            break;
                        case state::ID::GRASS :
                            listXTextCell.push_back(191);
                            listYTextCell.push_back(81);
                            break;
                        case state::ID::DIRT :
                            listXTextCell.push_back(311);
                            listYTextCell.push_back(81);
                            break;   
                        case state::ID::BARBECUE :
                            listXTextCell.push_back(71);
                            listYTextCell.push_back(221);
                            break;
                        case state::ID::SKY :
                            listXTextCell.push_back(191);
                            listYTextCell.push_back(221);
                            break;
                        case state::ID::POOL :
                            listXTextCell.push_back(311);
                            listYTextCell.push_back(221);
                            break;
                        case state::ID::CANDY :
                            listXTextCell.push_back(431);
                            listYTextCell.push_back(221);
                            break;
                        default :
                            std::cout << "erreur définition coordonnées textures" << std::endl;
                            break;
                    }
                }
            }
        }


        // Coordonnées du tableau correspondant à la coordonnée i de la liste
        // Initialisees sur la premiere case de la grille AFFICHEE
        int xi=0, yi=2;

        for (int i = 0; i < 29; i++) 
        {
            // On se deplace dans la grille selon les indices i et j - modif des coords x,y,xi,yi
            if (i == 5 || i == 11) {
                x -= halfWidth;
                y += 86;
                xi++;

                switch (i) {
                    case 5:
                        yi++;
                        shift = i - 5;
                        break;
                    case 11:
                        shift = i - 11;
                        break;
                    default:
                        shift = i;
                }
            }

            else if (i == 18 || i == 24) {
                x += halfWidth;
                y += 86;
                xi++;

                switch (i) {
                    case 18:
                        shift = i - 18;
                        break;
                    case 24:
                        yi=0;
                        shift = i - 24;
                        break;
                    default:
                        shift = i;
                }
            }

            else
            {
                shift = shift;
            }



            // On initialise un Tile pour la cellule en i_eme position 
            Tile cellTile(listXTextCell[i], listYTextCell[i]);

            // On fixe la position de la cellule dans l'affichage final
            this->surface->setFinalLocation(i, shift, x, y, cellTile);
            // On fixe la position du sprite dans l'image texture de base
            this->surface->setTextureLocation(i, cellTile);

            shift += 1;
            yi = (yi+1)%7;

        }

    }
}