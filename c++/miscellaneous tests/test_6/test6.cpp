#include <iostream>
#include <map>
#include "CGIProtocol.h"
#include "Form.h"

/*
int DefineEgiForm(void *http, char *name, CGIHandler form)
{
    std::cout << name << " : " ;
    form(http);

    return 0;
}*/


int main(void)
{
    CGIProtocol* pInfCGI = CGIProtocol::GetInstance();
    pInfCGI->InitForm(DefineEgiForm);
    
    return 0;
}
