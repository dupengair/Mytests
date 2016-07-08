#pragma once
#include <cstring>
#include <cstddef>
#include <iostream>


#include <cmath>
#include <cstdlib>

#include "classdef.h"


using std::cout;
using std::endl;

namespace template_test
{
	template <typename FO>
	void print_values(FO fo) {
		for (int i = -2; i<3; ++i) {
			std::cout << "f(" << i*0.1 << ") = " << fo(i*0.1) << endl;
		}
	}


	class Abs {
	public:
		double operator() (double v) const {
		return std::abs(v);
	};

	class Sine {
	public:
		double operator() (double a) const {
			return std::sin(a);
		}
	};

    
};
