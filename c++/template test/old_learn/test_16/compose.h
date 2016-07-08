#pragma once

#include <iostream>

using std::cout;
using std::endl;




namespace template_test
{


	template <typename C, int N>
	class BaseMem: public C {
	public:
		BaseMem(C& c): C(c) {}
		BaseMem(C const& c): C(c) {}
	};


	template <typename FO1, typename FO2>
	class Composer: private BaseMem<FO1, 1>, private BaseMem<FO2, 2> {
	public:
		Composer(FO1 f1, FO2 f2): BaseMem<FO1, 1>(f1), BaseMem<FO2, 2>(f2) {}
		double operator() (double v) {
			return BaseMem<FO2, 2>::operator()(BaseMem<FO1, 1>::operator()(v));
	};
    
};

