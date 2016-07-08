#include <iostream>


namespace template_test
{

    using std::cout;
    using std::endl;

    
    template<typename Y>
    class Outter {
    public:
        template<typename T>
        class Inner {
        public:
            void func() { cout << 6 << endl; }
            };
        };

    class Outter1 {
    public:
        template<typename T>
        class Inner {
        public:
            void func() { cout << 6 << endl; }
            };
        };    

    template<typename N>
    class Test {
    public:
        void func() { i.func(); i1.func(); }
    private:
        typename Outter<N>::template Inner<N> i;

        Outter1::Inner<N> i1;
     };


    class BX {
    public:
        void func() { cout << 7 << endl; }
    };

    class DX: private BX {
    public:
        using BX::func;
    };

    template<typename T>
    class DXT: private Outter<T> {
  //  public:
      //  using  Outter<T>::template Inner<T>::func;
    };

    namespace N {
        class X {
        public: int a;
        };

        template<int I>void select(X*) { cout << I << endl; }        
    }

    void g(N::X* xp)
        {
        N::select<3>(xp);
        }





    template <typename X>
    class Base {
    public:
        int basefield;
        typedef int T;
    };

    class D1: public Base<void> {   
        public:
            void f() { basefield = 3; }
    };

    template <typename T>
    class D2: public Base<void> {
        public:
            void f() { basefield = 7; }
            T strange;
    };





    void g1(D2<int*>& d2, int* p)
        {
            d2.strange = p;
        }
    
    };
