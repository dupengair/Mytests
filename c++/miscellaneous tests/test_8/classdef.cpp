#include "iostream"
#include "classdef.h"

using namespace std;


Base::Base()
{
    //cout << " Base class constructed" << endl;
    i = 101;

}

Base::~Base()
{
  //  cout << " Base class destructed" << endl;
}

void Base::Interface() const
{
    cout << "Interface in Base class " << i << endl;

}

void Base::test1(int a)
{
      cout << "test1 in Base class :" << a << endl;
}



Derived::Derived()
{
   // cout << " Derived class constructed" << endl;
   i=102;

}

Derived::~Derived()
{
   // cout << " Derived class destructed" << endl;
}



void Derived::Interface() const
{
    cout << "Interface in Derived class" << endl;
    //Base::Interface();

}

void Derived::test1(int a)
{
      cout << "test1 in Derived class :" << a << endl;
}

