#include <iostream>
#include "classdef.h"
#include <stdlib.h>
#include <typeinfo>


using namespace template_test;

class MyClass {
    int a;
};

void func() {
}


int main(void)
{
    std::cout << "int" << std::endl;
    check<int>();
    
    std::cout << "MyClass" << std::endl;
    check<MyClass>();

    std::cout << "func" << std::endl;
    check(func);
    
    return 0;
}



