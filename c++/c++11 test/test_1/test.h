#pragma once

#if __cplusplus < 201103L
    #error not support c++11
#endif


#include "classdef.h"

/*Test Variadic Template1*/
template<typename  Args>
void output(Args args) {
    cout << "[the last]: " << args << endl;
}

template<typename Arg0, typename ... Args>
void output(Arg0 arg0, Args ... args) {
    cout << arg0 << " ";
    output<Args...>(args...);
}


/*Test Variadic Template2*/
template<typename ClsType>
void CallMtd(ClsType *obj)
{
    cout << "the end: " << endl;
    obj->method();
}

template<typename ClsType0, typename... ClsTypeN>
void CallMtd(ClsType0 *obj, ClsTypeN*... objn)    
{
    cout << "this should be call with at least 1 param, total params : " << sizeof... (objn) << endl;
    obj->method();
    CallMtd<ClsTypeN...>(objn...);
}

template<typename... ClsTypeN>
void CallMtd(ClsTypeN*... objn)    
{
   cout << "call without params" << endl;
}


/*Test Variadic Template3*/
void myPrintf(const char * s)
{
    while (*s)
    {
        if (*s == '%')
        {
            if (*(s + 1) == '%')
            {
                ++s;
            }
            else
            {
                cout << "invalid format string: missing arguments" << endl;
                return;
            }
        }
        std::cout << *s++;
    }
}

template<typename T, typename... Args>
void myPrintf(const char * s, T value, Args... args)
{
    while (*s)
    {
        if (*s == '%')
        {
            if (*(s + 1) == '%')
            {
                ++s;
            }
            else
            {
                std::cout << value;
                myPrintf(s + 1, args...); // 即便 *s == 0 的时候，也调用，以便用于检测多余的参数。
                return;
            }
        }
        std::cout << *s++;
    }
   cout << "extra arguments provided to myPrintf" << endl;
}

