#include <iostream>
#include <string>
#include <list>
#include <boost/smart_ptr.hpp> 
#include <boost/make_shared.hpp> 

#include "product.h"

using namespace std;
using namespace boost;
using namespace test_boost;


typedef shared_ptr<Product> ProductPtr;
typedef weak_ptr<Product> ProductWPtr;


list<ProductPtr> pdtList;

void func(ProductPtr p)
{
//    ProductPtr pdt(new Product_A());
//        (*p).show();
        p->show();

//    pdtList.push_back(pdt);

//    Product_B BB(234);


//    delete pdt;
}
 self_sharedPtr Create()
    {
        self_sharedPtr ssp= make_shared<self_shared>(1);

        return ssp;
    }



int test_lvalue()
{
    int a = 3;
    return a;
}


int main(void)
{
    #if 1
    Product *pdt = new Product_A();
    pdt->show();

    shared_ptr<Product> p1(new Product_A(123));
    p1->show();

    ProductPtr p2(new Product_A(321));
    p2->show();

    ProductPtr p3 = make_shared<Product_A>(132);
    p3->show();
     cout << "p3 count1 = " << p3.use_count() << endl;
    

    
    ProductWPtr wp1(p1);
    if(!wp1.expired())
        {
        ProductPtr p4=wp1.lock();
        p4->show();
        cout << "p1 count1 = " << p1.use_count() << endl;
        cout << "p2 count1 = " << p2.use_count() << endl;
        cout << "p3 count1 = " << p3.use_count() << endl;
        cout << "p4 count1 = " << p4.use_count() << endl;
        }
    
    self_sharedPtr ssp1(new self_shared(555));
    ssp1->show();
    cout << "ssp1 count1 = " << ssp1.use_count() << endl;

    
    self_sharedPtr ssp2 = ssp1->shared_from_this();
    ssp2->show();
    cout << "ssp1 count1 = " << ssp1.use_count() << endl;
    cout << "ssp2 count1 = " << ssp2.use_count() << endl;

    
    self_sharedPtr ssp3 = ssp1;
    cout << "ssp1 count1 = " << ssp1.use_count() << endl;
    cout << "ssp2 count1 = " << ssp2.use_count() << endl;
    cout << "ssp3 count1 = " << ssp3.use_count() << endl;
    
   delete pdt;

   #else
   Create()->ToObject();

   const int& val = test_lvalue();

   cout << "val = " << val <<endl;
   
    #endif
   
    return 0;
}

