#include <iostream>

using std::cout;
using std::endl;

namespace template_test
{

    template <class T>
    class testMemberTemplate {
        public:
            testMemberTemplate(T t): x(t) { cout << "testMemberTemplate ctor : " << x << endl; }
            ~testMemberTemplate() { cout << "testMemberTemplate dtor" << endl; }

            template <class X>
            void showPriMember(void) { cout << "pri member x = " << x << endl; }

        private:
            T x;
    };


};