#include "factory.h"




int main()
{
    factory *fac1 = new factory_A();
    product *pdt1 = fac1->CreateProduct("pdt_A");

    pdt1->baseop();

    delete fac1;
    
    return 0;
}

