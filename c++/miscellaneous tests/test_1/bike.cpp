#include <stdio.h>
#include<string.h>
#include "bike.h"




int Bike::bike = 1;

Bike::Bike(const char *pname):Vehicle(pname)
{
	
	printf("new bike : %d %s\n", bike, name);
	bike++;
}

Bike::~Bike()
{
	bike--;
	printf("delete bike : %d %s\n", bike, name);
}

void Bike::getname(void)
{
	printf("bike : %d %s\n", bike, name);
}

