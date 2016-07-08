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
    
   
 class Product_B: public Product 
    {
    public:
    	void show(void);        

    //protected:
    	Product_B(int var = 0);
    	 ~Product_B();
        int var;
    };

 
    class Product_A: public Product 
    {
    public:
    	void show(void);        

    //protected:
    	Product_A(int var = 0);
    	virtual ~Product_A();
        int var;
       
    };


class self_shared;
typedef shared_ptr<self_shared> self_sharedPtr;

    class self_shared : public enable_shared_from_this<self_shared>
    {
    public:
    	void show(void);

    //protected:
    	self_shared(int var = 0);
    	~self_shared();
           int var;

        self_sharedPtr ToObject() { return shared_from_this(); }
    };
    
}

#endif
