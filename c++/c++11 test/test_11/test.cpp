#include <iostream>
#include <cstdio>
#include <string>
#include <list>
#include <algorithm>

#include "test.h"



using namespace cpp11test;

using std::cout;
using std::endl;

void g(double) { cout << "double" << endl; } // #1

template<typename T> 
void f() {
     g(1);
 }
 
void g(int) { cout << "int" << endl; } // #2


int C;

class C {
    private:
        int i[2];
    public:
        static int f() {
            return sizeof(C);
            }
};

int f()
{
    return sizeof(C);
}

int main() 
{
    std::string str = "it";
    int i = 10;
    Printf("test: %s, 2nd %d\n", str, i);
    printf("test: %s, 2nd %d\n", str.c_str(), i);

    
    //std::list<int> li;     
    //std::sort(li.begin(), li.end());

    f<int>();
    cout << C::f() << " " << ::f() << endl;
}

