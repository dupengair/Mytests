#pragma once

#include <iostream>
#include "classdef.h"


using std::cout;
using std::endl;

namespace template_test
{
    template<typename T>    
    class Array {
        public:
            T t;
            Array(T t):t(t) {}
    };

    template<typename T>
    class RParam<Array<T> > {
        public:
            typedef const Array<T>& Type;
    };


     
    class MyClass1 {
        public:
            MyClass1() {}
            MyClass1(const MyClass1 &) {
                std::cout << "MyClass1 copy constructor called\n";
            }
    };

    class MyClass2 {
        public:
            MyClass2() {}
            MyClass2(const MyClass2 &) {
                std::cout << "MyClass2 copy constructor called\n";
            }
    };



    template<>
    class RParam<MyClass2> {
        public:
            typedef MyClass2 Type;
    };


    template<typename T1, typename T2>
    void foo_core(typename RParam<T1>::Type p1, typename RParam<T2>::Type p2)
    {
        check<typename RParam<T1>::Type>();
        check<typename RParam<T2>::Type>();
    }

    template<typename T1, typename T2>
    void foo(const T1& p1, const T2& p2)
    {
        foo_core<T1, T2>(p1, p2);
    }  











    
};
