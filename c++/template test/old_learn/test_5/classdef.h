#pragma once

#include <iostream>

using std::cout;
using std::endl;

namespace template_test
{

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


    template<typename T1, typename T2>
    class Promotion {
        public:
            typedef typename IfThenElse<(sizeof(T1) > sizeof(T2)), T1, 
                typename IfThenElse<(sizeof(T1) < sizeof(T2)), T2, void>::ResultT
                    >::ResultT ResultT;
    };

    template<typename T>
    class Promotion<T, T> {
        public:
            typedef T ResultT;
    };
                    

    
    #define MK_PROMOTION(T1, T2, Tr) \
        template<> \
        class Promotion<T1, T2> { \
            public: \
                typedef Tr ResultT; \
        };\
        \
        template<> \
        class Promotion<T2, T1> { \
            public: \
                typedef Tr ResultT; \
        }
          

    MK_PROMOTION(bool, char, int);
    MK_PROMOTION(bool, unsigned char, int);
    MK_PROMOTION(bool, signed char, int);
    MK_PROMOTION(int, char, int);


template<typename T>    
class Array {
    public:
        T t;
        Array(T t):t(t) {}
};

template<typename T1, typename T2>
class Promotion<Array<T1>, Array<T2> > {
    public:
        typedef Array<typename Promotion<T1, T2>::ResultT> ResultT;
};

template<typename T>
class Promotion<Array<T>, Array<T> > {
    public:
            typedef Array<typename Promotion<T, T>::ResultT> ResultT;
};



template<typename T1, typename T2>    
typename Promotion<Array<T1>, Array<T2> >::ResultT
    operator+ (Array<T1> const& a1, Array<T2> const& a2) {
       return a1.t + a2.t;
};




};
