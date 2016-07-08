#include <iostream>
#include "classdef.h"

using namespace template_test;

class MyClass {};
void myfunc() {}
enum E{e1};

int main(void)
{
    cout << "int: ";
    check<int>();

    cout << "int&: ";
    check<int&>();
    
    cout << "char[42]: ";
    check<char[42]>();
    
    cout << "MyClass: ";
    check<MyClass>();
    
    cout << "ptr to enum: ";
    E* ptr=0;
    checkT(ptr);
    
    cout << "42: ";
    checkT(42);

    cout << "myfunc(): ";
    checkT(myfunc);

    cout << "memptr to array: ";
    char (MyClass::* memptr)[] = 0;
    checkT(memptr);
    
    return 0;
}

