#ifndef _MOTOR_H
#define _MOTOR_H

#include "vehicle.h"

#define M_NAME_LEN 10

class Motor : virtual public Vehicle
//class Motor : public Vehicle
{
public:
	Motor(const char *pname = "new motor");
	~Motor();
	virtual void getvehicle(void);
	int getmotor();
	void getname(void);
protected:
	static int motor;
};

#endif
