#include <iostream>
#include <stddef.h>
#include <cassert>
#include <cstring>
#include <typeinfo>


namespace template_test
{

    using std::cout;
    using std::endl;


    template <typename T1, typename T2>
    class Duo {
        public:
            typedef T1 Type1;
            typedef T2 Type2;
            enum { N = 2 };

        private:
            T1 value1;
            T2 value2;

        public:
            Duo(): value1(), value2() {}
            Duo(T1 const& a, T2 const& b): value1(a), value2(b) {}

            template<typename U1, typename U2>
            Duo(Duo<U1, U2> const& d): value1(d.v1()), value2(d.v2()) {}

            template<typename U1, typename U2>
            Duo<T1, T2>& operator= (Duo<U1, U2> const& d) {
                value1 = d.v1();
                value2 = d.v2();
                return *this;
                }


            T1& v1() { return value1; }
            T2& v2() { return value2; }
            T1 const& v1 () const{ return value1; }
            T2 const& v2() const{ return value2; }
        };


    template<typename T1, typename T2, typename U1, typename U2>
    inline bool operator== (Duo<T1, T2> const& d1, Duo<U1, U2> const& d2) 
    {
        return (d1.v1() == d2.v1()) && (d1.v2() == d2.v2());
    }
            
    template<typename T1, typename T2, typename U1, typename U2>
    inline bool operator!= (Duo<T1, T2> const& d1, Duo<U1, U2> const& d2) 
    {
        return !(d1== d2);
    }         

    template <typename T1, typename T2>
    inline Duo<T1, T2> make_duo(T1 const& a, T2 const& b) 
    {
        return Duo<T1, T2>(a, b);
    }


    template<typename A, typename B, typename C>
    class Duo<A, Duo<B, C> > {
        public:
            typedef A T1;
            typedef Duo<B,C> T2;
            enum { N = Duo<B, C>::N + 1 };

        private:
            T1 value1;
            T2 value2;

        public:
            Duo(): value1(), value2() {}
            Duo(T1 const& a, T2 const& b): value1(a), value2(b) { cout << "N = " << N << endl; }

            template<typename U1, typename U2>
            Duo(Duo<U1, U2> const& d): value1(d.v1()), value2(d.v2()) {}

            template<typename U1, typename U2>
            Duo<T1, T2>& operator= (Duo<U1, U2> const& d) {
                value1 = d.v1();
                value2 = d.v2();
                return *this;
                }


            T1& v1() { return value1; }
            T2& v2() { return value2; }
            T1 const& v1 () const { return value1; }
            T2 const& v2() const { return value2; }
        };

    template <typename A>
    struct Duo<A, void> {
        public:
            typedef A T1;
            typedef void T2;
            enum { N =1 };

        private:
            T1 value1;

        public:
            Duo(): value1(){}
            Duo(T1 const& a): value1(a) { cout << "N = " << N << endl; }

            T1& v1() { return value1; }
            void v2() {}
            T1 const& v1 () const { return value1; }
            void v2() const {}
        };


    template<int N, typename A>
    class DuoT {
        public:
            typedef void ResultT;
        };

    template<typename A, typename B>
    class DuoT<1, Duo<A, B> > {
        public:
            typedef A ResultT;
        };
        
    template<typename A, typename B>
    class DuoT<2, Duo<A, B> > {
        public:
            typedef B ResultT;
        };    
    
    template<int N, typename A, typename B, typename C>
    class DuoT<N, Duo<A, Duo<B, C> > > {
        public:
            typedef typename DuoT<N-1, Duo<B, C> >::ResultT ResultT;
        };

    template<typename A, typename B, typename C>
    class DuoT<1, Duo<A, Duo<B, C> > > {
        public:
            typedef A ResultT;
        };
   
    template<typename A, typename B, typename C>
    class DuoT<2, Duo<A, Duo<B, C> > > {
        public:
            typedef B ResultT;
        };      


    // TypeOp
    template <typename T>
    class TypeOp {
    public:
            typedef     T    ArgT;
            typedef     T    BareT;
            typedef     T const ConstT;
            typedef     T &     RefT;
            typedef     T &     RefBareT;
            typedef     T const &   RefConstT;
    };
    
    template <typename T>
    class TypeOp<T const> {
    public:
               typedef     T const  ArgT;
               typedef     T    BareT;
               typedef     T const  ConstT;
               typedef     T &     RefT;
               typedef     T &     RefBareT;
               typedef     T const &   RefConstT;
    };
    
    template <typename T>
    class TypeOp<T&> {
    public:
               typedef     T&    ArgT;
               typedef     T    BareT;
               typedef     T const  ConstT;
               typedef     T &     RefT;
               typedef     T &     RefBareT;
               typedef     T const &   RefConstT;
    };

    template <>
    class TypeOp<void> {
    public:
               typedef     void    ArgT;
               typedef     void    BareT;
               typedef     void const  ConstT;
               typedef     void     RefT;
               typedef     void     RefBareT;
               typedef     void     RefConstT;
    };


    template<int N, typename T>
    class DuoValue {
        public:
            static void get(T&) {}
            static void get(T const&) {}
        };

    template<typename A, typename B>
    class DuoValue<1, Duo<A, B> > {
        public:
            static A& get(Duo<A, B> &d) { return d.v1(); }
            static A const& get(Duo<A, B> const& d) { return d.v1(); }
        };

    template<typename A, typename B>
    class DuoValue<2, Duo<A, B> > {
        public:
            static B& get(Duo<A, B> &d) { return d.v2(); }
            static B const& get(Duo<A, B> const& d) { return d.v2(); }
        };

    template<int N, typename A, typename B, typename C>
    class DuoValue<N, Duo<A, Duo<B, C> > > {
        public:
            static typename TypeOp<typename DuoT<N-1, Duo<B, C> >::ResultT>::RefT get(Duo<A, Duo<B, C> > &d) { 
                return DuoValue<N-1, Duo<B, C>>::get(d.v2()); 
                }
            
            static typename TypeOp<typename DuoT<N-1, Duo<B, C> >::ResultT>::RefConstT get(Duo<A, Duo<B, C> > const& d) { 
                return DuoValue<N-1, Duo<B, C>>::get(d.v2()); 
                }
        };

    template<typename A, typename B, typename C>
    class DuoValue<1, Duo<A, Duo<B, C> > > {
        public:
            static A& get(Duo<A, Duo<B, C> > &d) { return d.v1(); }
            static A const& get(Duo<A, Duo<B, C> > const& d) { return d.v1(); }
        };
    
    template<typename A, typename B, typename C>
    class DuoValue<2, Duo<A, Duo<B, C> > > {
        public:
            static B& get(Duo<A, Duo<B, C> > &d) { return d.v2().v1(); }
            static B const& get(Duo<A, Duo<B, C> > const& d) { return d.v2().v1(); }
        };

    
    template<int N, typename A, typename B>
    inline typename TypeOp<typename DuoT<N, Duo<A, B> >::ResultT>::RefT val(Duo<A, B>& d) {
        return DuoValue<N, Duo<A, B> >::get(d);
        }

    template<int N, typename A, typename B>
    inline typename TypeOp<typename DuoT<N, Duo<A, B> >::ResultT>::RefConstT val(Duo<A, B> const& d) {
        return DuoValue<N, Duo<A, B> >::get(d);
        }


    class NullT {};

    template <typename P1, typename P2 = NullT, typename P3 = NullT, typename P4 = NullT, typename P5 = NullT>
    class Tuple : public Duo<P1, typename Tuple<P2, P3, P4, P5, NullT>::BaseT> {
        public:
            typedef Duo<P1, typename Tuple<P2, P3, P4, P5, NullT>::BaseT> BaseT;

            Tuple() {}
            Tuple(
                typename TypeOp<P1>::RefConstT a1, 
                typename TypeOp<P2>::RefConstT a2, 
                typename TypeOp<P3>::RefConstT a3 = NullT(), 
                typename TypeOp<P4>::RefConstT a4 = NullT(), 
                typename TypeOp<P5>::RefConstT a5 = NullT())
                : BaseT(a1, Tuple<P2, P3, P4, P5, NullT>(a2, a3, a4, a5)) {} 
    };

    template <typename P1, typename P2 >
    class Tuple<P1, P2, NullT, NullT, NullT> : public Duo<P1, P2> {
        public:
            typedef Duo<P1, P2> BaseT;

            Tuple() {}
            Tuple(
                typename TypeOp<P1>::RefConstT a1, 
                typename TypeOp<P2>::RefConstT a2, 
                typename TypeOp<NullT>::RefConstT = NullT(), 
                typename TypeOp<NullT>::RefConstT = NullT(), 
                typename TypeOp<NullT>::RefConstT = NullT())
                : BaseT(a1, a2) {} 
    };

    template <typename P1>
    class Tuple<P1, NullT, NullT, NullT, NullT> : public Duo<P1, void> {
        public:
            typedef Duo<P1, void> BaseT;

            Tuple() {}
            Tuple(
                typename TypeOp<P1>::RefConstT a1, 
                typename TypeOp<NullT>::RefConstT = NullT(), 
                typename TypeOp<NullT>::RefConstT = NullT(), 
                typename TypeOp<NullT>::RefConstT = NullT(), 
                typename TypeOp<NullT>::RefConstT = NullT())
                : BaseT(a1) {} 
    };    


    template<typename T1>
    inline Tuple<T1> make_tuple(T1 const& a1) {
        return Tuple<T1>(a1);
        }

    template<typename T1, typename T2>
    inline Tuple<T1, T2> make_tuple(T1 const& a1, T2 const& a2) {
        return Tuple<T1, T2>(a1, a2);
        }

    template<typename T1, typename T2, typename T3>
    inline Tuple<T1, T2, T3> make_tuple(T1 const& a1, T2 const& a2, T3 const& a3) {
        return Tuple<T1, T2, T3>(a1, a2, a3);
        }

    template<typename T1, typename T2, typename T3, typename T4>
    inline Tuple<T1, T2, T3, T4> make_tuple(T1 const& a1, T2 const& a2, T3 const& a3, T4 const& a4) {
        return Tuple<T1, T2, T3, T4>(a1, a2, a3, a4);
        }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    inline Tuple<T1, T2, T3, T4, T5> make_tuple(T1 const& a1, T2 const& a2, T3 const& a3, T4 const& a4, T5 const& a5) {
        return Tuple<T1, T2, T3, T4, T5>(a1, a2, a3, a4, a5);
        }

};

