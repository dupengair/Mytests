#include <iostream>
#include <string>
#include "test.h"

#include <stdio.h>


using std::cout;
using std::endl;


struct A { int a; virtual void func() { cout << "A" << endl; } };
struct B: public A { void func() { cout << "B" << endl; } };

struct init11 { 
		int a=1;			//非静态不能用()
		std::string str{"sss"};
	};

template<typename T, typename N  = int>
void func(T a, N b) {
    cout << a << b << endl;
}

template void func<int>(int, int);
template void func<float>(float, int);




int main(void)
{
    mff(aa(), 3, 2);
    
    /*Test Variadic Template1*/
    cout << endl << "test1 ->" << endl;
    typedef decltype(std::cout) cout_type;
    auto endl = std::endl<cout_type::char_type, cout_type::traits_type>;
    output(1, 0.3, (void*)nullptr, "string", 'c');
    output(1, 0.3, (void*)nullptr, "string", 'c', endl);

    /*Test Variadic Template2*/
    cout << endl << "test2 ->" << endl;
    Type1 t1(1);
    Type2 t2(2);
    Type3 t3(3);
    Type4 t4(4);
    Type5 t5(5);
    Type6 t6(6);

    CallMtd(&t1, &t2, &t3, &t4, &t5, &t6);
    CallMtd();
    
    /*Test Variadic Template3*/
    cout << endl << "test4 ->" << endl;
    myPrintf( "a%bcde%fghij%kl%mn\n", 12, "interesting", 8421, "very_interesing" );


    A b;
    b.func();
    b.~A();
    new (&b) B;
    b.func();

    
    
    return 0;
}
