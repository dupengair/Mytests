#include <iostream>
#include "classdef.h"


#define SharePtr std::shared_ptr

//using namespace std;
using std::cout;
using std::endl;

int global_int = 1;

/*
typedef struct
{
    int x, y, z;
} Point;*/

class Point{
public:
   // Point(int _x=0, int _y=0, int _z=0) : x(_x), y(_y), z(_z) {}
public:
    int x, y, z;   
};


 
Point func()
{
    Point local;

    cout << "local.x : " << local.x <<endl;

    Point *p = new Point;

    //*p = local;

    cout << "p->x : " << p->x <<endl;

    delete p;
    
    return local;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

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
        std::cout << " add func " << endl;
        funclist.push_back(func);
}

void invoke(int a, int b)
{
    for(std::list<Callbackbefore>::iterator i =funclist.begin(); i != funclist.end(); ++i)
        {
         std::cout << " call func " << endl;
        ((Callbackafter)*i)(a, b);
        }
}

auto max(int a, int b) -> int ;

int main(void)
{
    addCbk((const Callbackbefore &)func_1);
    addCbk((const Callbackbefore &)func_2);
    addCbk((const Callbackbefore &)func_3);
    
    invoke(1, 2);
    
 //   int local_int = 2;

 //   func();
    
//    Derived d;
//    Base *pb = &d;
//    pb->testbm();

//    auto x = 1;

//    Base b;
//    Derived d;

    return 0;
}
