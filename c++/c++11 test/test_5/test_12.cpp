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


    	printf("%p\n", pfunc);  	//A::func()���ڴ��ַ
    	printf("%p\n", &G::func);   	//ͬ��
       printf("%p\n", &G::sfunc);   	//ͬ��


             

    			SmartArray s;
			s[{1, 3, 5}] = 1;		//s[]�ĵ�1��3��5��Ԫ��ֵ
			s[{2, 4, 6}] = 2;		//s[]�ĵ�2, 4, 6��Ԫ��ֵ
			s.Print();	

    
       
}
