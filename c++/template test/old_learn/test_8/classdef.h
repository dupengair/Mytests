#pragma once

#include <iostream>

using std::cout;
using std::endl;

namespace template_test
{

    template <typename T>
    class IsClassT {
        private:
            typedef char One;
            typedef struct { char a[2]; } Two;
            template<typename C> static One test(int C::*);
            template<typename C> static Two test(...);
        public:
            enum { Yes = sizeof(IsClassT<T>::test<T>(0)) == 1 };
            enum { No = !Yes };
    };

    template<typename T>
    void check()
    {
        if (IsClassT<T>::Yes) 
            cout << " is class " << endl;
        else
            cout << " not a class " << endl;
    }

    template<typename T>
    void check(T)
    {
        check<T>();
    }
    


    template<bool C, typename Ta, typename Tb>
    class IfThenElse;

    template<typename Ta, typename Tb>
    class IfThenElse<true, Ta, Tb> {
        public:
            typedef Ta ResultT;
    };
          
    template<typename Ta, typename Tb>
    class IfThenElse<false, Ta, Tb> {
        public:
            typedef Tb ResultT;
    };



/*
    template<typename T>
    class RParam {
        public:
            typedef typename IfThenElse<sizeof(T) < 2* sizeof(void*), T, T const&>::ResultT Type;
    };
*/

    template<typename T>
    class RParam {
        public:
            typedef typename IfThenElse<IsClassT<T>::No, T, T const&>::ResultT Type;
    };  
 

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
