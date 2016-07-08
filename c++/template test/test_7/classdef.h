#include <iostream>
#include <stddef.h>
#include <cassert>
#include <cstring>
#include <typeinfo>


namespace template_test
{

    using std::cout;
    using std::endl;


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
        enum { IsPtrT = 0, IsRefT = 0, IsArraryT = 1, IsFuncT = 0, IsPtrMemT = 1 };
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


    template<typename T>
    void check() {
        if(TypeT<T>::IsFundaT)  cout << "IsFundaT" << endl;
        if(TypeT<T>::IsPtrT)  cout << "IsPtrT" << endl;
        if(TypeT<T>::IsRefT)  cout << "IsRefT" << endl;
        if(TypeT<T>::IsArraryT)  cout << "IsArraryT" << endl;
        if(TypeT<T>::IsFuncT)  cout << "IsFuncT" << endl;
        if(TypeT<T>::IsPtrMemT)  cout << "IsPtrMemT" << endl;
        if(TypeT<T>::IsEnumT)  cout << "IsEnumT" << endl;
        if(TypeT<T>::IsClassT)  cout << "IsClassT" << endl;
    }

    template<typename T>
    void checkT(T) {
        check<T>();

        if(TypeT<T>::IsPtrT || TypeT<T>::IsPtrMemT)
            check<typename CompoundT<T>::BaseT>();
    }
                                
        
};

    
