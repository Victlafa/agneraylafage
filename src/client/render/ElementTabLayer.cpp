#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "ElementTabLayer.h"
#include "CellTileSet.h"
#include "CharsTileSet.h"
#include "state/SimpleCell.h"

// Type : 0 = Cellules, 1 = Creatures
namespace render{
    
    ElementTabLayer::ElementTabLayer(state::ElementTab tab, int type) : tab(tab), type(type){
        if (!type)
            this->tileset = std::shared_ptr<CellTileSet>(new CellTileSet());
        else
            this->tileset = std::shared_ptr<CharsTileSet>(new CharsTileSet());
    }
    
    void ElementTabLayer::initSurface() {
        
        int x = 311;
        int y = 187;
        int shift = 0;
        int halfWidth = 0;
        this->surface->initQuads(29);
        
        if (!type) 
        {
            this->surface->loadTexture("hexa.png");
            halfWidth = 51;
        } 
            
        else if (type)
        {
            this->surface->loadTexture("groupes.png");
            halfWidth = 50;
        }
        
        else
            std::cout << "Le type d'ElementTabLayer n'a pas été choisi correctement !\n" << std::endl;

//        const Tile& tuile = this->tileset->getTile(*tab->get(0,0));
//        this->surface->setTextureLocation(0, tuile);
//        this->surface->setFinalLocation(0, x + shift * 2 * halfWidth, y, tuile);
        
        // Affichage des cellules de la map :
        for (int i = 0; i < (int)tab.getHeight(); i++) {
            for (int j = 0; j < (int)tab.getWidth(); j++) {
                
                if (tab.get(i, j) != NULL) {
                    Tile tuile = ((this->tileset).get())->getTile(*(tab.get(i,j).get()));
                    std::cout << "Hauteur de la tuile (" << i << "," << j << ") :" << tuile.getHeight() << std::endl;

                    if (i == 5 || i == 11) {
                        x -= halfWidth;
                        y += 86;

                        switch (i) {
                            case 5:
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

                        switch (i) {
                            case 18:
                                shift = i - 18;
                                break;
                            case 24:
                                shift = i - 24;
                                break;
                            default:
                                shift = i;
                        }
                    }
                    else
                        shift = shift;


                    this->surface->setTextureLocation(i, tuile);
                    this->surface->setFinalLocation(i, x + shift * 2 * halfWidth, y, tuile);

                    shift += 1;
                }
            }
        }
        
    }
}


