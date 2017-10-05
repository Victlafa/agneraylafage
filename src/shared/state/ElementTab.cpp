/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ElementTab.h"
#include <iostream>

namespace state
{
    // Constructor :
    ElementTab::ElementTab (size_t width, size_t height)
    {
        this->width = width;
        this->height = height;
        
        try
        {
            this->list = new std::vector<std::unique_ptr<Element>>();
        }
        
        catch(std::bad_alloc &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    
    ElementTab::~ElementTab() 
    { delete this; }
    
    // Getters and setters :
    
    size_t ElementTab::getWidth (){
        return this->width;
    }
    
    size_t ElementTab::getHeight (){
        return this->height;
    }
    
    void ElementTab::resize (size_t width, size_t height){
        this->width = width;
        this->height = height;
    }
    
    const Element& ElementTab::get (int i, int j){
        return *(list->at(i*width + j));
    }
    
    void ElementTab::set (Element elem, int i, int j){
        int cpt = 0;
        for (auto Iter = list->begin(); Iter != list->end(); Iter++) {
            if (cpt == (int)(i * width + j)) {
                // Quand on a trouvé la bonne position, on insère le nouvel élément dans la liste :
                list->insert(Iter, 1, elem);
                
                break;
            }
            cpt += 1;
        }
        
    }
    
    const Element& ElementTab::operator()(int i, int j){
        return *(list->at(i*width + j));
    }
    
    TypeID ElementTab::getTabType() const{
        return this->tabType;
    }
    
    void ElementTab::setTabType(TypeID tabType){
        this->tabType = tabType;
    }
    
    
    
    
};