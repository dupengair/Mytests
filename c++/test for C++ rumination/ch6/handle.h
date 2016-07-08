#ifndef HANDLE_H
#define HANDLE_H

#include "point.h"
#include "upoint.h"

class Handle {
public:
    Handle(): up(new UPoint) {}
    Handle(int x, int y): up(new UPoint(x, y)) {}
    Handle(const Point&): up(new UPoint) {}
    Handle(const Handle& h): up(h.up) { ++up->u; }
    Handle& operator=(const Handle&);
    ~Handle() { if (--up->u == 0) delete up; }

    int x() const {return up->p.x(); };
    Handle& x(int);
    int y() const { return up->p.y(); };
    Handle& y(int);

private:
    UPoint *up;
};


#endif
