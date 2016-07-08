#include <iostream>

#include "test.h"


using namespace template_test;

using std::cout;
using std::endl;

class Test {
public:
    Test(int t): i(t) { cout << "ctor" << endl; }
    Test(const Test&) { cout << "copy ctor" << endl; }
private:
    int i;
};

int main(void)
{

    enum TEST{ One = 1, Two };
    int t;

    // IsEnum(One);
    IsEnum(t);



    return 0;
}



