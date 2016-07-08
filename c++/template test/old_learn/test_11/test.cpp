#include <iostream>


#include "test.h"


using namespace template_test;

using std::cout;
using std::endl;



int main(void)
{
    Array<float> x(100), y(100);

    cout << "before :" << endl << "x = " << endl;
    x.pr();

    cout << endl << "y = " << endl;
    y.pr();

    x = ((float)1.2) * x + x * y;

    cout << endl << "after :" << endl << "x = " << endl;
    x.pr();

    cout << endl;

    return 0;
}



