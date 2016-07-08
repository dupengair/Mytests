#pragma once

#include <iostream>

using std::cout;
using std::endl;



namespace template_test
{
	
    template<bool C, typename Ta, typename Tb>
    class IfThenElse;

    template<typename Ta, typename Tb>
    class IfThenElse<true, Ta, Tb> {
        public:
            typedef Ta ResultT;
    };
          
    template<typename Ta, typename Tb>
    class IfThenElse<false, Ta, Tb> {
        public:
            typedef Tb ResultT;
    };
	
};

