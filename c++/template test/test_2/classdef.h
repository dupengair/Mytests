#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <typeinfo>


namespace template_test
{

    using std::cout;
    using std::endl;


    template <typename T>
    class ElementT;    

    template <typename T>
    class ElementT<std::vector<T> > {
    public:
        typedef T Type;   
    };

    template <typename T>
    class ElementT<std::list<T> > {
    public:
        typedef T Type;   
    };


    template <typename T>
    class ElementT<std::stack<T> > {
    public:
        typedef T Type;   
    };


    template <typename T>
    void print_element_type (T const & c) {
        cout << "Container of " << typeid(typename ElementT<T>::Type).name() << " elements." << endl;
    }

    template <typename T>
    class IsClassT {
    private:
        typedef char One;
        typedef struct { char a[2]; } Two;
        template <typename C> static One test(int C::*);
        template <typename C> static Two test(...);
    public:
        enum { Yes = sizeof(IsClassT<T>::test<T>(0)) == 1 };
        enum { No = !Yes };
    };

    template <typename T>
    void check() {
        if (IsClassT<T>::Yes) 
            cout << "IsClassT " << endl;
         else
            cout << "!IsClassT " << endl;
    }

    template <typename T>
    void checkT(T) {
        check<T>();
    }

};
