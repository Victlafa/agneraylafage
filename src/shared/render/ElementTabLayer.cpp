#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "ElementTabLayer.h"


namespace render{
    
    ElementTabLayer::ElementTabLayer(const state::ElementTab& tab){
        this->tab = tab;
    }
    
    void initSurface(int type){
        //Initialisation des cellules
        if(type==0){
            //On place les 4 cellules spéciales
            //on détermine leurs coordonnées
            std::vector<std::vector<int> > lcoordonees;
            std::vector<std::vector<int> > lforbid(6);
            lforbid[0][0]=0;lforbid[1][0]=1;lforbid[2][0]=0;lforbid[3][0]=6;lforbid[4][0]=5;lforbid[5][0]=6;
            lforbid[0][1]=0;lforbid[1][1]=0;lforbid[2][1]=1;lforbid[3][1]=3;lforbid[4][1]=4;lforbid[5][1]=4;
            
            for(int i=0; i<4; i++){
            //On remplit la map de cellules simples aléatoires (pour le moment)
                std::vector<int> c(2);
                c[0]=rand(0,7)%7;
                c[1]=rand(0,5)%5;
                while((std::find(lforbid.begin(),lforbid.end(),c)!=lforbid.end())&&(std::find(lcoordonees.begin(),lcoordonees.end(),c)!=lcoordonees.end())){
                    c[0]=rand(0,7)%7;
                    c[1]=rand(0,5)%5;
                }
                lcoordonees.push_back(c);
                std::cout << "x : "+c[0]+" y : "+c[1] << std::endl;
            }
        }
        
        //Initialisation des groupes de créatures
        if(type==1){
            
            
        }
    }
    
}
