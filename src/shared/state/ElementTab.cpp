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
        
        std::vector<std::unique_ptr<Element>>* newList = new std::vector<std::unique_ptr<Element>>();
        
        for (int cpt = 0; cpt < (int)list->size(); cpt++) {
            if (cpt != (int)(i*width + j))
                *newList->at((int)(i*width + j)) = *std::move(list->at(cpt));
            else
                *newList->at(cpt) = *std::move(list->at(cpt));
        }
        
        list = newList;
        
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