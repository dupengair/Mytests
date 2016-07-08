#include <iostream>
#include "classdef.h"

using namespace template_test;


int main(void)
{

    BreadSlicer<> bs1;
    bs1.print(1);
    bs1.print(2);
    bs1.print(3);
    bs1.print(4);

    BreadSlicer<Policy3_is<CustomPolicy> > bs2;
    bs2.print(1);
    bs2.print(2);
    bs2.print(3);
    bs2.print(4);
    
    return 0;
}

