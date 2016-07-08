#pragma once
#include <cstring>
#include <stddef.h>
#include <iostream>
#include "classdef.h"

#include <typeinfo>


using std::cout;
using std::endl;

namespace template_test
{

	 int one(int t) {
	 	cout << "call func with value: " << t << endl;
		return 1;
 	}
	
 	double seven() {
		return 7.0;
 	}

	std::string more() {
		return std::string("more");
	}

	template <typename FunctorT>
	void demo(FunctorT func) {
		std::cout << "Funtor return type " << typeid(typename FunctorT::ReturnT).name() << endl
				<< "Functor return value " << func() << endl;
	}
				
 		
	template <typename FunctorT, typename P1>
	void demo(FunctorT func, P1 p) {
		std::cout << "Funtor return type " << typeid(typename FunctorT::ReturnT).name() << endl
				<< "Functor return value " << func(p) << endl;
	}
			

    
};
