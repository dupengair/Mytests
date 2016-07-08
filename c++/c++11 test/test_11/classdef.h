#pragma once
#include <iostream>
#include <stdexcept>


using std::cout;
using std::endl;


namespace cpp11test {
    
void Printf(const char* s) {
    while(*s) {
        if((*s == '%') && (*++s != '%')) 
            throw std::runtime_error("invalid format string: missing arguments");
        cout << *s++;
    }
}

template<typename T, typename... Args>
void Printf(const char* s, T value, Args... args) {
    while(*s) {
        if((*s == '%') && (*++s != '%')) {
            cout << value;
            return Printf(++s, args...);
        }
        cout << *s++;
    }
     throw std::runtime_error("extra arguments");
}
    
}
