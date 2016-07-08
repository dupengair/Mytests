
#include <iostream>
#include "point.h"
#include "handle.h"

int main()
{
    Point p1, p2, p3, p4;
    Handle h1(p1), h2(p2), h3(p3), h4(p4);

    h1 = h2;
    h1.x(1);
    
    
}
