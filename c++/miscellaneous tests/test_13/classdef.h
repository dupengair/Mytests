#pragma once
#include <string>
#include <iostream>

using namespace std;

class Enum {
public:
    Enum();    
    virtual ~Enum();
    virtual void testbm(void) = 0;
    void seti(int t) { i = t; }
    int geti(void) { return i; }
private:
    int i;
    
};



class ChildrenEnum : public Enum {
     
public:
    ChildrenEnum();
    virtual  ~ChildrenEnum(); 

    virtual void testbm(void);
    virtual int Enum(int i);
    ChildrenEnum& operator=(const ChildrenEnum& rhs)
        {
        Enum::operator=(rhs);
        t = rhs.t;
        return *this;
        }
    
    void sett(int y) { t= y; }
    int gett(void) { return t; }
    private:
        int t;
    
};


class TreeEnum : public ChildrenEnum {
     
public:
    TreeEnum();
    virtual  ~TreeEnum(); 

    virtual void testbm(void);
    virtual int Enum(int i);
    
};


template<typename T>
class Base {
public:
       void exit(void) { cout << " Base " << endl; }
};


template<typename T>
class Derived : Base<T> {
public:
       using Base<T>::exit;
       void exitd(void) {  exit(); }
};

    
    


