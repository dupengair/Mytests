#include <iostream>
#include <string.h>


using namespace std;



class StaticBase {
public:
    StaticBase();
    virtual ~StaticBase();

    class TooManyObjects{
        public:
            TooManyObjects() { cout << "too many objects!" << endl; }
        };

private: 
    static size_t numObjects;
    
    StaticBase(const StaticBase& rhs);
    //StaticBase();
};






class Derived : public StaticBase{
     
public:
    Derived();


  virtual  ~Derived(); 

    
};


class Third {
private:
    Derived d;
};





class Derived2 : private StaticBase{
     
public:
    Derived2();


  virtual  ~Derived2(); 

    
};