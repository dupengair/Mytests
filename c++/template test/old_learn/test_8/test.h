#pragma once
#include <cstring>
#include <stddef.h>
#include <iostream>
#include "classdef.h"


using std::cout;
using std::endl;

namespace template_test
{

    template<typename T, bool Bitwise>
    class BitOrClassCSM;

    template<typename T> 
    class BitOrClassCSM<T, false> {
    public:
        static void copy (typename RParam<T>::ResultT src, T* dst) {
            *dst = src;
        }

        static void copy_n (const T* src, T* dst, size_t n) {
            for (size_t k = 0; k < n; k++) 
                dst[k] = src[k];
        }

        static void copy_init (typename RParam<T>::ResultT src, void* dst) {
            ::new(dst) T(src);
        }

        static void copy_init_n (const T* src, void* dst, size_t n) {
            for (size_t k = 0; k < 0; k++)
                ::new((void*)((char *)dst + k)) T(src[k]);
        }

        static void swap (T* a, T* b) {
            T tmp(*a);
            *a = *b;
            *b = tmp;
        }

       static void swap_n (T* a , T* b, size_t n) {
            for (size_t k = 0; k < 0; k++) {
                T tmp(a[k]);
                a[k] = b[k];
                b[k] = tmp;
                }
       };

       static void move (T* src, T* dst) {
            assert(src != dst);
            *dst = *src;
            src->~T();   
       };

       static void move_n (T* src, T* dst, size_t n) {
            assert(src != dst);
            for (size_t k = 0; k < n; k++) {
                *dst[k] = src[k];
                src[k].~T();   
            }
       };

       static void void_move_init (T* src, T* dst, size_t n) {
            assert(src != dst);
            ::new(dst) T(*src);
            src->~T();
       };   

       static void void_move_init_n (T* src, T* dst, size_t n) {
            assert(src != dst);
            for (size_t k = 0; k < n; k++) {
                ::new((void*)((char *)dst + k)) T(src[k]);
                src[k].~T();   
            }       
       };   
    };


    
    template<typename T> 
    class BitOrClassCSM<T, true> : public  BitOrClassCSM<T, false> {
    public:
        static void copy_n (const T* src, T* dst, size_t n) {
            std::memcpy((void*) dst, (void*)src, n);
        }

        static void copy_init_n (const T* src, void* dst, size_t n) {
            std::memcpy(dst, (void*)src, n);
        }

        static void move_n (const T* src, T* dst, size_t n) {
            assert(src != dst);
            std::memcpy((void*) dst, (void*)src, n);
        }
        
        static void move_init_n (const T* src, void* dst, size_t n) {
            assert(src != dst);
            std::memcpy(dst, (void*)src, n);
        }      
        
    };
        
    

    
};
