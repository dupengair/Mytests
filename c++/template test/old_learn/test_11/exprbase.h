#pragma once

#include <iostream>
#include <stddef.h>
#include <cassert>

using std::cout;
using std::endl;

namespace template_test
{

    template<typename T, typename OP1, typename OP2>
    class A_Add {
    private:
        typename A_Traits<OP1>::ExprRef op1;
        typename A_Traits<OP2>::ExprRef op2;

    public:
        A_Add (OP1 const& a, OP2 const& b): op1(a), op2(b) {}
        
        T operator[] (size_t idx) const {
                return op1[idx] + op2[idx];
        }

        size_t size() const {
            assert (op1.size() == 0|| op2.size() == 0 || op1.size() == op2.size());
            return op1.size() != 0 ? op1.size() : op2.size();
        }

    };

    template<typename T, typename OP1, typename OP2>
    class A_Mult {
    private:
        typename A_Traits<OP1>::ExprRef op1;
        typename A_Traits<OP2>::ExprRef op2;

    public:
        A_Mult (OP1 const& a, OP2 const& b): op1(a), op2(b) {}
        
        T operator[] (size_t idx) const {
                return op1[idx] * op2[idx];
        }

        size_t size() const {
            assert (op1.size() == 0|| op2.size() == 0 || op1.size() == op2.size());
            return op1.size() != 0 ? op1.size() : op2.size();
        }

    };

    template <typename T>
    class A_Scalar {
    private:
        T const& s;

    public:
        A_Scalar (T const& v): s(v) {}

        T operator[] (size_t) const {
            return s;
        }

        size_t size() const {
            return 0;
        }
        
    };


        

        
};
