#include <iostream>
#include "classdef.h"

using namespace std;

extern "C" {
void test_sym(int& a);
}

void test_sym(int& a)
{
    a = 1;
}



int main()
{/*
    cout << "test_7 start" << endl;

    //Base b;
    //b.NVI_Interface();

    Derived d;
    d.test();
    d.i = 10;

    Derived2 d2;
    d2.test2();
    //d2.i=11;
    //d2.NVI_Interface();

    
    Base* pb;
    //pb=&d2;*/


       
}
