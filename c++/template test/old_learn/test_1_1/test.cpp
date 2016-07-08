//#include <iostream>
#include "classdef.h"

using namespace template_test;
extern const char hah[] ="hello";


int seed(int t)
{
    return t;
}


int main(void)
{
    cout << "the max is: " << max(7, 42, 68) << endl;

    const char* s1 = "huoguo";
    const char* s2 = "yuanyangguo";
    const char* s3 = "baicai";

    cout << "the max is: " << max(s1, s2, s3) << endl;

    //cout << "the max is: " << max(s1, s2) << endl;
    //printf("addr of max(s1, s2): %p\n", max(s1, s2));

    //int myint = 1;
    //f(seed(myint));
    
    MyChar<hah> x;
    x.get();

    Name2<int> n(1);
    n.get();

   
    Name2<int, Name1<float> > o(2);
    o.get();

    Name3<int> m(2);
    m.get();

    std::string s;

    ::maxx("apple","peach");   // OK: same type
    ::maxxx("apple","tomato");  // ERROR: different types
    
    return 0;
}
