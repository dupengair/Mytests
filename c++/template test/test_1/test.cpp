#include <iostream>
#include "classdef.h"

using namespace template_test;


int main(void)
{
    int num[] = {1, 2, 3, 4, 5};
    std::cout << "the average value of integer values is: " 
                  << Accum<int>::accum(&num[0], &num[5]) /5 
                  << '\n';

    char name [] = "templates";
    int length = sizeof(name) -1;

    std::cout << "the average value of char values in " << name << " is: " 
                  << Accum<char>::accum(&name[0], &name[length]) /length 
                  << '\n';  

    std::cout << "the multiply value of integer values is: " 
                  << Accum<int, MultiPolicy>::accum(&num[0], &num[5])
                  << '\n';
    
    return 0;
}
