#include <iostream>

namespace template_test
{

    using std::cout;
    using std::endl;

    namespace X {
        template<typename T>void f(T);
        }

    namespace N {
        using namespace X;
        enum E { e1 };
        void f(E);
        }

    void f(int);



    
};
