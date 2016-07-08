#include <iostream>
#include <string.h>

#include "vehicle.h"


using namespace std;

void vehicleFn(Vehicle &v)
{
    cout << "get vehicle - ";
    v.getvehicle();
}




int main()
{

    Vehicle *vp = Vehicle::createNew("v_dup");
    //Vehicle *vp2 = Vehicle::createNew("v_dup2");

    
    vp->getvehicle();
    //vp2->getvehicle();

    vp->destroy();
   // vp2->destroy();

    return 0;
}

