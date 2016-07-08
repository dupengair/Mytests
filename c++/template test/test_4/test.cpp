#include <iostream>
#include "classdef.h"

using namespace template_test;

template<typename T1, typename T2>
void foo(typename RParam<T1>::Type p1, typename RParam<T2>::Type p2)
{
    std::cout << "foo called" << std::endl;
}

template<typename T1, typename T2>
void foo_core(typename RParam<T1>::Type p1, typename RParam<T2>::Type p2)
{
    std::cout << "foo_core called" << std::endl;
}


template<typename T1, typename T2>
void foo1(T1 const&  p1, T2 const& p2)
{
    foo_core<T1, T2>(p1, p2);
}

void test(MyClass2 mc)
{
    std::cout << "test called" << std::endl;
}


int main(void)
{
    MyClass1 mc1;
    MyClass2 mc2(2);
    foo<MyClass1, MyClass2>(mc1, mc2);
    foo1<MyClass1, MyClass2>(mc1, mc2);
    test(mc2);
    
    return 0;
}

