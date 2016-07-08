#include <iostream>
#include <string>

#include "test.h"

#include <stdio.h>


using std::cout;
using std::endl;

struct G { 
    void func(void) { }
    static void sfunc(void) {}
    static const int a = 1;
    };
  	void (G::*pfunc)() = &G::func;  


int main() {




    A a(1,2);
    A b(1,2);

    //if(a) {} //cout << a.operator bool()<< endl;
    //if(b) {} //cout << b.operator bool()<< endl;


    cout << (int)a + (int)b << endl;    


    	printf("%p\n", pfunc);  	//A::func()的内存地址
    	printf("%p\n", &G::func);   	//同上
       printf("%p\n", &G::sfunc);   	//同上


             

    			SmartArray s;
			s[{1, 3, 5}] = 1;		//s[]的第1、3、5个元素值
			s[{2, 4, 6}] = 2;		//s[]的第2, 4, 6个元素值
			s.Print();	

    
       
}
