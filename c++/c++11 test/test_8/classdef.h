#pragma once
#include <iostream>


using std::cout;
using std::endl;


namespace cpp11test {
    
    template <typename... T> struct MultiTypes;
    template <typename T1, typename... T>
    struct MultiTypes<T1, T...>: public MultiTypes<T...> {
        T1 t1;
        MultiTypes<T1, T...>(T1 a, T... b): t1(a), MultiTypes<T...>(b...) {
            cout << "MultiTypes<T1, T...>(T1 a, T... b)" << endl;
        }
    };


    
    template<> struct MultiTypes<> {
           MultiTypes<>() { cout << "MultiTypes<>()" << endl; }
    };

    template <template <typename...>class VariadicType, typename... Args>
    VariadicType<Args...> Build(Args&&... args) {
        return VariadicType<Args...> (std::forward<Args>(args)...);
    };
            
    
}
