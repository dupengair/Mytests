#include <iostream>

#include "product.h"


using std::cout;
using std::string;

namespace test_boost {

    Product::Product(string name):name(name)
    {
        cout << "Constuct Product : " << name << endl;
    }

    Product::~Product()
    {
        cout << "Destuct Product : " << name << endl;
    }

    Product::Product(const Product& rhs)
    {
        name = rhs.name;
    }

    Product& Product::operator=(const Product& rhs)
    {
        this->name = rhs.name;
        return *this;
    }
    
    void Product::show(void)
    {
        cout << "show Product : " << name  << endl;
    }


    Product_A::Product_A(string name):Product(name)
    {
        cout << "Constuct Product_A : " << name  << endl;
    }

    Product_A::~Product_A()
    {
        cout << "Destuct Product_A : " << name <<  endl;
    }

    void Product_A::show(void)
    {
        cout << "show Product_A : " << name  << endl;
    }

}
