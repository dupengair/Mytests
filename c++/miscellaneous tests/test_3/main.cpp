#include "factory.h"


int main()
{
    factory *fac1 = new factory_A();
    product *pdt1 = fac1->CreateProduct("pdt_A");

    factory *fac2 = new factory_B();
    product *pdt2 = fac2->CreateProduct("pdt_B");

    pdt1->destroy();
    pdt2->destroy();

    //delete pdt1;
    //delete pdt2;
    delete fac1;
    delete fac2;
    
    return 0;
}

