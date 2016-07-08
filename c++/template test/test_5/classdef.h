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

    
    template<typename T>
    class RParam {
    public:
        typedef typename IfThenElse<IsClassT<T>::No, T, T const&>::ResultT Type;
    };


    template <typename T, bool BitWise>
    class BitOrClassCSM;

    template <typename T>
    class BitOrClassCSM<T, false> {
    public:
        static void copy (typename RParam<T>::ResultT src, T* dst) {
            *dst = src;
        }

        static void copy_n (typename RParam<T>::ResultT src, T* dst, size_t n) {
            for(size_t k=0; k<n; ++k) {
                *dst[k] = src[k];
            }
        }

        static void copy_init (typename RParam<T>::ResultT src, T* dst) {
            ::new(dst) T(src);
        }
         
         static void copy_init_n (T const* src, T* dst, size_t n) {
             for(size_t k=0; k<n; ++k) {
                 ::new((void*)((char*)dst+k) T(src[k]);
             }
         }
         

        static void swap(T* a, T* b) {
            T tmp(*a);
            *a = *b;
            *b = tmp;
        }

        static void swap_n (T* a, T* b, size_t n) {
            for(size_t k=0;k<n;++k) {
                T tmp(a[k]);
                a[k] = b[k];
                b[k] = tmp;
            }
        }
        
                
        static void move(T* src, T* dst) {
            assert(src != dst);
            *dst = *src;
            src->~T();
        }

        static void move_n(T* src, T* dst, size_t n) {
            assert(src != dst);
            for(size_t k=0;k<n;++k) {
                dst[k] = src[k];
                src[k].~T();
            }
        }

        static void move_init(T* src, T* dst) {
            assert(src != dst);
            ::new(dst) T(src);
            *dst = *src;
            src->~T();
        }

        static void move_init_n(T* src, T* dst, size_t n) {
            assert(src != dst);
            for(size_t k=0;k<n;++k) {
                ::new((void*)((char*)dst+k) T(src[k]);
                src[k].~T();
            }
        }
    };


    template <typename T>
    class BitOrClassCSM<T, true> : public BitOrClassCSM<T, false> {
    public:

        static void copy_n (typename RParam<T>::ResultT src, T* dst, size_t n) {
            std::memcpy((void*)dst, (void*)src, n);
        }
         
        static void copy_init_n (T const* src, T* dst, size_t n) {
             std::memcpy(dst, (void*)src, n);
        }

        static void move_n(T* src, T* dst, size_t n) {
            assert(src != dst);
            std::memcpy((void*)dst, (void*)src, n);
        }

        static void move_init_n(T const* src, T const* dst, size_t n) {
            assert(src != dst);
            std::memcpy(dst, (void*)src, n);
        }
    };


    template <typename T>
    class CSMtraits: public BitOrClassCSM<T, IsClassT<T>::No > {};
        

};
