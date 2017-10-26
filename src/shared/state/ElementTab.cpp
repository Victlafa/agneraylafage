/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ElementTab.h"
#include "CreaturesID.h"
#include "Cell.h"
#include "CreaturesGroup.h"
#include <iostream>

namespace state
{
    // Constructor :
    ElementTab::ElementTab (TypeID type, size_t width, size_t height)
    {
        this->width = width;
        this->height = height;
        
        try
        {
            this->list = std::vector<std::unique_ptr<Element>>(width*height);
        }
        
        catch(std::bad_alloc &e)
        {
            std::cerr << e.what() << std::endl;
        }
        
        if (type == TypeID::CELL)
        {
            for (int i = 0; i < (int)(width*height); i++)
            {
                //this->list.push_back(std::move(std::unique_ptr<Element>(new Element())));
                this->list.at(i) = std::unique_ptr<Element>(new Element());
                std::cout << list[i].get() << std::endl;
            }
                
            
        }
        
        else if (type == TypeID::CREATURESGROUP)
        {
            this->list.reserve(width*height);
            int* intRand1 = new int[3];
            int* intRand2 = new int[3];
            int rand1;
            int rand2;
            
            for (int j = 0; j < 3; j++)
            {
                do
                {
                    rand1 = rand()%29;
                    rand2 = rand()%29;
                }
                while (rand1 == intRand1[0] || rand2 == intRand2[0] || rand1 == intRand1[1] || rand2 == intRand2[1]);
                
                intRand1[j] = rand1;
                intRand2[j] = rand2;
                
            }
            
        }
            
        
    }
    
    ElementTab::~ElementTab() {
//        for (auto elem : list)     
//            delete elem;
    }
    
    // Getters and setters :
    
    size_t ElementTab::getWidth () const{
        return this->width;
    }
    
    size_t ElementTab::getHeight () const{
        return this->height;
    }
    
    void ElementTab::resize (size_t width, size_t height){
        this->width = width;
        this->height = height;
    }
    
    const std::unique_ptr<Element>& ElementTab::get (int i, int j) const{
        return this->list.at(i*width + j);
    }
    
    void ElementTab::set (Element* elem, int i, int j){
        this->list.at(i*width + j) = std::unique_ptr<Element>(elem);
    }
    
    Element& ElementTab::operator()(int i, int j) const{
        return *(list.at(i*width + j));
    }
    
    TypeID ElementTab::getTabType() const{
        return this->tabType;
    }
    
    void ElementTab::setTabType(TypeID tabType){
        this->tabType = tabType;
    }
    
    
    
    
};