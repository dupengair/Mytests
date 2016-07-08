#include <iostream>
#include <list>
//#include "test.h"


using namespace std;


typedef void (*CblkBefore)(void);
typedef void (*CblkAfter)(int a, int b);

list<CblkBefore> funclist;

void func_1(int a, int b)
{
	cout << __func__ << " : a = " << a << " , b = " << b << endl;
}

void func_2(int a, int b)
{
	cout << __func__ << " : a = " << a << " , b = " << b << endl;
}

void func_3(int a, int b)
{
	cout << __func__ << " : a = " << a << " , b = " << b << endl;
}


void addCblk(const CblkBefore &func)
{
	static int count = 0;
	cout << "add func " << ++count << " , func = " << func << endl;
	funclist.push_back(func);
}

void invoke(int a, int b)
{	
	static int count = 0;
	
	for(typename list<CblkBefore>::iterator i = funclist.begin(); i != funclist.end(); ++i)
	{
		cout << "invoke func " << ++count << endl;
		((CblkAfter &)(*i))(a, b);
	}
}

#define REGISTERCLASS(NAME,CLASS) static BaseClass* __configlib_  ## NAME = CLASS

//ACTIONSTEP
REGISTERCLASS(__base_actionstep,new BaseClass(ActionStep::Type(),[](System::Object* obj) -> bool
{
	return dynamic_cast<Base::ActionStep*>(obj);
},[](void)
{
	return ActionStep::Create()->ToObject();
}));



int main()
{

    exfunc();
	addCblk((CblkBefore)func_1);
	addCblk((CblkBefore)func_2);
	addCblk((CblkBefore)func_3);
	
	
	cout << "funclist.size = " << funclist.size() << endl;

	invoke(1, 2);

	return 0;
}
