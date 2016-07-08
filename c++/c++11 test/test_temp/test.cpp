#include <iostream>
#include <vector>
#include <string>

#include "test.h"


using namespace cpp11test;

using std::cout;
using std::endl;
using std::string;

class C
{
    string str;
    public:
        C(const string& s):str(s) {}
        string& get() { return str; }
};



int main() 
{
    string ary[] = {"1", "2", "3" };
    std::vector<string> vs;
    for (auto& elem: ary) {
        vs.push_back(elem);
    }

#if 1
    for (C& c: vs) {
        cout << "c: " << c.get() << endl;
    }
#else
    C c = vs[1];
    cout << "c: " << c.get() << endl; 
#endif
    
}



