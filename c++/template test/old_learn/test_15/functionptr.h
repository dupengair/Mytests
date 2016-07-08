#pragma once

#include <iostream>

using std::cout;
using std::endl;


namespace template_test
{

	template<typename RT, typename P1 = void, typename P2 = void, typename P3 = void>
	class FunctionPtr {
	private:
		typedef typename FunctionPtrT<RT, P1, P2, P3>::Type FuncPtr;
		FuncPtr fptr;
	public:
		enum { NumParams = FunctionPtrT<RT, P1, P2, P3>::NumParams };
		typedef RT ReturnT;
		typedef P1 Param1T;
		typedef P2 Param2T;
		typedef P3 Param3T;

		FunctionPtr(FuncPtr ptr): fptr(ptr) { }
		RT operator() () {
			return fptr();
		}
		RT operator() (typename ForwardParamT<P1>::Type a1) {
			return fptr(a1);
		}

		RT operator() (typename ForwardParamT<P1>::Type a1, typename ForwardParamT<P2>::Type a2) {
			return fptr(a1, a2);
		}

		RT operator() (typename ForwardParamT<P1>::Type a1, 
						typename ForwardParamT<P2>::Type a2 ,
						typename ForwardParamT<P3>::Type a3) {
			return fptr(a1, a2, a3);
		}
		
	};















}

