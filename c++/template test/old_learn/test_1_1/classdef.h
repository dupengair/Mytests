#ifndef __CLASSDEF_H__
#define __CLASSDEF_H__


#include <iostream>
#include <cstring>
#include <cstdio>

using std::cout;
using std::endl;

namespace template_test
{

    template <typename T>
    inline T const& max(T const& a, T const& b)
    {
    	return a<b ? a : b;
    }

   inline char const* const& max(char const*  a, char const* b)
   //inline char const* max(char const*  a, char const* b)
    {
    	printf("addr of a: %p\n", a);
	printf("addr of b: %p\n", b);
    	return strcmp(a, b)<0 ? a : b;
    }

    template <typename T>
    inline T const& max(T const& a, T const& b, T const& c)
    {
    	return max(max(a, b), c);
    }


    int g(const int& i)
    {
        cout << "in g():" << i << endl;
        return i;
    }

    template<typename T>
    void f(T& t)
    {
    	cout << "test " << g(t) << endl;
    }


    template<typename T>
    class MyClass {
    private:
	T a;

    public:
        MyClass(T a):a(a) {}
        T get(void);
    };

    template<typename T>
    T MyClass<T>::get(void)
        {
            return a;
        }


    template <>
    class MyClass<int> {
    private:
	int a;

    public:
        MyClass(int a):a(a) {}
        int get(void);
    };


     int  MyClass<int>::get(void)
     {
            cout << "ll" << endl;
            return a;
     }

     template <const char* name>
     class MyChar {        
     public:
        void get(void) { cout << name << endl; }
     };


     template<typename T>
     class Name1 {
     T a;
     public:
       Name1(T t):a(t) {};
       void get(void) { cout <<"in Name1: " << a << endl; }
     };

    template<typename A, typename B = Name1<A> >
    class Name2 {
    A a;
    B b;
    public:
      Name2(A i): a(i), b(i+1) {}
      void get(void) { cout <<"in Name2: " << a << endl; b.get(); }
    };

    //template<typename A, template<typename B> class N = Name1 >
    template<typename A, template<typename> class N = Name1 >
    class Name3 {
    A a;
    N<A> b;
    public:
      Name3(A i): a(i), b(i+1) {}
      void get(void) { cout <<"in Name3: " << a << endl; b.get(); }
    };   

    
    template <typename T>
    inline T const& maxx (T const& a, T const& b)
    {
        return  a < b  ?  b : a;
    }

    template <typename T>
    inline T const& maxxx (T const a, T const b)
    {
        return  a < b  ?  b : a;
    }

};

#endif
