#include <iostream>

#include "motor.h"
#include "vehicle.h"
#include "car.h"
#include "bike.h"
#include "motorbike.h"
#include "test1.h"
#include "testMap.h"
#include "motor2.h"
#include "vehicle2.h"




using namespace std;

void vehicleFn(Vehicle &v)
{
    cout << "get vehicle - ";
    v.getvehicle();
}

void motorbikeFn(Vehicle &mb)
{
    cout << "get motorbike :\n";
    mb.getname();
}

void vehicleFn2(Vehicle2 &v)
{
    cout << "get vehicle - ";
    v.getvehicle();
}


int main()
{

    Motor2 m("m_dup");
    Vehicle2*vp = &m;

    vehicleFn2(m);
    m.getvehicle();
    vp->getvehicle();
/*    m.getname();
    vp->getvehicle();
    vp->getname();
  */
  
//	Vehicle2 v("v_dup");
//	Car c("c_dup");
//	Bike b("b_dup");
 //   test_display();
//    test_display_map();
 //   test_display_map2();
//    Motorbike mb("mb_dup");
//	m.getvehicle();
//	b.getvehicle();
//	mb.getvehicle();
//	motorbikeFn(mb);
	
//	motorFn(m);
//	vehicleFn2(v);

//	vehicleFn(c);
//	vehicleFn(b);
	
	return 0;
}

