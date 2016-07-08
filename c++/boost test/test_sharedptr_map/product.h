#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <map>
#include <boost/smart_ptr.hpp> 
//#include <boost/make_shared.hpp> 
//#include <boost/enable_shared_from_this.hpp>





namespace test_boost {

    using namespace std;
    using namespace boost;

    class Product
    {
    public:
    	virtual void show(void);

    	Product(string name);
       Product(const Product& rhs);
       Product& operator=(const Product& rhs); 
       
    	virtual ~Product();

    public:
        string name;
    };
    
 
    class Product_A: public Product 
    {

    public:
    	void show(void);    

    	Product_A(string name);
    	~Product_A();     

    };


    typedef shared_ptr<Product> ProductPtr;
    typedef weak_ptr<Product> ProductWPtr;
    typedef map<string, ProductPtr> TPDTMAP;
    typedef map<string, Product*> TPDTOBJMAP;


    class Factory{
    public: 
           ProductPtr produce(string name) {
                cout << "produce product : " << name << endl;
                ProductPtr pdt;
                pdt.reset(new Product_A(name));
               // cout << " use count 1 : " << pdt.use_count() << endl;
                return pdt;
            }         

            Product* produceobj(string name) {
                cout << "produce product obj: " << name << endl;
                return (new Product(name));
            } 
    };





}

#endif
