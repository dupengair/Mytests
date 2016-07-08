#include <iostream>
#include "classdef.h"

using namespace template_test;

void incr(int& a) {
    ++a;
}

void print(int a) {
    std::cout << a << std::endl;
}


int main(void)
{

    int x = 7;
    apply(x, incr);
    apply(x, print);

    return 0;
}
