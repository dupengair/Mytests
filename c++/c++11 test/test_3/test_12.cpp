#include <iostream>
#include <string>
#include "test.h"

#include <stdio.h>
#include <typeinfo>

using std::cout;
using std::endl;


int func(int t) {
    return t;
}

int main(void)
{

    A a = GetA();		//拷贝构造
    B b = GetB();		//移动构造
     
    return 0;
}
