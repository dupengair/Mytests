#include <iostream>
#include "classdef.h"
#include <stdlib.h>

using namespace template_test;

void incr(int& a)
{
    ++a;
    std::cout << a << std::endl;
}

void print(int a)
{
    std::cout << a << std::endl;
}

int main(void)
{
    int x = 7;
    apply(x, print);
    apply(x, incr);

    return 0;
}



