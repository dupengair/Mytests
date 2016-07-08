#pragma once
#include <string>

using namespace std;

class Base {
public:
    Base();
    virtual ~Base();

    virtual int testbm(void);
    
private:
   int bm1;
   int bm2;
   static int count;
    
};



class Derived : public Base {
     
public:
    Derived();
  virtual  ~Derived(); 

    virtual int testbm(void);
    
    
private:
   int dm1;
   int dm2;
    
};

class movecp {
public:
    movecp(int t = 0):a(t) { cout << "ctor: a  = " << a << endl;}
    movecp(const movecp& t) { a = t.a; cout << "cctor: a  = " << a << endl; }

private:
    int a;
    
};

