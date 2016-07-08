#include <iostream>
#include "classdef.h"

using namespace template_test;

class MyClass {};

class MyStruct {};

union MyUnion {};

void myfunc() { }

enum E{e1} e;

int main(void)
{
    std::stack<double> s;
    print_element_type(s);

    std::cout << "int: ";
    check<int>();

    std::cout << "MyClass: ";
    check<MyClass>();

    std::cout << "MyStruct: ";
    check<MyStruct>();

    std::cout << "MyUnion: ";
    check<MyUnion>();

    std::cout << "enum: ";
    checkT(e);

    std::cout << "myfunc(): ";
    checkT(myfunc);
    
    return 0;
}
