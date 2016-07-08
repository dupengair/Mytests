#ifndef _MOTOR2_H
#define _MOTOR2_H

#include "vehicle2.h"

#define M_NAME_LEN 10

class Motor2 : public Vehicle2
//class Motor : public Vehicle
{
public:
	Motor2(const char *pname = "new motor");
	~Motor2();
	void getvehicle(void);
	int getmotor();
	void getname(void);
protected:
	static int motor;
};

#endif

