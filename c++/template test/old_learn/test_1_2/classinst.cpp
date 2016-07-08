#include "classdef.h"

using namespace template_test;

//template MyChar<int>;
template MyChar<int>::MyChar(int a);
template void MyChar<int>::get();


//template MyChar<float>;
template MyChar<float>::MyChar(float a);
template void MyChar<float>::get();

template MyChar<double>::MyChar(double a);
template void MyChar<double>::get();

