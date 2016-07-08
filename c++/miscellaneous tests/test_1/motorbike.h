#ifndef _MOTORBIKE_H
#define _MOTORBIKE_H

#include <iostream>

#include "motor.h"
#include "bike.h"


#define MB_NAME_LEN 32

enum MB_USE
{
	MB_BIKE = 0,
	MB_MOTOR
};

class Motorbike : public Bike, public Motor
{
public:
	Motorbike(const char *pname = "new motorbike");
	~Motorbike();
	MB_USE getUse(void);
	void setUse(MB_USE use);
	void getname(void);
	friend std::ostream & operator << (std::ostream &os, Motorbike &mb);
protected:
	static int motorbike;
	MB_USE mb_use;
};


#endif

