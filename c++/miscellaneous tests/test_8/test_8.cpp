#include <iostream>
#include "classdef.h"

using namespace std;

#if 0
//#define __TEST_TRAITS
//#define __TEST_TMP
#define __TEST_PFUNC



#ifdef __TEST_TRAITS
template<typename T>
struct iterator_traits1 
{
    typedef typename T::value_type value_type;
};



template<typename T>
struct iterator_traits1<T*> 
{
    typedef T value_type;
};



template<typename T>
typename iterator_traits1<T>::value_type func(T iter)
{
    return *iter;
}

template<typename T>
struct MyIter
{
    typedef T value_type;
    T* ptr;
    MyIter(T* p = 0):ptr(p) {}
    T& operator*() const { return *ptr; }
};


int main()
{
    int i = 23;
    int *p=&i;
    MyIter<int> mit = &i;

    //cout << func(i) << endl;  
    cout << func(p) << endl;
    cout << func(mit) << endl;
}

#endif 

#ifdef __TEST_TMP
template<unsigned n>
struct Factorial 
{
    enum { value = n * Factorial<n -1>::value };
};

template<>
struct Factorial<0> 
{
    enum { value = 1 };
};

int main()
{
    cout << Factorial<5>::value<<endl;
    cout << Factorial<10>::value<<endl;
}
    
#endif

#ifdef __TEST_PFUNC

typedef int (*FUNC)(int);

int func(int p)
{
    return p;
}

int caller(int p, FUNC f)
{
    return f(p);
}

int caller1(int p, int (int))
{
    return p;
}


int main()
{
    cout << caller1(5, func) <<endl;
}
   

#endif

#else

/*void* operator new(size_t, void* ptr) throw()
{
    return ptr;
}*/


int main()
{
/*
    cout << "test_8 start" << endl;
    
    Derived d;
    d.Interface();
    cout << "d.i = " << d.i << endl;
     cout << "d.Base::i = " << d.Base::i << endl;
*/

    Base *pb = new  Derived();
    pb->Interface();
    cout << "pb->i = " << pb->i << endl;

    pb->test1(1);
    Derived d;
    d.test1(2);
/*


    string str="0123";

    string::size_type Pos = str.find("\n", string::npos+1);

    cout<<" find : " << Pos << " , value = " << str[Pos] << endl;
    */
       
}

#endif
