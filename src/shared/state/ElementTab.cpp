/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ElementTab.h"
#include "CreaturesID.h"
#include "Cell.h"
#include "SimpleCell.h"
#include "CreaturesGroup.h"
#include <iostream>

namespace state
{
    // Constructor :
    ElementTab::ElementTab (TypeID type, size_t width, size_t height)
    {
        this->width = width;
        this->height = height;
        tabType = type;
       
        list.resize(width*height);
        
        if (type == TypeID::CELL)
        {
            for (int i = 0; i < (int)(width*height); i++)
            {
                //this->list.push_back(std::move(std::unique_ptr<Element>(new Element())));
                list.at(i).reset(new SimpleCell(SimpleCellID::SAND, "wood", 0, 0, 0));
                //this->list.at(i) = std::unique_ptr<Cell>(new Cell());
                //std::cout << list[i].get() << std::endl;
            }
                
            
        }
        
        else if (type == TypeID::CREATURESGROUP)
        {
            this->list.reserve(width*height);
            int** intRand1 = new int*[3];
            int rand11;
            int rand12;
            
            // On va tirer au sort des coordonnees pour placer des creatures :
            for (int j = 0; j < 3; j++)
            {
                intRand1[j] = new int[2];
                
                do
                {
                    rand11 = rand()%height;
                    rand12 = rand()%width;
                }
                while (rand11 == intRand1[j][0] || rand12 == intRand1[j][1]);

                intRand1[j][0] = rand11;
                intRand1[j][1] = rand12;

                this->set(std::unique_ptr<CreaturesGroup>(new CreaturesGroup(CreaturesID::BLACKSMITH)).get(),rand11,rand12);
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