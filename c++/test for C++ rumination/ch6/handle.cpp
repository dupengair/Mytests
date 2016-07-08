#include "handle.h"

Handle& Handle::operator=(const Handle& h)
{
    ++h.up->u;
    if(--up->u == 0)
            delete up;
    up = h.up;
    return *this;
}


Handle& Handle::x(int x0)
{
    if (up->u != 1) {
        --up->u;
        up = new UPoint(up->p);
        }

    up->p.x(x0);
    return *this;
}

Handle& Handle::y(int y0)
{
    if (up->u != 1) {
        --up->u;
        up = new UPoint(up->p);
        }

    up->p.y(y0);
    return *this;
}
