#include <iostream>
#include "classdef.h"
#include <stdlib.h>
#include <typeinfo>


using namespace template_test;




int main(void)
{
    Array<int> a1(2);
    Array<bool> a2(true);
    Array<int> a3 = a1 + a2;

    std::cout << typeid(a1+a2).name() << " = " << a3.t <<std::endl;

    return 0;
}



