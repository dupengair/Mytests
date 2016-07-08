#include <stdio.h>
#include <string.h>

#include "motorbike.h"
#include "motor.h"
#include "bike.h"

using namespace std;

int Motorbike::motorbike = 1;

Motorbike::Motorbike(const char *pname):Vehicle(pname), Bike(pname), Motor(pname)
{
	
	printf("new motorbike : %d %s\n", motorbike, name);
	motorbike++;
	mb_use = MB_BIKE;
}

Motorbike::~Motorbike()
{
	motorbike--;
	printf("delete motorbike : %d %s\n", motorbike, name);
}



MB_USE Motorbike::getUse(void)
{
	return mb_use;
}


void Motorbike::setUse(MB_USE use)
{
	mb_use = use;
}

void Motorbike::getname(void)
{
	printf("motorbike : %d %s\n", motorbike, name);
}

ostream& operator << (ostream &os, Motorbike &mb)
{
    os << "name = " << mb.name << " , " << "use = " << mb.mb_use << endl;
    return os;
}

