#pragma once
#include <iostream>


using std::cout;
using std::endl;


template <typename... T>
void DummyWraper(T... t) {}

template <typename T>
T pr(T t) {
    cout << t;
    return t;    
}

template <typename... A>
void VTPrint(A... a) {
    DummyWraper(pr(a)...);
}
		
