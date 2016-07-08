
#define _FUNCTIONS_C

#include <iostream>
#include "functions.h"




void INFINOVACGI_FUNCTION_CLK InfinovaCGI_FunctionsCBLK_Sys_Get(void *hnd)
{
    std::cout << "in InfinovaCGI_FunctionsCBLK_Sys_Get : " << *(int *)hnd << std::endl;
}


void INFINOVACGI_FUNCTION_CLK InfinovaCGI_FunctionsCBLK_Sys_Set(void *hnd)
{
    std::cout << "in InfinovaCGI_FunctionsCBLK_Sys_Set : " << *(int *)hnd << std::endl;
}





