#include <vector>
#include <iostream>

#include "test_4.h"


using std::vector;
using std::cout;
using std::endl;

void func(test*  t)
{
    t->display();
}


int main()
{

#if 0
    vector<vector<int> > vec; //> >之间必须有空格!!!!
    
    product *p=new product_A("pdt1");
    
    p->display(123);
    p->display();

    p->display2(123);
    p->display2();

    p->display3(321);
    //p->display3();                    error!
    //p->product_A::display3();   error!

    product_A aa("pdt2");
    aa.display3();
    //aa.product::display3(123);   error!
    //aa.display3(123);                error!

    p->display4();
    p->product::display4();

    //p->haha();
    p->ppp();
    aa.ppp();
        
    p->destroy();
 #else
    ttest aa;
    func(&aa);
 #endif
    return 0;
}
