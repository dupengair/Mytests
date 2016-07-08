#include <iostream>
#include <cmath>
#include <cstdlib>

#include "classdef.h"

using namespace template_test;

#if 0
template <typename T>
class Abs {
    public:
        enum { NumParams = 1 };
        typedef T ReturnT;
        typedef T Param1T;
        
    public:
        T operator() (T v) const {
            return std::abs(v);
            }
};

template <typename T>
class Sine {
    public:
        enum { NumParams = 1 };
        typedef T ReturnT;
        typedef T Param1T;
        
    public:
        T operator() (T a) const {
            return std::sin(a);
            }
};


template<typename FO>
void print_values(FO fo) 
{
    for (int i=-2; i<3; ++i) {
        cout << "f(" << i*0.1 << ") = " << fo(i*0.1) << endl;
        }
}
#else

double add(double a, double b)
{
    return a + b;
}

double twice(double a)
{
    return 2 * a;
}

#endif


int main()
{
#if 0
    cout << compose(Abs<double>(), Sine<double>())(0.5) << endl;

    print_values(Abs<double>());
    print_values(Sine<double>());
    print_values(compose(Abs<double>(), Sine<double>()));
    print_values(compose(Sine<double>(), Abs<double>()));
#else
    cout << "compute (20+7)*2: " << compose(func_ptr(add), func_ptr(twice))(20, 7) << endl;
#endif
    
}

