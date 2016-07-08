#include <iostream>

#include "test.h"


using namespace template_test;

using std::cout;
using std::endl;


int main(void)
{
	
	int* t = new int(2);
	CountPtr<int> p1(t);
	CountPtr<int> p2(t);

	cout << (p1 == p2) << endl;

    return 0;
}



