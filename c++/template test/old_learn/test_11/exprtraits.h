#pragma once

#include <iostream>
#include <stddef.h>
#include <cassert>

using std::cout;
using std::endl;

namespace template_test
{

    template <typename T> class A_Scalar;

    template <typename T> 
    class A_Traits;

    template <typename T>
    class A_Traits {
    public:
        typedef T const& ExprRef;
    };

    template <typename T>
    class A_Traits<A_Scalar<T> > {
    public:
        typedef A_Scalar<T> ExprRef;
    }; 

};  
