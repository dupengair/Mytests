#include <iostream>


#include "test.h"


using namespace template_test;



int main(void)
{
    MyClass1 c1;
    MyClass2 c2;

    check<MyClass1>();
    check<MyClass2>();
    
    foo(c1, c2);
    
    
    return 0;
}



