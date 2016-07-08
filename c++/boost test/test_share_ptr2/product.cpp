#include <iostream>

#include "product.h"

using namespace std;

namespace test_boost {

    Product::Product()
    {
        cout << "Constuct Product" << endl;
    }

    Product::~Product()
    {
        cout << "Destuct Product" << endl;
    }


    Product_A::Product_A(int var):var(var)
    {
        cout << "Constuct Product_A : var = " << var << endl;
    }

    Product_A::~Product_A()
    {
        cout << "Destuct Product_A : var = " << var << endl;
    }

    void Product_A::show(void)
    {
        cout << "show Product_A : var = " << var << endl;
    }

    Product_B::Product_B(int var):var(var)
    {
        cout << "Constuct Product_B : var = " << var << endl;
    }

    Product_B::~Product_B()
    {
        cout << "Destuct Product_B : var = " << var << endl;
    }

    void Product_B::show(void)
    {
        cout << "show Product_B : var = " << var << endl;
    }
    
    self_shared::self_shared(int var):var(var)
    {
        cout << "Constuct self_shared : var = " << var << endl;
    }

    self_shared::~self_shared()
    {
        cout << "Destuct self_shared : var = " << var << endl;
    }

    void self_shared::show(void)
    {
        cout << "show self_shared : var = " << var << endl;
    }
}
