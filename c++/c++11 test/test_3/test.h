#pragma once

#if __cplusplus < 201103L
//    #error not support c++11
#endif


#include "classdef.h"

void set(A& a, int t) { *a.d = t; }
void set(B& b, int t) { *b.d = t; }

A GetA() { A a; set(a, 1); return a; }
B GetB() { B b; set(b, 1); return b; }