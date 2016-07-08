#include <iostream>

#include "test_4.h"
#include "mycout.h"

using std::cout;
//using MYCOUT::cout;
using std::endl;

product::product(char * name)
{
    cout << "construct product : " << name << endl;
}

product::~product()
{
    cout << "destruct product" << endl;
}

void product::display2(int ID)
{
    cout << "product ID = " << ID <<endl;
}

void product::display3(int ID)
{
    cout << "product::display " << ID << endl;
}

void product::display4()
{
    cout << "product::display4 " << endl;
}

void product::destroy(void)
{
    delete this;
}

void product::ppp(void)
{
    cout << "product::ppp " << endl;
}



product_A::product_A(char * name):product(name)
{
    cout << "construct product_A : " << name << endl;
}

product_A::~product_A()
{
    cout << "destruct product_A " << endl;
}

void product_A::display(int ID)
{
    cout << "product_A ID " << ID <<endl;
}

void product_A::display2(int ID)
{
    cout << "product_A ID = " << ID <<endl;
}

void product_A::display3()
{
    //product::display3();
    cout << "product_A::display3" << endl;
}

void product_A::display4()
{
    cout << "product_A::display4 " << endl;
}

void product_A::haha()
{
    cout << "product_A::haha " << endl;
}

void product_A::ppp(void)
{
    cout << "product_A::ppp " << endl;
}


test::test()
{
    cout << "construct test  " << endl;
}

test::~test()
{
    cout << "destruct test" << endl;
}

void test::display()
{
    cout << "test : display " << endl;
}

ttest::ttest()
{
    cout << "construct ttest  " << endl;
}

ttest::~ttest()
{
    cout << "destruct ttest" << endl;
}

void ttest::display()
{
    cout << "ttest : display " << endl;
}