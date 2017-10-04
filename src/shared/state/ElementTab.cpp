/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ElementTab.h"

namespace state
{
    // Constructor :
    ElementTab::ElementTab (size_t width = 0, size_t height = 1)
    {
        this->width = width;
        this->height = height;
        this->list = new std::vector<std::unique_ptr<Element>>();
        if (list == NULL)
            throw std::bad_alloc("La liste des éléments d'ElementTab doit être initialisée !");
    }
    
    ElementTab::~ElementTab() 
    { delete this; }
    
    // Getters and setters :
    
    size_t const ElementTab::getWidth (){
        return this->width;
    }
    
    size_t const ElementTab::getHeight (){
        return this->height;
    }
    
    size_t ElementTab::add (Element* elem){
        this->list.push_back(elem);
    }
    
    void ElementTab::resize (size_t width, size_t height){
        this->width = width;
        this->height = height;
    }
    
    Element* const ElementTab::get (int i, int j = 0){
        return list[i*width + j];
    }
    
    void ElementTab::set (int i, int j = 0, Element* elem){
        list[i*width + j] = elem;
    }
    
    const Element& ElementTab::operator()(int i, int j = 0) const{
        return list[i*width + j];
    }
    
    // Setters and Getters
    const Element& ElementTab::getComposedOf() const{
        return this->composedOf;
    }
    
    void ElementTab::setComposedOf(const Element& Compose){
        this->composedOf = Compose;
    }
    
    
};