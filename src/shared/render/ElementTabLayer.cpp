#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "ElementTabLayer.h"
#include "CellTileSet.h"
#include "CharsTileSet.h"
#include "../state/SimpleCell.h"

// Type : 0 = Cellules, 1 = Creatures
namespace render{
    
    ElementTabLayer::ElementTabLayer(const std::shared_ptr<state::ElementTab>& tab, int type) : tab(tab), type(type){
        if (!type)
            this->tileset = std::shared_ptr<CellTileSet>(new CellTileSet());
        else
            this->tileset = std::shared_ptr<CharsTileSet>(new CharsTileSet());
    }
    
    void ElementTabLayer::initSurface() {
        
        int x = (!type) ? 311 : 0;
        int y = (!type) ? 187 : 0;
        int shift = 0;
        
        if (!type) 
{
            this->surface->loadTexture("hexa.png");
            this->surface->initQuads(29);
            int halfWidth = 51;
            
            // Affichage des cellules de la map :
            for (int i = 0; i < 29; i++) {
                
                state::Element elem = *(this->tab->get(i,0)); 
                Tile tuile = this->tileset->getTile(elem);
                
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
                this->surface->setFinalLocation(i, x + shift*2*halfWidth, y, tuile);
           
                shift += 1;
            }
        }
        
        else if (type)
        {
            
        }
        
        else
            std::cout << "Le type d'ElementTabLayer n'a pas été choisi correctement !\n" << std::endl;

        
        
//        //Initialisation des cellules
//        if(type==0){
//            //On place les 4 cellules spéciales
//            //on détermine leurs coordonnées
//            std::vector<std::vector<int> > lcoordonees;
//            std::vector<std::vector<int> > lforbid(6);
//            lforbid[0][0]=0;lforbid[1][0]=1;lforbid[2][0]=0;lforbid[3][0]=6;lforbid[4][0]=5;lforbid[5][0]=6;
//            lforbid[0][1]=0;lforbid[1][1]=0;lforbid[2][1]=1;lforbid[3][1]=3;lforbid[4][1]=4;lforbid[5][1]=4;
//            
//            for(int i=0; i<4; i++){
//            //On remplit la map de cellules simples aléatoires (pour le moment)
//                std::vector<int> c(2);
//                c[0]=rand()%7;
//                c[1]=rand()%5;
//                while((std::find(lforbid.begin(),lforbid.end(),c)!=lforbid.end())&&(std::find(lcoordonees.begin(),lcoordonees.end(),c)!=lcoordonees.end())){
//                    c[0]=rand()%7;
//                    c[1]=rand()%5;
//                }
//                lcoordonees.push_back(c);
//                std::cout << "x : " << c[0] << " y : " << c[1] << std::endl;
//            }
//        }
//        
//        //Initialisation des groupes de créatures
//        if(type==1){
//            
//            
//        }
    }
    
}
