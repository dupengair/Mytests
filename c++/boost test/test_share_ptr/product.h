#ifndef PRODUCT_H
#define PRODUCT_H

//#include <boost/smart_ptr.hpp> 
#include <boost/make_shared.hpp> 
#include <boost/enable_shared_from_this.hpp>

namespace test_boost {

    using namespace std;
    using namespace boost;

    class Product
    {
    public:
    	virtual void show(void) = 0;

    //protected:
    	Product();
    	virtual ~Product();
    	//~Product();
    };
    
   
 class Product_B
    {
    private:
         #define BBB 123321
    public:
        enum {KAKA = 9};
         enum {GAGA = 5555} guagua;
    public:
        typedef void (*FUNC_test_B)(int args);
    public:
       void caller_B(FUNC_test_B test_B)
        {
        guagua = GAGA;
        test_B(111);
        }
       void test_B(int args);
       
    };

 
    class Product_A: public Product 
    {
    public:
        typedef void (Product_A::*FUNC_test_A)(int args);
    public:
    	void show(void);        

    //protected:
    	Product_A(int var = 0);
    	~Product_A();
           int var;

       void test_call(Product_B* caller)
        {
        //caller->caller_B((Product_B::FUNC_test_B)& test_A);
        FUNC_test_A pFunc= &Product_A::test_A;
        caller->caller_B((Product_B::FUNC_test_B)pFunc);
        }
   private:
       //static void test_A(int args)
       void test_A(int args)
        {
        cout << "in Product_A : test_A " << BBB << Product_B::KAKA << endl;
        }
       
    };





    class self_shared : public enable_shared_from_this<self_shared>
    {
    public:
    	void show(void);

    //protected:
    	self_shared(int var = 0);
    	~self_shared();
           int var;
    };
    
}

#endif
