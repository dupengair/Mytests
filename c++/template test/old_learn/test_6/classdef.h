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





};
