#include <stdio.h>
#include <string.h>

#include "vehicle2.h"
#include "motor2.h"


int Motor2::motor = 1;

Motor2::Motor2(const char *pname):Vehicle2(pname)
{
	
	printf("new motor : %d %s\n", motor, name);
	motor++;
}

Motor2::~Motor2()
{
	motor--;
	printf("delete motor : %d %s\n", motor, name);
}

void Motor2::getvehicle(void)
{
	printf("Motor's get getvehicle : %d %s\n", motor, name);
}


int Motor2::getmotor(void)
{
	printf("get motor : %d %s\n", motor, name);
 	return motor;
}
	
void Motor2::getname(void)
{
	printf("motor : %d %s\n", motor, name);
}



