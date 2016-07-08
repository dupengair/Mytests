

class Base {
public:
    Base();
    ~Base();

    int i;

public:
    int NVI_Interface() const;

private:
    virtual int NVI_Impl() const;
    
};


class Derived : public Base {
public:
    Derived();
    ~Derived();   
    void test();

private:
    virtual int NVI_Impl() const;
};

class Derived2 : private Base {
public:
    Derived2();
    ~Derived2();    
    void test2();

private:
    virtual int NVI_Impl() const;
};