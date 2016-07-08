#include <iostream>
#include <vector>

#include "classdef.h"

using namespace template_test;

Duo<float, int> foo() 
{
    return make_duo(42, 42);
}

int main()
{
    if(foo() == make_duo(42, 42.0)) {
        cout << "haha, got u!" << endl;
        } else {
        cout << "oops, missed u!" << endl;
        }

    Duo<bool, int> d(1, 2);
    cout << d.v1() << endl;
    cout << val<1>(d) << endl;

    Duo<bool, Duo<int, float> > t;

    val<1>(t) = true;
    val<2>(t) = 42;
    val<3>(t) = 0.2;

    cout << val<1>(t) << endl;
    cout << val<2>(t) << endl;
    cout << val<3>(t) << endl;

    Tuple<int> t1;
    val<1>(t1) += 42;
    cout << t1.v1() << endl;

    Tuple<bool, int> t2(true, 42);
    cout << val<1>(t2) << ", " << t2.v2() << endl;

    Tuple<bool, int, double> t3;
    
    val<1>(t3) = true;
    val<2>(t3) = 42;
    val<3>(t3) = 0.2;

    cout << val<1>(t3) << ", ";
    cout << val<2>(t3) << ", ";
    cout << val<3>(t3) << endl;

    t3 = make_tuple(false, 223, 13.13);
    cout << val<1>(t3) << ", ";
    cout << val<2>(t3) << ", ";
    cout << val<3>(t3) << endl;

    Tuple<bool, int, float, double> t4(true, 42, 13, 1.95583);
    cout << val<4>(t4) << endl;
    cout << t4.v2().v2().v2() << endl;

    
    
}

