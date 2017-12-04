/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CreaturesTabLayer.h"
#include "CharsTileSet.h"
#include <iostream>

namespace render
{
    CreaturesTabLayer::CreaturesTabLayer (const state::CreaturesTab& tab) : ElementTabLayer(tab)
    {
        this->tileset = std::shared_ptr<CharsTileSet>(new CharsTileSet());
        this->initSurface();
        this->surface->loadTexture("groupes.png");
    }
    void CreaturesTabLayer::initSurface ()
{
        int x = 311;
        int y = 187;
        int shift = 0;
        int halfWidth = 0;
        this->surface->initQuads();
        
        halfWidth = 50;

        // Listes temporaires qui permettront d'initialiser les Surface
        std::vector<int> listXTextChars = std::vector<int>();
        listXTextChars.reserve(29);
        std::vector<int> listYTextChars = std::vector<int>();
        listYTextChars.reserve(29);

        // On recupere les coordonnees des textures creatures dans l'image de texture associee
        // selon les types de creatures presents dans le tableau de creatures
        for (unsigned int i = 0; i < tab.getHeight(); i++) {

            for (unsigned int j = 0; j < tab.getWidth(); j++) {

                // S'il y a un groupe de creatures dans la case etudiee
                if (NULL != tab.get(i, j)) {

                    //std::cout << "TestsRender : elemType : " << tab.get(i,j)->getElemType() << std::endl;
                    // On recupere les coordonnees de la texture en fonction de son type et du nombre de creatures
                    switch (tab.get(i, j)->getElemType()) {
                        case state::ID::BLACKSMITH:
                            listXTextChars.push_back(50 * (2 * (tab.get(i, j)->getCreaturesNbr()) - 1));
                            listYTextChars.push_back(50);
                            //std::cout << "TestsRender : xTextPush : " << 50*(2*(tab.get(i,j)->getCreaturesNbr())-1) << " yTextPush : " << 50 << std::endl;
                            break;
                        case state::ID::COOKER:
                            listXTextChars.push_back(50 * (2 * (tab.get(i, j)->getCreaturesNbr()) - 1));
                            listYTextChars.push_back(150);
                            //std::cout << "TestsRender : xTextPush : " << 50*(2*(tab.get(i,j)->getCreaturesNbr())-1) << " yTextPush : " << 150 << std::endl;
                            break;
                        case state::ID::LUMBERJACK:
                            listXTextChars.push_back(50 * (2 * (tab.get(i, j)->getCreaturesNbr()) - 1));
                            listYTextChars.push_back(250);
                            //std::cout << "TestsRender : xTextPush : " << 50*(2*(tab.get(i,j)->getCreaturesNbr())-1) << " yTextPush : " << 250 << std::endl;
                            break;
                        case state::ID::MINER:
                            listXTextChars.push_back(50 * (2 * (tab.get(i, j)->getCreaturesNbr()) - 1));
                            listYTextChars.push_back(350);
                            //std::cout << "TestsRender : xTextPush : " << 50*(2*(tab.get(i,j)->getCreaturesNbr())-1) << " yTextPush : " << 350 << std::endl;
                            break;
                        default:
                            //std::cout << "TestsRender : default  elemType : " << tab.get(i,j)->getElemType() << std::endl;
                            //std::cout << "erreur définition coordonnées textures" << std::endl;
                            listXTextChars.push_back(350);
                            listYTextChars.push_back(350);
                            break;
                    }

                } else {
                    unsigned int height = 5, width = 7;
                    if (!((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) || (i == height - 1 && j == width - 1) || (i == height - 1 && j == width - 2) || (i == height - 2 && j == width - 1))) {
                        listXTextChars.push_back(450);
                        listYTextChars.push_back(450);
                    }
                }
            }
        }

        // Coordonnées du tableau correspondant à la coordonnée i de la liste
        // Initialisees sur la premiere case de la grille AFFICHEE
        int xi = 0, yi = 2;

        for (int i = 0; i < 29; i++) {
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
                        yi = 0;
                        shift = i - 24;
                        break;
                    default:
                        shift = i;
                }
            }
            else {
                shift = shift;
            }


            // On initialise un Tile pour le groupe de creatures en i_eme position 
            Tile charsTile(listXTextChars[i], listYTextChars[i]);

            // S'il y a une cellule en position i du tableau de creatures
            if (NULL != tab.get(xi, yi)) {
                //std::cout << "xi : " << xi << " yi : " << yi << " et i : " << i << std::endl;
                //std::cout << "x et y : " << x << " " << y << std::endl;
            }

            // On fixe la position du groupe de creatures dans l'affichage final
            this->surface->setFinalLocation(i, shift, x, y, charsTile);
            // On fixe la position du sprite dans l'image texture de base
            this->surface->setTextureLocation(i, charsTile);

            shift += 1;
            yi = (yi + 1) % 7;

        }
    }
}
