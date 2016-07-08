#include <iostream>
#include <map>

#include "CGIProtocol.h"
#include "functions.h"


int xxx = 9;

CGIProtocol* CGIProtocol::instance = NULL;

CGIProtocol* CGIProtocol::GetInstance(void)
{
    if(NULL == instance)
        {
        instance = new CGIProtocol();
        }

    return instance;
}

void CGIProtocol::InitForm(DefineEgiFormFunc callback)
{
    int i = 0;
    for( T_CGIPROTOCOL::iterator iter = varHandler.begin(); iter != varHandler.end(); iter++) 
        {
        callback(&i, (char *)iter->first.c_str(), iter->second);
        i++;
        }

}

CGIProtocol::CGIProtocol()
{
    varHandler[INFINOVACGI_SYS_GET] = InfinovaCGI_FunctionsCBLK_Sys_Get;
    varHandler[INFINOVACGI_SYS_SET] = InfinovaCGI_FunctionsCBLK_Sys_Set;
}

CGIProtocol::~CGIProtocol()
{
}
