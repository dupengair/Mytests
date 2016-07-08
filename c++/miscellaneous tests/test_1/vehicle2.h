#ifndef _VEHICLE2_H
#define _VEHICLE2_H


#define V_NAME_LEN 32

class Vehicle2
{
public:
	Vehicle2(const char *pname = "new vehicle");
	~Vehicle2();
	virtual void getvehicle(void);
	//virtual void getname(void) ;
protected:
	char name[V_NAME_LEN];
};

	
#endif

