#include <iostream>


#include "test.h"


using namespace template_test;

using std::cout;
using std::endl;



int main(void)
{

    cout << sizeof(NoOptimizable<empty>) << endl;
    cout << sizeof(NoOptimizable<char_1>) << endl;
    cout << sizeof(Optimizable<empty>) << endl;
    cout << sizeof(Optimizable<char_1>) << endl;

	
    return 0;
}



