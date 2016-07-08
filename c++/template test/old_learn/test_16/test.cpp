#include <iostream>

#include "test.h"


using namespace template_test;

using std::cout;
using std::endl;


int main(void)
{

    cout << compose(Abs(), Sine())(0.5) << endl;

    print_values(Abs());
    cout<<endl;

    print_values(Sine());
    cout<<endl;
    
    print_values(compose(Abs(), Sine());
    cout<<endl;

    print_values(compose(Sine(), Abs());
    cout<<endl;
    

    return 0;
}



