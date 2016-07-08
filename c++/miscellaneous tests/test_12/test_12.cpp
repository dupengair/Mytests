#include <iostream>
#include "classdef.h"
#include <list>


typedef void (*Callbackbefore)(void);
typedef bool (*Callbackafter)(int a, int b);
std::list<Callbackbefore> funclist;


void func_0(void)
{
    std::cout << "func_0"<<std::endl; 
}

void func_1(int a, int b)
{
    std::cout << "func_1, a = " << a <<" , b =" << b <<std::endl; 
}

void func_2(int a, int b)
{
    std::cout << "func_2, a = " << a <<" , b =" << b <<std::endl; 
}

void func_3(int a, int b)
{
    std::cout << "func_3, a = " << a <<" , b =" << b <<std::endl; 
}

void addCbk(const Callbackbefore &func)
{
        std::cout << " add func " << std::endl;
        funclist.push_back(func);
}

void invoke(int a, int b)
{
    for(std::list<Callbackbefore>::iterator i =funclist.begin(); i != funclist.end(); ++i)
        {
         std::cout << " call func " << std::endl;
        ((Callbackafter &)*i)(a, b);
        }
}


movecp ret_obj(int n)
{
    movecp t(n);
    
    return t;
}

int main(void)
{
    #if 0
    addCbk((const Callbackbefore )func_1);
    addCbk((const Callbackbefore )func_2);
    addCbk((const Callbackbefore )func_3);
    
    invoke(1, 2);
    #else

    movecp t1 = ret_obj(1);

    #endif

    return 0;
}
