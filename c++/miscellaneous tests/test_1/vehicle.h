#ifndef _VEHICLE_H
#define _VEHICLE_H


#define V_NAME_LEN 32

class Vehicle
{
public:
	Vehicle(const char *pname = "new vehicle");
	~Vehicle();
	virtual void getvehicle(void);
	virtual void getname(void) = 0;
protected:
	char name[V_NAME_LEN];
};

	
#endif
