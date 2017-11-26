#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "ElementTabLayer.h"
#include "CellTileSet.h"
#include "CharsTileSet.h"
#include "state/SimpleCell.h"

// Type : 0 = Cellules, 1 = Creatures
namespace render{
    
    ElementTabLayer::ElementTabLayer(const state::ElementTab& tab, int type) : Layer(), tab(tab), type(type){
        if (!type)
            this->tileset = std::shared_ptr<CellTileSet>(new CellTileSet());
        else if (type)
            this->tileset = std::shared_ptr<CharsTileSet>(new CharsTileSet());
        else
            throw std::runtime_error("Le type donné en entrée du constructeur ElementTabLayer doit etre 0 ou 1");
    }
    
    void ElementTabLayer::initSurface() {
        
        // Les coordonnees x = 311 et y = 187 correspondent à la position de la première cellule de la carte affichee au joueur
        int x = 311;
        int y = 187;
        int shift = 0;
        int halfWidth = 0;
        
        // On ajoute 29 quads à la liste de quads de la surface
        this->surface->initQuads();
        
        // Listes temporaires qui permettront de recuperer les coords donnees par les tiles
//        std::vector<int> listXTile = std::vector<int>();
//        listXTile.reserve(29);
//        std::vector<int> listYTile = std::vector<int>();
//        listYTile.reserve(29);
        
        std::vector<Tile> listTiles(29);
        
        // Si le tableau à afficher est de type cellules
        if (!type) {
            this->surface->loadTexture("hexa.png");
            halfWidth = 51;
            
        }
            
        // Si le tableau à afficher est de type creatures
        else if (type)
        {
            this->surface->loadTexture("groupes.png");
            halfWidth = 50;
        }
        
        // Les autres eventuels cas levent une exception
        else
            throw std::runtime_error("Le type d'ElementTabLayer n'a pas été choisi correctement !\n");

        // On recupere les coordonnees des textures dans l'image de texture associee
        // selon les types d'elements presents dans le tableau
        for (unsigned int i = 0; i < tab.getHeight(); i++) {

            for (unsigned int j = 0; j < tab.getWidth(); j++) {

                if (NULL != tab.get(i, j)) {

                    //listXTile = tileset->getTile(tab->get(i,j))->getX();
                    //listYTile = tileset->getTile(tab->get(i,j))->getY();
                    listTiles.push_back(tileset->getTile(tab.get(i,j)));

                }
            }
        }
        
        // Coordonnées du tableau correspondant à la coordonnée i de la liste
        // Initialisees sur la premiere case de la grille AFFICHEE
        int xi=0, yi=2;
        std::vector<sf::VertexArray> quads;
             
        for (int i = 0; i < 29; i++) 
        {
            // Recuperation de la liste de quads de la surface 
            quads = surface->getQuadsList();
            
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
                xi++;//yi++;
                
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
            
            //std::cout << "xtextcell : " << xTextCell << " ytextcell : " << yTextCell << std::endl;
            //std::cout << "xtextchars : " << xTextChars << " ytextchars : " << yTextChars << std::endl;
            //std::cout << "i : " << i << " xi : " << xi << " yi : " << yi << std::endl;
            
            // S'il y a une cellule en position i du tableau
            if(tab.get(xi,yi)!=NULL){
                
                
                // On fixe la position de la cellule dans l'affichage final
                surface->setFinalLocation(i, shift, x, y, listTiles[i]);
                // On fixe la position du sprite dans l'image texture de base
                surface->setTextureLocation(i, listTiles[i]);

            }
                        
            shift += 1;
            
            //std::cout << "xi et yi : " << xi << " " << yi << std::endl;
            yi = (yi+1)%7;

        }
        
    }
}


