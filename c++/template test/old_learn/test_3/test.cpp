//#include <iostream>
#include "classdef.h"
#include <stdlib.h>

using namespace template_test;

static int* a = new int();
static int* b = (int*)malloc(sizeof(int));

int main(void)
{
    Test<int> t;
    t.func();
    
    DX d;
    d.func();

    //D2<int*> d2;
    //int* p;
   // g(d2, p);

    return 0;
}



