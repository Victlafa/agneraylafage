/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ElementTabFactory.h"

namespace state
{
    ElementTabFactory::~ElementTabFactory (){
        delete(this);
    }
    
    ElementTab* ElementTabFactory::newInstance (char id, size_t height, size_t width) const
    {
        return new ElementTab(TypeID::CELL,width,height);
        
    }
    
    void ElementTabFactory::registerType (char id, AElementTabAlloc* elem)
    {
        this->list[id] = elem;
    }
    
    static ElementTabFactory* createDefault ()
    {
        return new ElementTabFactory();
    }
    
    const std::map<char,AElementTabAlloc*>& ElementTabFactory::getList() const
    {
        return this->list;
    }
    
    void ElementTabFactory::setList(const std::map<char,AElementTabAlloc*>& list)
    {
        this->list = list;
    }
}
