#ifndef HANDLE_H
#define HANDLE_H

#include "point.h"
#include "UseCount.h"


class Handle {
public:
    Handle(): p(new Point) {}
    Handle(int x, int y): p(new Point(x, y)) {}
    Handle(const Point&): p(new Point) {}
    Handle(const Handle& h): u(h.u), p(h.p) { }
    Handle& operator=(const Handle& h);
    ~Handle() { if ( u.only())  delete p; }

    int x() const {return p->x(); };
    Handle& x(int);
    int y() const { return p->y(); };
    Handle& y(int);

private:
    UseCount u;
    Point* p;
    
};


#endif
