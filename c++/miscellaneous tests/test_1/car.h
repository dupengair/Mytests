#ifndef _CAR_H
#define _CAR_H



#include "vehicle.h"


class Car : public Vehicle
{
public:
	Car(const char *pname = "new car");
	~Car();
	void getname(void);
protected:
	static int car;
};

#endif
