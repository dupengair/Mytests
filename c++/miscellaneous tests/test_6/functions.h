#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#ifdef _FUNCTIONS_C
#define _FUNCTIONS_EXT
#else
#define _FUNCTIONS_EXT extern
#endif



#define INFINOVACGI_FUNCTION_CLK



_FUNCTIONS_EXT void INFINOVACGI_FUNCTION_CLK InfinovaCGI_FunctionsCBLK_Sys_Get(void *hnd);
_FUNCTIONS_EXT void INFINOVACGI_FUNCTION_CLK InfinovaCGI_FunctionsCBLK_Sys_Set(void *hnd);

#endif
