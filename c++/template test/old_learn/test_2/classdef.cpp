#include <iostream>
#include "classdef.h"


namespace template_test
{
    namespace N {
        void f(E) { cout << "N::f(N::E) called" <<endl; }
        }

    void f(int){
        cout << "::f(int) called" << endl;             
        } 


}