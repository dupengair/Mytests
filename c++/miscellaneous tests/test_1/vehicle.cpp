
#include <iostream>
#include <string.h>

#include "vehicle.h"

using namespace std;

Vehicle::Vehicle(const char *pname)
{
    if((NULL != pname) && (strlen(pname) <= V_NAME_LEN))
        {
        strcpy(name, pname);
        }
	
    cout <<"new vehicle : " << name << endl;
}

Vehicle::~Vehicle()
{
    cout << "delete vehicle : " << name << endl;
}

void Vehicle::getvehicle(void)
{
    cout << "Vehicle' s get vehicle : " << name << endl;
}


