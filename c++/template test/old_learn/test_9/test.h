#pragma once
#include <cstring>
#include <stddef.h>
#include <iostream>
#include "classdef.h"


using std::cout;
using std::endl;

namespace template_test
{


    template <typename PolicySetter1 = DefaultPolicyArgs,
                      typename PolicySetter2 = DefaultPolicyArgs,
                      typename PolicySetter3 = DefaultPolicyArgs,
                      typename PolicySetter4 = DefaultPolicyArgs>
    class BreadSlicer {
    private:
        typedef PolicySelector<PolicySetter1, PolicySetter2, PolicySetter3, PolicySetter4> Policies;

    public:
        void p1(void) { Policies::P1::print(); }
        void p2(void) { Policies::P2::print(); }
        void p3(void) { Policies::P3::print(); }
        void p4(void) { Policies::P4::print(); }
    };

    
};
