#pragma once

#include <iostream>

using std::cout;
using std::endl;


namespace template_test
{
	template<typename RT> inline
	FunctionPtr<RT> func_ptr (RT (*fp) ()) {
		return FunctionPtr<RT>(fp);
	}

	template<typename RT, typename P1> inline
	FunctionPtr<RT, P1> func_ptr (RT (*fp) (P1)) {
		return FunctionPtr<RT, P1>(fp);
	}	

	template<typename RT, typename P1, typename P2> inline
	FunctionPtr<RT, P1, P2> func_ptr (RT (*fp) (P1, P2)) {
		return FunctionPtr<RT, P1, P2>(fp);
	}	

	template<typename RT, typename P1, typename P2, typename P3> inline
	FunctionPtr<RT, P1, P2, P3> func_ptr (RT (*fp) (P1, P2, P3)) {
		return FunctionPtr<RT, P1, P2, P3>(fp);
	}	


}
