

class Base {
public:
    Base();
    ~Base();
    int i;

    static int member;

public:
   virtual void Interface() const =0;
   void test1(int a);

    
};



class Derived : public Base {
     
public:
    Derived();
    ~Derived(); 
   int i;

   

public:

    virtual void Interface() const;
    void test1(int a);
};

