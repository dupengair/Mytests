#ifndef _TEST_4_H
#define _TEST_4_H


class product
{
public: 
    product(char * name);
    virtual ~product();
    virtual void display(int ID = 111) = 0;    /* 基类声明，子类实现*/
    virtual void display2(int ID = 555);        /* 基类实现，子类重载*/
    virtual void display3(int ID);        
    virtual void display4();        
    
    void destroy();
    void ppp(void);
};

class product_A : public product
{
public :
    product_A(char * name = "no name A");
    ~product_A();
    virtual void display(int ID);
    virtual void display2(int ID);
    virtual void display3();
    virtual void display4();   
    void haha(void);
    void ppp(void);
};

class test
{
public: 
    test();
    ~test();
    virtual void display();
};

class ttest: public test
{
public: 
      ttest();
    ~ttest();  
    virtual void display();
};

#endif
