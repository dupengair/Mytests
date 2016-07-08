#include <iostream>

#include "test.h"


using namespace template_test;

using std::cout;
using std::endl;


int main(void)
{

    #if 0
    Duo<bool, int> d;
    cout << d.v1() << endl;
    cout << val<1>(d) << endl;

    Duo<bool, Duo<int, float> > t;
    val<1>(t) = true;
    val<2>(t) = 42;
    val<3>(t) = 0.2;

    cout << val<1>(t) << endl;
    cout << val<2>(t) << endl;
    cout << val<3>(t) << endl;

    Duo<bool, Duo<int, Duo<float, char> > > q;
    val<1>(q) = true;
    val<2>(q) = 42;
    val<3>(q) = 0.2;
    val<4>(q) = 'c';

    cout << val<1>(q) << endl;
    cout << val<2>(q) << endl;
    cout << val<3>(q) << endl;
    cout << val<4>(q) << endl;

    #else
    Tuple<int> t1;
    val<1>(t1) += 42;
    cout << t1.v1() << endl;

    Tuple<bool, int> t2;
    cout<< val<1>(t2) << ", " << t2.v1() << endl;

    Tuple<bool, int, double> t3;

    val<1>(t3) = true;
    val<2>(t3) = 42;
    val<3>(t3) = 0.2;

    cout << val<1>(t3) << ", " << val<2>(t3) << ", " << val<3>(t3) << endl;

    t3 = make_tuple(false, 23, 13.13);
    cout << val<1>(t3) << ", " << val<2>(t3) << ", " << val<3>(t3) << endl;

    Tuple<bool, int, float, double> t4(true, 42, 131, 1.95583);
    cout << val<4>(t4) << endl;
    cout << t4.v2().v2().v2() << endl;
    
    #endif
    
    return 0;
}



