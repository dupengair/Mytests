
#include <stdio.h>
#include <string.h>

#include "vehicle.h"
#include "motor.h"


int Motor::motor = 1;

Motor::Motor(const char *pname):Vehicle(pname)
{
	
	printf("new motor : %d %s\n", motor, name);
	motor++;
}

Motor::~Motor()
{
	motor--;
	printf("delete motor : %d %s\n", motor, name);
}

void Motor::getvehicle(void)
{
	printf("Motor's get getvehicle : %d %s\n", motor, name);
}


int Motor::getmotor(void)
{
	printf("get motor : %d %s\n", motor, name);
 	return motor;
}
	
void Motor::getname(void)
{
	printf("motor : %d %s\n", motor, name);
}



