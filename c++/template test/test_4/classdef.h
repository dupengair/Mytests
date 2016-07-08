#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <typeinfo>


namespace template_test
{

    using std::cout;
    using std::endl;



    template <bool C, typename Ta, typename Tb>
    class IfThenElse;

    template <typename Ta, typename Tb>
    class IfThenElse<true, Ta, Tb> {
    public:
        typedef Ta ResultT;
    };
    
    template <typename Ta, typename Tb>
    class IfThenElse<false, Ta, Tb> {
    public:
        typedef Tb ResultT;
    };

    template<typename T1, typename T2>
    class Promotion {
    public:
        typedef typename IfThenElse<(sizeof(T1) > sizeof(T2)), T1, 
                                                      typename IfThenElse <(sizeof(T1) < sizeof(T2)), T2, void>::ResultT                                                      
                                                      >::ResultT ResultT;
    };

    template<typename T>
    class Promotion<T, T> {
    public:
        typedef T ResultT;
    };

    #define MK_PROMOTION(T1, T2, Tr)             \
        template<> class Promotion<T1, T2> {    \
        public:                                                        \
            typedef Tr ResultT;                                \
        };                                                               \
                                                                          \
        template<> class Promotion<T2, T1> {     \
        public:                                                         \
            typedef Tr ResultT;                                 \
        };


    MK_PROMOTION(bool, char, int)
    MK_PROMOTION(bool, unsigned char, int)
    MK_PROMOTION(bool, signed char, int)


    template <typename T>
    class Array{};

    template<typename T1, typename T2>
    class Promotion<Array<T1>, Array<T2> > {
    public:
        typedef Array<typename Promotion<T1, T2>::ResultT> ResultT;
    };
        
    template<typename T>
    class Promotion<Array<T>, Array<T> > {
    public:
        typedef Array<typename Promotion<T, T>::ResultT> ResultT;
    };


    
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

/*
    template<typename T>
    class RParam {
    public:
        typedef typename IfThenElse<sizeof(T) <= 2 * sizeof(void*), T, T const& >::ResultT Type;
    };
*/

    template<typename T>
    class RParam {
    public:
        typedef typename IfThenElse<IsClassT<T>::No, T, T const&>::ResultT Type;
    };

    template<typename T>
    class RParam<Array<T> > {
    public:
        typedef Array<T> const& Type;
    };




    class MyClass1 {
    public:
        MyClass1() {}
        MyClass1(MyClass1 const&) {
            cout << "MyClass1 copy constuctor called" << endl;
        }
    };

    class MyClass2 {
    public:
        MyClass2(int n) { a = n; }
        MyClass2(MyClass1 const&) {
            cout << "MyClass2 copy constuctor called, a = " << a << endl;
        }
        int a;

        virtual void test(void) { cout << a << endl; }
    };

    template<>
    class RParam<MyClass2> {
    public:
        typedef MyClass2 Type;
    };


    
         

};
