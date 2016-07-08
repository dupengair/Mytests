#include <iostream>
#include "UseCount.h"

using namespace std;

bool UseCount::reattach(const UseCount& u)
{
    ++*u.p;
    if(--*p ==0) {
        cout << "only object before reattach " << endl;
        delete p;
        p = u.p;
        return true;
        }

     cout << "more than 1 objects before reattach " << endl;
    p = u.p;
    return false;
}

bool UseCount::makeonly()
{
    if(*p == 1) 
        return false;

    --*p;
    p = new int(1);
    return true;
}

