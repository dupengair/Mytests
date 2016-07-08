
#include <iostream>
#include <string.h>

#include "vehicle.h"

using namespace std;

Vehicle* Vehicle::instance = 0;

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

void Vehicle::getname(void) const
{
    cout << "Vehicle' s get name : " << name << endl;
    strcpy(name, "hahaha");
}

Vehicle* Vehicle::createNew(const char *pname)
{
#if 1
    if(instance == 0)
        {
        instance = new Vehicle(pname);
        }

    return instance;
#else
    return new Vehicle(pname);
#endif
}

void Vehicle::destroy(void)
{
    delete this;
}


