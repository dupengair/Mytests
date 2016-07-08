#include <iostream>
#include <string>
#include <boost/smart_ptr.hpp> 
#include <boost/make_shared.hpp> 

#include "product.h"

using namespace std;
using namespace boost;
using namespace test_boost;


typedef shared_ptr<Product> ProductPtr;
typedef weak_ptr<Product> ProductWPtr;
typedef shared_ptr<self_shared> self_sharedPtr;



int main(void)
{
//    Product *pdt = new Product_A();
//    pdt->show();

/*
    Product_B *pdt_B = new Product_B();


    Product_A AA;
    AA.test_call(pdt_B);
    cout << "BBB :" << BBB << endl;
    cout << "KAKA :" << Product_B::KAKA << endl;
*/



    
  //  pdt_B->test_B(111);

    shared_ptr<Product> p1;

    if(NULL == p1)
        {
        cout << "1. p1 is null" << endl;
        }
    
    p1.reset(new Product_A(123));

    if(NULL == p1)
        {
        cout << "2. p1 is null" << endl;
        }

    p1->show();
/*
    shared_ptr<Product> p1(new Product_A(123));
    p1->show();

    ProductPtr p2(new Product_A(321));
    p2->show();

    ProductPtr p3 = make_shared<Product_A>(132);
    p3->show();

    ProductWPtr wp1(p1);
    if(!wp1.expired())
        {
        ProductPtr p4=wp1.lock();
        p4->show();
        cout << "p4 count1 = " << p4.use_count() << endl;
        cout << "p1 count1 = " << p1.use_count() << endl;
        }
    
    self_sharedPtr ssp1(new self_shared(555));
    ssp1->show();
    cout << "ssp1 count1 = " << ssp1.use_count() << endl;
    
    self_sharedPtr ssp2 = ssp1->shared_from_this();
    ssp2->show();
    cout << "ssp1 count1 = " << ssp1.use_count() << endl;
    cout << "ssp2 count1 = " << ssp2.use_count() << endl;
*/
    
//    delete pdt;
//    delete pdt_B;
    return 0;
}

