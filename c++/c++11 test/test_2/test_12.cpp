#include <iostream>
#include <string>
#include "test.h"

#include <stdio.h>


using std::cout;
using std::endl;



struct A {

        A(int a):_a(a) { cout << "in class A: " << _a << endl; }
private:
        int _a;
};

struct B:A  {
    using A::A;
private:
        int _b;
};

template<typename T>  
inline T& max(T a, T b) {    
    return a > b ? a : b;
}


struct C {
    C() { cout << _i << endl; }
    C(int i):C() { _i = i; } 
private:
     int _i {0};
};

void func(int& i)
{
    cout << "i = " << i << endl;
}

template <unsigned int I>  
    class Ret {
};

int xxx(int) { cout << "int " ; }
float xxx(float) { cout << "float " ; }
template <typename T> 
    Ret<sizeof(xxx((T)0))> f(T) {
    }


double foo(int a) { return (double(a) + 0.1); }
int foo(double b) { return (int) b; }

template <typename T>
auto Forward(T t) -> decltype(foo(t)) {
        return foo(t);
}




int main(void)
{
    B b(1);

    cout<< max("abc", "abcd") <<endl;

    C c(2);

   // f(1);

    float a = 1.01;
    cout << sizeof(int(0)) << endl;

    int aa = 1;
    cout << sizeof(float(0)) << endl;

    cout << Forward(2) << endl;; 		//2.1
    cout << Forward(0.5) << endl;		//0
		
    return 0;
}
