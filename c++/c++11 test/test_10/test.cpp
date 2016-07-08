#include <iostream>
#include <vector>
#include <algorithm>

#include "test.h"



using namespace cpp11test;

using std::cout;
using std::endl;


void realfunc(int& u)  { std::cout << "lvalue ref: " << u << std::endl; }
	void realfunc(int&& u) { std::cout << "rvalue ref: " << u << std::endl; }
	void realfunc(const int& u)  { std::cout << "const lvalue ref: " << u << std::endl; }
	void realfunc(const int&& u) { std::cout << "const rvalue ref: " << u << std::endl; }				
	template<typename T> 
	void forwardfunc(T&& t) {	
		realfunc(std::forward<T>(t));		
	}


void realfunc1(int& u)	{ std::cout << "realfunc1: " << u << std::endl; }
void realfunc2(int&& u) { std::cout << "realfunc2: " << u << std::endl; }
void realfunc3(const int& u)  { std::cout << "realfunc3: " << u << std::endl; }
void realfunc4(const int&& u) { std::cout << "realfunc4: " << u << std::endl; } 	
void realfunc5(char u)	{ std::cout << "realfunc5: " << u << std::endl; }
void realfunc6(const char u)  { std::cout << "realfunc6: " << u << std::endl; }


template<typename T, typename U> 
void funcwarpper(T&& t, U& func) {	
		func(std::forward<T>(t));		
}	



int main() 
{
	int a = 1;
	//int b = 2;
	const int c = 3;
	const int d = 4;
			
	forwardfunc(a); 		//lref
	//forwardfunc(std::move(b));	//rref
	forwardfunc(2);	//rref
	forwardfunc(c); 		//const lref
	forwardfunc(std::move(d));	//const rref



	const char e = 'e';
			
	funcwarpper(a, realfunc1);	//1
	funcwarpper(2, realfunc2);	//2
	funcwarpper(c, realfunc3);	//3
	funcwarpper(4, realfunc4);	//4
	funcwarpper(e, realfunc5);	//e
	funcwarpper('f', realfunc6);	//f	

}

