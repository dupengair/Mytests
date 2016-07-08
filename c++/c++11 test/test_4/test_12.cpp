#include <iostream>
#include <string>


#include "test.h"


#include <stdio.h>


using std::cout;
using std::endl;



void realfunc(int& u)  { std::cout << "lvalue ref: " << u << std::endl; }
void realfunc(int&& u) { std::cout << "rvalue ref: " << u << std::endl; }
void realfunc(const int& u)  { std::cout << "const lvalue ref: " << u << std::endl; }
void realfunc(const int&& u) { std::cout << "const rvalue ref: " << u << std::endl; }	

			
template<typename T> 
void forwardfunc(T&& t) { 	
    realfunc(std::forward<T>(t)); 
    //realfunc(t);
}


void realfunc1(int& u)  { std::cout << "realfunc1: " << u << std::endl; }
void realfunc2(int&& u) { std::cout << "realfunc2: " << u << std::endl; }
void realfunc3(const int& u)  { std::cout << "realfunc3: " << u << std::endl; }
void realfunc4(const int&& u) { std::cout << "realfunc4: " << u << std::endl; }		
void realfunc5(char u)  { std::cout << "realfunc5: " << u << std::endl; }
void realfunc6(const char u)  { std::cout << "realfunc6: " << u << std::endl; }

		
template<typename T, typename U> 
void funcwarpper(T&& t, U& func) { 	
    func(std::forward<T>(t)); 		
}	


Student class1 = {{1, "Li"}, {2, "Wang"}, {3, "Zhao"}};



int main() {
    int a = 1;
    int b = 2;
    const int c = 3;
    const int d = 4;
    const char e = 'e';
    
					
    forwardfunc(a);			        //lref
    forwardfunc(std::move(b));	 //rref
    forwardfunc(c);			        //const lref
    forwardfunc(std::move(d));	 //const rref

    funcwarpper(a, realfunc1);	
    funcwarpper(2, realfunc2);	
    funcwarpper(c, realfunc3);	
    funcwarpper(4, realfunc4);	
    funcwarpper(e, realfunc5);	
    funcwarpper('f', realfunc6);	

    func({1, 2, 3, 4});

    SmartArray s;
    s[{1, 3, 5}] = 1;		//s[]的第1、3、5个元素值
    s[{2, 4, 6}] = 2;		//s[]的第2, 4, 6个元素值
    s.Print();

}
