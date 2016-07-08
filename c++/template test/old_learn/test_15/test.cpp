#include <iostream>

#include "test.h"


using namespace template_test;

using std::cout;
using std::endl;


int main(void)
{

    demo(func_ptr(one), 1);
    demo(func_ptr(seven));
    demo(func_ptr(more));

    return 0;
}



