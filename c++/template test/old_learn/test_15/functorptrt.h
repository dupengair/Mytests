#pragma once

#include <iostream>

using std::cout;
using std::endl;


namespace template_test
{
	template<typename RT, typename P1 = void, typename P2 = void, typename P3 = void>
	class FunctionPtrT {
	public:
		enum { NumParams = 3 };
		typedef RT (*Type)(P1, P2, P3);
	};

	template<typename RT, typename P1, typename P2>
	class FunctionPtrT <RT, P1, P2, void>{
	public:
		enum { NumParams = 2 };
		typedef RT (*Type)(P1, P2);
	};	

	template<typename RT, typename P1>
	class FunctionPtrT <RT, P1, void, void>{
	public:
		enum { NumParams = 1 };
		typedef RT (*Type)(P1);
	};

	template<typename RT>
	class FunctionPtrT <RT, void, void, void>{
	public:
		enum { NumParams = 0 };
		typedef RT (*Type)();
	};

	
    
};

