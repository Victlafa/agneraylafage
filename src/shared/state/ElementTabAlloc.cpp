/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ElementTabAlloc.h"

namespace state
{
    template <class E,typename ID> ElementTabAlloc<E,ID>::ElementTabAlloc (ID id)
    {
        this->id = id;
    }
    
    template <class E,typename ID> ElementTab* ElementTabAlloc<E,ID>::newInstance (size_t height, size_t width)
    {
        return new ElementTab(height*width);
    }
    
    template <class E,typename ID> const ID& ElementTabAlloc<E,ID>::getId() const
    {
        return this->id;
    }
    
    template <class E,typename ID> void ElementTabAlloc<E,ID>::setId(const ID& id)
    {
        this->id = id;
    }
}
