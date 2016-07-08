#include "handle.h"
#include <iostream>
#include <thread>

using namespace std;

Handle& Handle::operator=(const Handle& h)
{
    if(u.reattach(h.u))        
        delete p; 
    
    p = h.p;    
    return *this;
}


Handle& Handle::x(int x0)
{   
    if(u.makeonly()) {
        p = new Point(*p);
        cout << "shared pointer makeonly " << endl;
        }
    else {
        cout << "no shared pointer " << endl;
        }

    p->x(x0);
    return *this;
}

Handle& Handle::y(int y0)
{
    if(u.makeonly()) {
        p = new Point(*p);
        cout << "shared pointer makeonly " << endl;
        }
    else {
        cout << "no shared pointer " << endl;
        }
    
    p->y(y0);
    return *this;
}
