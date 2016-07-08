
#include <stdio.h>
#include <string.h>
#include "car.h"




int Car::car = 1;

Car::Car(const char *pname):Vehicle(pname)
{
	
	printf("new car : %d %s\n", car, name);
	car++;
}

Car::~Car()
{
	car--;
	printf("delete car : %d %s\n", car, name);
}

void Car::getname(void)
{
	printf("car : %d %s\n", car, name);
}

