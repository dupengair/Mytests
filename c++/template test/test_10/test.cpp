#include <iostream>
#include <vector>
#include <typeinfo>

#include "classdef.h"

using namespace template_test;

double seven() 
{
    return 7.0;
}

std::string more()
{
    return std::string("more");
}

template <typename FunctorT>
void demo(FunctorT func)
{
    cout << "Functor returns type " 
            << typeid(typename FunctorT::ReturnT).name() << endl
            << "Functor return value " << func() << endl;
}

int main()
{
    std::vector<int> v(10);

    initialize<FunctionReturningIntWrapper<random_int> > (v);
    
    for(std::vector<int>::size_type i=0; i<v.size(); ++i) {
        std::cout << "coll[" << i << "]: " << v[i] << std::endl;;
        }

    demo(func_ptr(seven));
    demo(func_ptr(more));
}

