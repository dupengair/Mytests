#ifndef _FACTORY_H
#define _FACTORY_H


class product
{
public: 
    product(char * name);
    ~product();
    void destroy();
};

class product_A : public product
{
public :
    product_A(char * name = "no name A");
    ~product_A();
};

class product_B : public product
{
public :
    product_B(char * name = "no name B");
    ~product_B();
};


class factory
{
public :
    factory();
    ~factory();

    virtual product *CreateProduct(char * name) =0;
};

class factory_A: public factory
{
public :
    factory_A();
    ~factory_A();

    product *CreateProduct(char * name);
};

class factory_B: public factory
{
public: 
    factory_B();
    ~factory_B();

    product *CreateProduct(char * name);
};

#endif
