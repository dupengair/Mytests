#include <iostream>
#include <stddef.h>
#include <cstring>
#include <cstdlib>


namespace template_test
{

    using std::cout;
    using std::endl;

    // ForwardParamT
    // TypeT
    template <typename T>
    class IsFundaT {
    public:
        enum{Yes = 0, No = 1};
    };

    #define MK_FUNDA_TYPE(T) \
        template<> class IsFundaT<T> { \
        public: \
            enum {Yes = 1, No =0};  \
        };

    MK_FUNDA_TYPE(void)
    MK_FUNDA_TYPE(char)
    MK_FUNDA_TYPE(unsigned char)
    MK_FUNDA_TYPE(signed char)
    MK_FUNDA_TYPE(wchar_t)
    MK_FUNDA_TYPE(signed short)
    MK_FUNDA_TYPE(unsigned short)
    MK_FUNDA_TYPE(signed int)
    MK_FUNDA_TYPE(unsigned int)
    MK_FUNDA_TYPE(signed long)
    MK_FUNDA_TYPE(unsigned long)
    MK_FUNDA_TYPE(signed long long)
    MK_FUNDA_TYPE(unsigned long long)
    MK_FUNDA_TYPE(float)
    MK_FUNDA_TYPE(double)
    MK_FUNDA_TYPE(long double)


    template <typename T>
    void test(T const& t) {
        if(IsFundaT<T>::Yes) {
            cout << "T is fundamental type" << endl;
        } else {
            cout << "T is not fundamental type" << endl;
        }
    }


    template<typename T>
    class IsFunctionT {
    public:
        typedef char One;
        typedef struct { char a[2]; } Two;
        template<typename U> static One test(...);
        template<typename U> static Two test(U (*)[1]);
    public:
        enum { Yes = sizeof(IsFunctionT<T>::test<T>(0)) == 1 };
        enum { No = !Yes };
    };

    template<typename T>
    class IsFunctionT<T&> {
    public:
        enum { Yes = 0 };
        enum { No = !Yes };
    };

    template<>
    class IsFunctionT<void> {
    public:
        enum { Yes = 0 };
        enum { No = !Yes };
    };

    template<>
    class IsFunctionT<void const> {
    public:
        enum { Yes = 0 };
        enum { No = !Yes };
    };    

    #if 1
    template<typename T>
    class CompoundT {
    public:
        enum { IsPtrT = 0, IsRefT = 0, IsArraryT = 0, IsFuncT = IsFunctionT<T>::Yes, IsPtrMemT = 0 };
        typedef T BaseT;
        typedef T BottomT;
        typedef CompoundT<void> ClassT;
    };

    #else
    template<typename T>
    class CompoundT {
    public:
        enum { IsPtrT = 0, IsRefT = 0, IsArraryT = 0, IsFuncT = 0, IsPtrMemT = 0 };
        typedef T BaseT;
        typedef T BottomT;
        typedef CompoundT<void> ClassT;
    };
    #endif
    

    template<typename T>
    class CompoundT<T&> {
    public:
        enum { IsPtrT = 0, IsRefT = 1, IsArraryT = 0, IsFuncT = 0, IsPtrMemT = 0 };
        typedef T BaseT;
        typedef typename CompoundT<T>::BottomT BottomT;
        typedef CompoundT<void> ClassT;
    };

    template<typename T>
    class CompoundT<T*> {
    public:
        enum { IsPtrT = 1, IsRefT = 0, IsArraryT = 0, IsFuncT = 0, IsPtrMemT = 0 };
        typedef T BaseT;
        typedef typename CompoundT<T>::BottomT BottomT;
        typedef CompoundT<void> ClassT;
    };

    template<typename T, size_t N>
    class CompoundT<T[N]> {
    public:
        enum { IsPtrT = 0, IsRefT = 0, IsArraryT = 1, IsFuncT = 0, IsPtrMemT = 0 };
        typedef T BaseT;
        typedef typename CompoundT<T>::BottomT BottomT;
        typedef CompoundT<void> ClassT;
    };

    template<typename T>
    class CompoundT<T[]> {
    public:
        enum { IsPtrT = 0, IsRefT = 0, IsArraryT = 1, IsFuncT = 0, IsPtrMemT = 0 };
        typedef T BaseT;
        typedef typename CompoundT<T>::BottomT BottomT;
        typedef CompoundT<void> ClassT;
    };

    template<typename T, typename C>
    class CompoundT<T C::*> {
    public:
        enum { IsPtrT = 0, IsRefT = 0, IsArraryT = 0, IsFuncT = 0, IsPtrMemT = 1 };
        typedef T BaseT;
        typedef typename CompoundT<T>::BottomT BottomT;
        typedef CompoundT<void> ClassT;
    };

    template<typename R>
    class CompoundT<R()> {
    public:
        enum { IsPtrT = 0, IsRefT = 0, IsArraryT = 0, IsFuncT = 1, IsPtrMemT = 0 };
        typedef R BaseT;
        typedef R BottomT;
        typedef CompoundT<void> ClassT;
    };

    template<typename R, typename P1>
    class CompoundT<R(P1)> {
    public:
        enum { IsPtrT = 0, IsRefT = 0, IsArraryT = 0, IsFuncT = 1, IsPtrMemT = 0 };
        typedef R BaseT(P1);
        typedef R BottomT(P1);
        typedef CompoundT<void> ClassT;
    };

    template<typename R, typename P1>
    class CompoundT<R(P1, ...)> {
    public:
        enum { IsPtrT = 0, IsRefT = 0, IsArraryT = 0, IsFuncT = 1, IsPtrMemT = 0 };
        typedef R BaseT(P1);
        typedef R BottomT(P1);
        typedef CompoundT<void> ClassT;
    };



    struct SizeOverOne { char c[2]; };
    
    template<typename T, bool convert_possible = !CompoundT<T>::IsFuncT && !CompoundT<T>::IsArraryT >
    class ConsumeUDC {
    public:
        operator T() const;
    };

    template<typename T>
    class ConsumeUDC<T, false> {};

    template<bool convert_possible>
    class ConsumeUDC<void, convert_possible> {};

    char enum_check(bool);
    char enum_check(char);
    char enum_check(signed char);
    char enum_check(unsigned char);
    char enum_check(wchar_t);

    char enum_check(signed short);
    char enum_check(unsigned shor);
    char enum_check(signed int);
    char enum_check(unsigned int);
    char enum_check(signed long);
    char enum_check(unsigned long);
    char enum_check(signed long long);
    char enum_check(unsigned long long);

    char enum_check(float);
    char enum_check(double);
    char enum_check(long double);

    SizeOverOne enum_check(...);

    template<typename T>
    class IsEnumT {
    public:
        enum { Yes = IsFundaT<T>::No && 
                                !CompoundT<T>::IsRefT &&
                                !CompoundT<T>::IsPtrT &&
                                !CompoundT<T>::IsPtrMemT &&
                                sizeof(enum_check(ConsumeUDC<T>())) == 1 };
        enum { No = !Yes };
    };

    template<typename T>
    class IsClassT {
    public:
        enum { Yes = IsFundaT<T>::No && 
                                IsEnumT<T>::No && 
                                !CompoundT<T>::IsRefT &&
                                !CompoundT<T>::IsPtrT &&
                                !CompoundT<T>::IsArraryT &&
                                !CompoundT<T>::IsPtrMemT &&
                                !CompoundT<T>::IsFuncT };
        enum { No = !Yes };
    };


    template<typename T>
    class TypeT {
    public:
        enum { IsFundaT = IsFundaT<T>::Yes,
                    IsPtrT = CompoundT<T>::IsPtrT,
                    IsRefT = CompoundT<T>::IsRefT,
                    IsArraryT = CompoundT<T>::IsArraryT,
                    IsFuncT = CompoundT<T>::IsFuncT,
                    IsPtrMemT = CompoundT<T>::IsPtrMemT,
                    IsEnumT = IsEnumT<T>::Yes,
                    IsClassT = IsClassT<T>::Yes };
    };
    // TypeT end

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
    // TypeOp end    



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

    template <typename F, int N>
    class UsedFunctorParam;

    template <typename F, int N>
    class FunctorParam {
        private:
            class Unused {
                private:
                    class Private {};
                public:
                    typedef Private Type;
            };
        public:
            typedef typename IfThenElse<F::NumParams >= N, UsedFunctorParam<F, N>, Unused>::ResultT::Type Type;
    };

    template <typename F>
    class UsedFunctorParam<F, 1> {
      public:
        typedef typename F::Param1T Type;
    };


    #define FunctorParamSpec(N)     \
            template<typename F>        \
            class UsedFunctorParam<F, N> { \
                public:                              \
                    typedef typename F::Param##N##T Type;    \
            };

    FunctorParamSpec(2);
    FunctorParamSpec(3);
    FunctorParamSpec(4);
    FunctorParamSpec(5);
    FunctorParamSpec(6);
    FunctorParamSpec(7);
    FunctorParamSpec(8);
    FunctorParamSpec(9);
    FunctorParamSpec(10);
    FunctorParamSpec(11);

    #undef  FunctorParamSpec


    template<typename RT, typename P1 = void, typename P2 = void, typename P3 = void>
    class FunctionPtrT {
        public:
            enum { NumParams = 3 };
            typedef RT (*Type)(P1, P2, P3);
    };

    template<typename RT, typename P1, typename P2>
    class FunctionPtrT<RT, P1, P2, void> {
        public:
            enum { NumParams = 2 };
            typedef RT (*Type)(P1, P2);
    };

    template<typename RT, typename P1>
    class FunctionPtrT<RT, P1, void, void> {
        public:
            enum { NumParams = 1 };
            typedef RT (*Type)(P1);
    };

    template<typename RT>
    class FunctionPtrT<RT, void, void, void> {
        public:
            enum { NumParams = 0 };
            typedef RT (*Type)();
    };

    template<typename T>
    class ForwardParamT {
        public:
            typedef typename IfThenElse<TypeT<T>::IsClassT, typename TypeOp<T>::RefConstT, typename TypeOp<T>::ArgT>::ResultT Type;
    };

    template<>
    class ForwardParamT<void> {
        private:
            class Unused {};
        public:
            typedef Unused Type;
    };

    template<typename RT, typename P1 = void, typename P2 = void, typename P3 = void>
    class FunctionPtr {
        private:
            typedef typename FunctionPtrT<RT, P1, P2, P3>::Type FuncPtr;
            FuncPtr fptr;
        public:
            enum { NumParams = FunctionPtrT<RT, P1, P2, P3>::NumParams };
            typedef RT ReturnT;
            typedef P1 Param1T;
            typedef P2 Param2T;
            typedef P3 Param3T;

            FunctionPtr(FuncPtr ptr):fptr(ptr) {}

            RT operator() () { return fptr(); }
            RT operator() (typename ForwardParamT<P1>::Type a1) { return fptr(a1); }
            RT operator() (typename ForwardParamT<P1>::Type a1,
                                        typename ForwardParamT<P2>::Type a2) { return fptr(a1, a2); }
            RT operator() (typename ForwardParamT<P1>::Type a1, 
                                        typename ForwardParamT<P2>::Type a2,
                                        typename ForwardParamT<P3>::Type a3) { return fptr(a1, a2, a3); }

    };

    template<typename RT> inline
    FunctionPtr<RT> func_ptr(RT (*fp)())
    {
        return FunctionPtr<RT>(fp);
    }

    template<typename RT, typename P1> inline
    FunctionPtr<RT, P1> func_ptr(RT (*fp)(P1))
    {
        return FunctionPtr<RT, P1>(fp);
    }

    template<typename RT, typename P1, typename P2> inline
    FunctionPtr<RT, P1, P2> func_ptr(RT (*fp)(P1, P2))
    {
        return FunctionPtr<RT, P1, P2>(fp);
    }
    
    template<typename RT, typename P1, typename P2, typename P3> inline
    FunctionPtr<RT, P1, P2, P3> func_ptr(RT (*fp)(P1, P2, P3))
    {
        return FunctionPtr<RT, P1, P2, P3>(fp);
    }

    //compose
    template <typename C, int N>
    class BaseMem: public C {
        public:
            BaseMem(C& c): C(c) {}
            BaseMem(C const& c): C(c) {}
     };

    
    template <typename FO1, typename FO2>
    class Composer: private BaseMem<FO1, 1>, private BaseMem<FO2, 2> {
        public:
             enum { NumParams = FO1::NumParams };
            typedef typename FO2::ReturnT ReturnT;

            #define ComposerParamT(N) \
                            typedef typename FunctorParam<FO1, N>::Type Param##N##T 
                ComposerParamT(1);
                ComposerParamT(2);
                ComposerParamT(3);
                ComposerParamT(4);
                ComposerParamT(5);
                ComposerParamT(6);
                ComposerParamT(7);
                ComposerParamT(8);
                ComposerParamT(9);
                ComposerParamT(10);
            #undef ComposerParamT               

            
        public:
            Composer(FO1 const& f1, FO2 const& f2): BaseMem<FO1, 1>(f1), BaseMem<FO2, 2>(f2) {}
            Composer(FO1 const& f1, FO2& f2): BaseMem<FO1, 1>(f1), BaseMem<FO2, 2>(f2) {}
            Composer(FO1& f1, FO2 const& f2): BaseMem<FO1, 1>(f1), BaseMem<FO2, 2>(f2) {}
            Composer(FO1& f1, FO2& f2): BaseMem<FO1, 1>(f1), BaseMem<FO2, 2>(f2) {}

            ReturnT operator() () {
                return BaseMem<FO2,2>::operator() (BaseMem<FO1,1>::operator()());
                }
            
            ReturnT operator() (typename ForwardParamT<Param1T >::Type v1) {
                return BaseMem<FO2,2>::operator() (BaseMem<FO1,1>::operator()(v1));
                }
            
            ReturnT operator() (typename ForwardParamT<Param1T >::Type v1,
                                                typename ForwardParamT<Param2T >::Type v2) {
                return BaseMem<FO2,2>::operator() (BaseMem<FO1,1>::operator()(v1, v2));
                }            
    };
    

    template<typename FO1, typename FO2> inline
    Composer<FO1, FO2> compose (FO1 f1, FO2 f2) 
    {
        return Composer<FO1, FO2> (f1, f2);
    }
    // compose end    // ForwardParamT end
    

    template <typename T>
    class BoundVal {
        private:
            T value;
            
        public:
            typedef T ValueT;
            BoundVal(T v): value(v) {}
            typename TypeOp<T>::RefT get() { return value; }
    };

    template<typename T, T Val>
    class StaticBoundVal {
        public:
            typedef T ValueT;
            T get() { return Val; }
    };

    template<typename F, int P>
    class BinderParams {
        public:
            enum { NumParams = F::NumParams-1 };
        #define ComposeParamT(N)    \
            typedef typename IfThenElse<(N<P), FunctorParam<F, N>, FunctorParam<F, N+1> >::ResultT::Type Param##N##T
            ComposeParamT(1);
            ComposeParamT(2);
            ComposeParamT(3);
        #undef ComposeParamT
    };

    template<int S, typename NegT, typename ZeroT, typename PosT>
    class SignSelectT {
        public:
            typedef typename IfThenElse<(S<0), NegT, typename IfThenElse<(S>0), PosT, ZeroT>::ResultT>::ResultT ResultT;
    };
    

    template <typename FO, int P, typename V>
    class Binder: private FO, private V {
        public:
            enum { NumParams = FO::NumParams-1 };
            typedef typename FO::ReturnT ReturnT;
            typedef BinderParams<FO, P> Params;

            
        #define ComposeParamT(N)    \
            typedef typename ForwardParamT<typename Params::Param##N##T>::Type Param##N##T
            
           ComposeParamT(1);
            ComposeParamT(2);
            ComposeParamT(3);
            
        #undef ComposeParamT

        public:
            Binder(FO& f): FO(f) {}
            Binder(FO& f, V& v): FO(f), V(v) {}
            Binder(FO& f, V const& v): FO(f), V(v) {}
            Binder(FO const& f): FO(f) {}
            Binder(FO const& f, V& v): FO(f), V(v) {}
            Binder(FO const& f, V const& v): FO(f), V(v) {}
            template<typename  T>
            Binder(FO& f, T& v): FO(f), V(BoundVal<T>(v)) {}
            template<typename  T>
            Binder(FO& f, T const& v): FO(f), V(BoundVal<T const>(v)) {}

            
            ReturnT operator() () {
                return FO::operator()(V::get());
            }
            ReturnT operator() (Param1T v1) {
                return FO::operator() (ArgSelect<1>::from(v1, v1, V::get()), 
                                                   ArgSelect<2>::from(v1, v1, V::get()));
            }
            ReturnT operator() (Param1T v1, Param2T v2) {
                return FO::operator() (ArgSelect<1>::from(v1, v1, V::get()), 
                                                   ArgSelect<2>::from(v1, v2, V::get()), 
                                                   ArgSelect<3>::from(v2, v2, V::get()));
            }
            ReturnT operator() (Param1T v1, Param2T v2, Param3T v3) {
                return FO::operator() (ArgSelect<1>::from(v1, v1, V::get()), 
                                                   ArgSelect<2>::from(v1, v2, V::get()), 
                                                   ArgSelect<3>::from(v2, v3, V::get()),
                                                   ArgSelect<4>::from(v3, v3, V::get()));
            }

        private:
            template<int A>
            class ArgSelect {
                public:
                    typedef typename TypeOp<typename IfThenElse<(A<=Params::NumParams), 
                                                                                               FunctorParam<Params, A>, 
                                                                                               FunctorParam<Params, A-1> >::ResultT::Type>::RefT NoSkipT;
                    
                    typedef typename TypeOp<typename IfThenElse<(A>1), 
                                                                                               FunctorParam<Params, A-1>, 
                                                                                               FunctorParam<Params, A> >::ResultT::Type>::RefT SkipT;    

                    typedef typename TypeOp<typename V::ValueT>::RefT BindT;

                    class NoSkip {
                        public:
                            static NoSkipT select (SkipT prev_arg, NoSkipT arg, BindT bound_val) { return arg; }
                    };
                    
                    class Skip {
                        public:
                            static SkipT select (SkipT prev_arg, NoSkipT arg, BindT bound_val) { return prev_arg; }
                    };
                    
                   class Bind {
                        public:
                            static BindT select (SkipT prev_arg, NoSkipT arg, BindT bound_val) { return bound_val; }
                    };

                   typedef typename SignSelectT<A-P, NoSkipT, BindT, SkipT>::ResultT    ReturnT;
                   typedef typename SignSelectT<A-P, NoSkip, Bind, Skip>::ResultT   SelectedT;

                    static ReturnT from (SkipT prev_arg, NoSkipT arg, BindT bound_val) {
                        return SelectedT::select(prev_arg, arg, bound_val);
                    }
                   
            };
                    
    };


    template <int P, typename FO> inline
    Binder<FO, P, BoundVal<typename FunctorParam<FO, P>::Type> >
    bind(FO const& fo, typename ForwardParamT<typename FunctorParam<FO, P>::Type>::Type val)
    {
        return Binder<FO, P, BoundVal<typename FunctorParam<FO, P>::Type> >(fo, BoundVal<typename FunctorParam<FO, P>::Type> (val));
    }    

    template <int PNum, typename RT, typename P1> inline
    Binder<FunctionPtr<RT, P1>, PNum, BoundVal<typename FunctorParam<FunctionPtr<RT, P1>, PNum>::Type> >
    bindfp(RT (*fp)(P1), typename ForwardParamT<typename FunctorParam<FunctionPtr<RT, P1>, PNum>::Type>::Type val)
    {
        return Binder<FunctionPtr<RT, P1>, PNum, BoundVal<typename FunctorParam<FunctionPtr<RT, P1>, PNum>::Type> >
                            (func_ptr(fp), BoundVal<typename FunctorParam<FunctionPtr<RT, P1>, PNum>::Type>(val));
    }    
    
    template <int PNum, typename RT, typename P1, typename P2> inline
    Binder<FunctionPtr<RT, P1, P2>, PNum, BoundVal<typename FunctorParam<FunctionPtr<RT, P1, P2>, PNum>::Type> >
    bindfp(RT (*fp)(P1, P2), typename ForwardParamT<typename FunctorParam<FunctionPtr<RT, P1, P2>, PNum>::Type>::Type val)
    {
        return Binder<FunctionPtr<RT, P1, P2>, PNum, BoundVal<typename FunctorParam<FunctionPtr<RT, P1, P2>, PNum>::Type> >
                            (func_ptr(fp), BoundVal<typename FunctorParam<FunctionPtr<RT, P1, P2>, PNum>::Type>(val));
    }    

    template <int PNum, typename RT, typename P1, typename P2, typename P3> inline
    Binder<FunctionPtr<RT, P1, P2, P3>, PNum, BoundVal<typename FunctorParam<FunctionPtr<RT, P1, P2, P3>, PNum>::Type> >
    bindfp(RT (*fp)(P1, P2, P3), typename ForwardParamT<typename FunctorParam<FunctionPtr<RT, P1, P2, P3>, PNum>::Type>::Type val)
    {
        return Binder<FunctionPtr<RT, P1, P2, P3>, PNum, BoundVal<typename FunctorParam<FunctionPtr<RT, P1, P2, P3>, PNum>::Type> >
                            (func_ptr(fp), BoundVal<typename FunctorParam<FunctionPtr<RT, P1, P2, P3>, PNum>::Type>(val));
    }    


    

    
};

