

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

