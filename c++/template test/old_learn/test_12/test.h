#pragma once
#include <cstring>
#include <stddef.h>
#include <iostream>
#include "classdef.h"


using std::cout;
using std::endl;

namespace template_test
{

   template<typename T>
    void IsWhat() {
        if(CompoundT<T>::IsPtrT)
            cout << "IsPtrT" << endl;
        else if(CompoundT<T>::IsRefT)
            cout << "IsRefT" << endl;
        else if(CompoundT<T>::IsArrayT)
            cout << "IsArrayT" << endl;
        else if(CompoundT<T>::IsFuncT)
            cout << "IsFuncT" << endl;
        else if(CompoundT<T>::IsPtrMemT)
            cout << "IsPtrMemT" << endl;
    }  


    
    template<typename T>
    void IsEnum(T) {
        if(IsEnumT<T>::Yes)
            cout << "IsEnum" << endl;
        else
            cout << "Is not Enum" << endl;
    }  

    
};
