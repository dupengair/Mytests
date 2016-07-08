#include <iostream>
#include <cmath>
#include <cstdlib>

#include "classdef.h"

using namespace template_test;

bool func(std::string const& str, double d, float f)
{
    cout << str << ": " << d << (d<f ? "<" : ">=") << f << endl;
    return d < f;
}

bool compare(std::string debugstr, double v1, float v2)
{
    if(debugstr != "") {
        cout << debugstr << ": " << v1 << (v1<v2?'<':'>') << v2 << endl;
    }

    return v1 < v2;
}

void print_name_value(std::string name, double value)
{
    cout << name << ": " << value << endl;
}

double sub (double a, double b)
{
    return a - b;
}

double twice(double a)
{
    return 2*a;
}


int main()
{
    bool result = bind<1>(func_ptr(func), "Comparing")(1.0, 2.0);
    cout << "bound function returned: " << result << endl;

    cout << "Composition result: " << compose(func_ptr(sub), func_ptr(twice))(3.0, 7.0) << endl;
    cout << "Binding result: " << bindfp<1>(compare, "main()->compare()")(1.02, 1.03) << endl;
    cout << "Binding output: ";
    bindfp<1>(print_name_value, "the ultimate answer to life")(42);
    cout << "Mixing composition and binding (bind<1>): " << bind<1>(compose(func_ptr(sub), func_ptr(twice)), 7.0)(3.0) << endl;
    cout << "Mixing composition and binding (bind<2>): " << bind<2>(compose(func_ptr(sub), func_ptr(twice)), 7.0)(3.0) << endl;

}

