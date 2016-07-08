#include <iostream>


#include "test.h"


using namespace template_test;

    class CustomPolicy {
        public:
            static void print(void) {
                cout << "CustomPolicy" << endl;
            }
    };



int main(void)
{
    BreadSlicer<> bs;
    bs.p1();
    bs.p2();
    bs.p3();
    bs.p4();

    std::cout << std::endl;

    BreadSlicer<Policy3_is<CustomPolicy> > bbs;
    bbs.p1();
    bbs.p2();
    bbs.p3();
    bbs.p4();    
    
    return 0;
}



