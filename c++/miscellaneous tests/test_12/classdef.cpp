#include <iostream>
#include <string.h>
#include "classdef.h"

using namespace std;


int Base::count = 0;
Base::Base(){
    cout << " Base class constructed, count = " << ++count << endl;
//    memset(this, 0, sizeof(Base)) ;

}

Base::~Base()
{
    cout << " Base class destructed" << endl;
}


int Base::testbm(void)
{
    cout << "in Base class :" << bm1 << " , " << bm2 << endl;
}



Derived::Derived()
{
    cout << " Derived class constructed" << endl;
    //memset(this, 0, sizeof(Derived)) ;
}

Derived::~Derived()
{
    cout << " Derived class destructed" << endl;
}



int Derived::testbm(void)
{
      cout << "in Derived class :" << dm1 << " , " << dm2 << endl;
}

