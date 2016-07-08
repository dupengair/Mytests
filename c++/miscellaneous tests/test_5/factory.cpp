
#include "factory.h"

using namespace std;

product::product(char * name)
{
    cout << "construct product : " << name << endl;
}

product::~product()
{
    cout << "destruct product" << endl;
}

void product::destroy(void)
{
    delete this;
}

product_A::product_A(char * name):product(name)
{
    cout << "construct product_A : " << name << endl;
}

product_A::~product_A()
{
    cout << "destruct product_A " << endl;
}

product_B::product_B(char * name):product(name)
{
    cout << "construct product_B : " << name << endl;
}

product_B::~product_B()
{
    cout << "destruct product_B " << endl;
}


factory::factory()
{
    cout << "construct factory" << endl;
}

factory::~factory()
{
    cout << "destruct factory " << endl;
}


factory_A::factory_A()
{
    cout << "construct factory_A" << endl;
}

factory_A::~factory_A()
{
    cout << "destruct factory_A " << endl;
}

product * factory_A::CreateProduct(char * name)
{
    return new product_A(name);
}

factory_B::factory_B()
{
    cout << "construct factory_B" << endl;
}

factory_B::~factory_B()
{
    cout << "destruct factory_B " << endl;
}

product * factory_B::CreateProduct(char * name)
{
    return new product_B(name);
}

