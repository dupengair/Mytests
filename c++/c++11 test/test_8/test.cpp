

#include "test.h"

struct X {
    X() { cout << "constructor" << endl; }
    X(X const& x) { cout << "copy constructor" << endl; }
    X(X&& x) { cout << "move constructor" << endl; }

    X& operator= (X const& x) {  cout << "copy assignment" << endl; }
    X&& operator= (X&& x) {  cout << "move assignment" << endl; }
};

X genX() {
    X x;
    return x;
}



int main() {

    A a;
    B b;

    //Build<MultiTypes>(a, b);

    X x;
    x = genX();

{
    int count = 3;
    const int y = [=] { int ret = 0, i = count; do{ret += i;}while(i-- != 0); return ret; }();
    cout << "y = " << y << endl;
}
}
