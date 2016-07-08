//#include <iostream>
#include "classdef.h"

using namespace template_test;


int main(void)
{
    testMemberTemplate<int> a(5);
    a.showPriMember<char>();
    
    return 0;
}
