
#include <iostream>
#include <string.h>

#include "vehicle2.h"

using namespace std;

Vehicle2::Vehicle2(const char *pname)
{
    if((NULL != pname) && (strlen(pname) <= V_NAME_LEN))
        {
        strcpy(name, pname);
        }
	
    cout <<"new vehicle : " << name << endl;
}

Vehicle2::~Vehicle2()
{
    cout << "delete vehicle : " << name << endl;
}

void Vehicle2::getvehicle(void)
{
    cout << "Vehicle' s get vehicle : " << name << endl;
}


