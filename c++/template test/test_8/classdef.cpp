#include <iostream>
#include "classdef.h"


namespace template_test
{

    size_t* alloc_counter()
    {
        return ::new size_t;
    }

    void dealloc_counter(size_t* ptr)
    {
        ::delete ptr;
    }
}
