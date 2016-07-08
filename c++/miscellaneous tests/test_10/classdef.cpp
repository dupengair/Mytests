

#include "classdef.h"

size_t StaticBase::numObjects = 0;

StaticBase::StaticBase(){

    try {
        if(numObjects >= 1)
            throw TooManyObjects();
        }
    catch(TooManyObjects& e)
        {
        cout << "can't define more than 1 objects" << endl;
        }

    ++numObjects;

    cout << numObjects << " StaticBase class constructed" << endl;

}

StaticBase::~StaticBase()
{
    cout << " StaticBase class destructed" << endl;
}







Derived::Derived()
{
    cout << " Derived class constructed" << endl;
}

Derived::~Derived()
{
    cout << " Derived class destructed" << endl;
}





