#pragma once

#include <iostream>
#include <stddef.h>
#include <cassert>

using std::cout;
using std::endl;


namespace template_test
{

    template <typename T, typename R1, typename R2>
    Array<T, A_Add<T, R1, R2> >
    operator+ (Array<T, R1> const& a, Array<T, R2> const& b) {
        return Array<T, A_Add<T, R1, R2> >(A_Add<T, R1, R2>(a.rep(), b.rep()));
    }

    template <typename T, typename R1, typename R2>
    Array<T, A_Mult<T, R1, R2> >
    operator* (Array<T, R1> const& a, Array<T, R2> const& b) {
        return Array<T, A_Mult<T, R1, R2> >(A_Mult<T, R1, R2>(a.rep(), b.rep()));
    }

    template <typename T, typename R2>
    Array<T, A_Mult<T, A_Scalar<T>, R2> >
    operator* (T const& s, Array<T, R2> const& b) {
        return Array<T, A_Mult<T, A_Scalar<T>, R2> >(A_Mult<T, A_Scalar<T>, R2>(A_Scalar<T>(s), b.rep()));
    }








};
