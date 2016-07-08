//#include <iostream>
#include "class.h"

using namespace template_test;



int main(void)
{

    MyChar<int> m(1);
    m.get();

    MyChar<float> n(1.1);
    n.get();

    MyChar<double> l(1.1);
        
    return 0;
}
