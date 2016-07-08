#ifndef _VEHICLE_H
#define _VEHICLE_H


#define V_NAME_LEN 32

class Vehicle
{
public:
	static Vehicle* createNew(const char *pname);
	void getvehicle(void);
       void getname() const;
       void destroy();
protected:
	~Vehicle();
	Vehicle(const char *pname = "new vehicle");
	mutable char name[V_NAME_LEN];
	static Vehicle* instance;
};

	
#endif
