#ifndef __CLASSDEF_H__
#define __CLASSDEF_H__

#include <iostream>
#include "class.h"


namespace template_test
{

    template<typename T>
    MyChar<T>::MyChar(T a):t(a) { 
        cout << "MyChar init: " << a << endl;
    }

    
    template<typename T>
    void MyChar<T>::get(void)   {
        cout << "get t: " << t << endl;
    }
}

#endif