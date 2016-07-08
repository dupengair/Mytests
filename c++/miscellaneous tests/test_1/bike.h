#ifndef _BIKE_H
#define _BIKE_H



#include "vehicle.h"


class Bike : virtual public Vehicle
//class Bike : public Vehicle
{
public:
	Bike(const char *pname = "new bike");
	~Bike();
	void getname(void);
protected:
	static int bike;
};

#endif

