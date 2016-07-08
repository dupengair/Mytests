#pragma once

#if __cplusplus < 201103L
    #error compiler not support c++11
#endif


#include "classdef.h"

using namespace cpp11test;

struct A {
    A() {}
    A(const A& a) { cout << "Copy constucted: " << __func__ << endl; }
    A(A&& a) { cout << "Move constructed: " << __func__ << endl; }
};

struct B {
    B() {}
    B(const B& a) { cout << "Copy constucted: " << __func__ << endl; }
    B(B&& a) { cout << "Move constructed: " << __func__ << endl; }
};


