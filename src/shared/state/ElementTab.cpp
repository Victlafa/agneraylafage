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
    
    Element* ElementTab::get (int i, int j){
        return list->at(i*width + j);
    }
    
    void ElementTab::set (std::unique_ptr<Element> elem, int i, int j){
        list->insert(i*width + j,elem);
    }
    
    const Element& ElementTab::operator()(int i, int j){
        return list->at(i*width + j);
    }
    
    
    
    
};