#pragma once

#include <iostream>

using std::cout;
using std::endl;


namespace template_test
{
	template<typename T>
	class ForwardParamT {
	public:
		typedef typename IfThenElse<TypeT<T>::IsClassT, 
				typename TypeOp<T>::RefConstT, 
				typename TypeOp<T>::ArgT>::ResultT Type;
	};

	template<>
	class ForwardParamT<void> {
	private:
		class Unused {};
	public:
		typedef Unused Type;
	};
    
};

