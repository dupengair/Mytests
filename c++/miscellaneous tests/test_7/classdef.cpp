#include "iostream"
#include "classdef.h"

using namespace std;


Base::Base()
{
    cout << " Base class constructed" << endl;
    i = 0;
}

Base::~Base()
{
    cout << " Base class destructed" << endl;
}

int Base::NVI_Interface() const
{
    cout << "NVI_Interface in Base class" << endl;

    int ret = NVI_Impl();

    return ret;
}

int Base::NVI_Impl() const
{
    cout << "NVI_Impl  in Base class" << endl;

    return 0;
}


Derived::Derived()
{
    cout << " Derived class constructed" << endl;
    i = 1;
}

Derived::~Derived()
{
    cout << " Derived class destructed" << endl;
}


int Derived::NVI_Impl() const
{
    cout << "NVI_Impl  in Derived class" << endl;
    //Base::NVI_Impl();
    
    return 0;
}

void Derived::test()
{
    cout << " Derived test i=" << i << endl;
}


Derived2::Derived2()
{
    cout << " Derived2 class constructed" << endl;
    i = 2;
}

Derived2::~Derived2()
{
    cout << " Derived2 class destructed" << endl;
}

void Derived2::test2()
{
    cout << " Derived2 test2 i=" << i << endl;
}

int Derived2::NVI_Impl() const
{
    cout << "NVI_Impl  in Derived2 class" << endl;
    //Base::NVI_Impl();
    
    return 0;
}
