#pragma once
#include <iostream>


using std::cout;
using std::endl;

/*class definition*/

class Size {
public:
    enum size { general, big, medium, small };
    size val;
public:
    Size(size s):val(s){}
    bool operator >= (const Size& s) { return val >= s.val; }
    static const Size General, Big, Medium, Small;
};

class Type {
public:
	enum type { general, high, medium, low };
	type val;
public:
	Type (type t):val(t){}
	bool operator >= (const Type& t) { return val >= t.val; }
	static const Type General, High, Medium, Low;
};
		
