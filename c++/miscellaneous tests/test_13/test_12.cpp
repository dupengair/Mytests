#include <iostream>
#include "test.h"
#include <list>
#include <string>
#include <vector>
#include <sys/resource.h>
#include <algorithm>

using std::cout;
using std::endl;

template <typename T , int n=23>
void func(T& t)
{
    std::cout << "t = " << t <<std::endl;
    std::cout << "n = " << n <<std::endl;
}

int size(int (*fun)(const vector<int>& v), const vector<int>& v)
{
    return fun(v);
}

void lmt(void)
{
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    cout << "Physical Memory : " << usage.ru_maxrss << " bytes" << endl;    

    class vsize {
        public:
        int operator()(const vector<int>& v) { return v.size(); }
    };

    int a[4] = {1,2,3,4};
    vector<int> v(a, a+4);
    vsize vs;
    cout << "vsize = " << vs(v) << endl;
}


template<typename T>
class Ba {
public:
       void exit(void) { cout << " Base " << endl; }
};

Ba<float> bb;





int main(void)
{

    
    int t = 1;
    func<int, 5>(t);

    ChildrenEnum ce;
    ce.testbm();
    ce.Enum(1);

    lmt();

    ce.seti(5);
    ce.sett(6);
    cout << "ce :  " << ce.geti() << ce.gett() << endl;

    ChildrenEnum cd;


    cd.seti(1);
    cd.sett(2);
    cout << "cd : i = " << cd.geti() << cd.gett()  << endl;

    cd = ce;
    cout << "cd : i = " << cd.geti() << cd.gett()  << endl;
    

    return 0;
}


