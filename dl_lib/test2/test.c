#include <stdlib.h>
#include <stdio.h>

#ifdef USE_DL
#include <dlfcn.h>


#define DL_TEST_SO  "./libtest_so.so"
#define DL_TEST_READ_SO    "read_gblvar_in_test_so"
#define DL_TEST_WRITE_SO  "write_gblvar_in_test_so"


#define DL_TEST_SO2  "./libtest_so2.so"
#define DL_TEST_READ_SO2    "read_gblvar_in_test_so2"
#define DL_TEST_WRITE_SO2  "write_gblvar_in_test_so2"


typedef int (*FUNC_READ)();
typedef void (*FUNC_WRITE)(int var);

int  main(void)
{
    char *perr = NULL;
    
    void* dl_lib_handler_test_so;    
    FUNC_READ  read_handler_test_so;
    FUNC_WRITE write_handler_test_so;  

    void* dl_lib_handler_test_so2;
    FUNC_READ  read_handler_test_so2;
    FUNC_WRITE write_handler_test_so2;
    
    
    printf("open [%s]  . . . ", DL_TEST_SO);

    /*open so 1*/
    dl_lib_handler_test_so = dlopen(DL_TEST_SO, RTLD_LAZY);
    if(!dl_lib_handler_test_so)
        {
        printf("failed \n");
        perr = dlerror();
        if(NULL != perr)
            {
            printf("%s\n", perr);
            }
        return 0;
        }

    printf("success\n");

    printf("open [%s]  . . . ", DL_TEST_SO2);

    /*open so 2*/
    dl_lib_handler_test_so2 = dlopen(DL_TEST_SO2, RTLD_LAZY);
    if(!dl_lib_handler_test_so2)
        {
        printf("failed \n");
        perr = dlerror();
        if(NULL != perr)
            {
            printf("%s\n", perr);
            }
        return 0;
        }

    printf("success\n");

    
    /*get read/write in so 1*/
    read_handler_test_so = (FUNC_READ)dlsym(dl_lib_handler_test_so, DL_TEST_READ_SO);
    perr = dlerror();
    if(NULL != perr)
        {
        printf("%s\n", perr);
        goto closelib;
        }

    write_handler_test_so = (FUNC_READ)dlsym(dl_lib_handler_test_so, DL_TEST_WRITE_SO);
    perr = dlerror();
    if(NULL != perr)
        {
        printf("%s\n", perr);
        goto closelib;
        }


    /*get read/write in so 2*/
    read_handler_test_so2 = (FUNC_READ)dlsym(dl_lib_handler_test_so2, DL_TEST_READ_SO2);
    perr = dlerror();
    if(NULL != perr)
        {
        printf("%s\n", perr);
        goto closelib;
        }

    write_handler_test_so2 = (FUNC_READ)dlsym(dl_lib_handler_test_so2, DL_TEST_WRITE_SO2);
    perr = dlerror();
    if(NULL != perr)
        {
        printf("%s\n", perr);
        goto closelib;
        }


    /*read global var in so 1/2*/
    read_handler_test_so();
    read_handler_test_so2();
    
    /*2 W -> 1 R*/
    write_handler_test_so2(999);
    read_handler_test_so();

     /*1 W -> 2 R*/
    write_handler_test_so(555);
    read_handler_test_so2();   


closelib:
    if(!dl_lib_handler_test_so)
        dlclose(dl_lib_handler_test_so);
    
    if(!dl_lib_handler_test_so2)
        dlclose(dl_lib_handler_test_so2);
    
    return 0;
}


#else
#include "test_so.h"
#include "test_so2.h"

int  main(void)
{
    /*read global var in so 1/2*/
    read_gblvar_in_test_so();
    read_gblvar_in_test_so2();
    
    /*2 W -> 1 R*/
    write_gblvar_in_test_so2(999);
    read_gblvar_in_test_so();

     /*1 W -> 2 R*/
    write_gblvar_in_test_so(555);
    read_gblvar_in_test_so2();   
}

#endif




