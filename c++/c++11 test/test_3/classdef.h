#pragma once
#include <string>
#include <iostream>

using std::cout;
using std::endl;

/*class definition*/

	class A {
		int *d;
	public:
		A():d(new int(0)) { cout << "A ctor" << endl; }
		A(const A& a):d(new int(*a.d)) { cout << "A copy ctor" << endl; }		//拷贝构造函数
		~A() { cout << "A dtor" << endl; delete d; }
              friend void set(A& a, int t);
	};


	class B {
		int *d;
	public:
		B():d(new int(0)) { cout << "B ctor" << endl; }
		B(const B& b):d(new int(*b.d)) { cout << "B copy ctor" << endl; }		//拷贝构造函数
		B(B&& b):d(b.d) { b.d = nullptr; cout << "B move ctor" << endl; }		       //移动构造函数
		~B() { cout << "B dtor" << endl; delete d; }
              friend void set(B& b, int t);
	};

