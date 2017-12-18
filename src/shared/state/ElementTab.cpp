#include "ElementTab.h"
#include <iostream>
#include <map>

using namespace std;

namespace state
{
    // Constructor :
    ElementTab::ElementTab(size_t width, size_t height) : list(width*height) {
        this->width = width;
        this->height = height;
        
    }
    
    ElementTab::~ElementTab() {}
    
    // Getters and setters :
    const size_t& ElementTab::getWidth () const{
        return this->width;
    }
    
    void ElementTab::setWidth(const size_t& width) { this->width = width; }
    
    const size_t& ElementTab::getHeight () const{
        return this->height;
    }
    
    void ElementTab::setHeight(const size_t& height) { this->height = height; }
    
    void ElementTab::resize (size_t width, size_t height){
        this->width = width;
        this->height = height;
    }
    
    const std::unique_ptr<Element>& ElementTab::get (int i, int j) const{
        //if(list.at(i*width+j)!=NULL)
        //    std::cout << "ElementTab.cpp get : getelemtype :" << list.at(i*width + j)->getElemType() << std::endl;
        return list.at(i*width + j);
    }
    
    const std::unique_ptr<Element>& ElementTab::getByNumber (int number) const{
        return list.at(number);
    }
    
    void ElementTab::set (Element* elem, int i, int j){
        list.at(i*width + j).reset(elem);
        //std::cout << "ElementTab : set : getElemType : " << elem->getElemType() << std::endl;
        
        if (elem != nullptr)
        {
            list.at(i*width + j)->setX(i);
            list.at(i*width + j)->setY(j);
        }
        
    }
    
    const std::unique_ptr<Element>& ElementTab::operator()(int i, int j) const{
        return list.at(i*width + j);
    }
    
    TypeID ElementTab::getTabType() const{
        return this->tabType;
    }
    
    void ElementTab::setTabType(TypeID tabType){
        this->tabType = tabType;
    }
    
    const std::vector<std::unique_ptr<Element> >& ElementTab::getList() const
    {
        return this->list;
    }
    
    void ElementTab::poisonCell(bool poison, int i, int j)
    {
        if (poison)
        {
            get(i,j)->setCellState(CellState::POISONED);
            
            //(Cell)(*pCell,CellState::POISONED); //.setCellState(CellState::POISONED);
            //std::cout << "etat de la cellule : " << this->get(i,j)->getCellState() << std::endl;
            //std::cout << "La case (" << i << "," << j << ") a normalement ete empoisonnee\n" << std::endl;
        }
        
        else
        {
            get(i,j)->setCellState(CellState::NORMAL);
        }
    }
    
    bool ElementTab::isPoisoned(int i, int j){
        if (get(i,j)->getCellState() == CellState::POISONED)
            return true;
        else
            return false;
    }
    
    bool ElementTab::clearList ()
    {
        this->list.clear();
        this->list.resize(height*width);
        
        if (list.size() == height*width)
            return true;
        else
            return false;
    }
    
};