#include <iostream>
#include "classdef.h"

using namespace std;

class Third;

int main(void)
{
    //StaticBase b;

   Derived2 d;

    StaticBase* pb = &d;

    Third* pT = new Third;

    delete pT;

    return 0;
}
