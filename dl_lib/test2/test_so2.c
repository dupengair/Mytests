#include <stdlib.h>
#include <stdio.h>

#ifdef USE_DL
#include <dlfcn.h>


#define DL_TEST_LIB2  "./libtest_lib.so"
#define DL_TEST_LIB_PRINT2    "test_lib_print"
#define DL_TEST_LIB_WRITE2  "test_lib_write"

typedef int (*FUNC_LIB_READ2)();
typedef void (*FUNC_LIB_WRITE2)(int var);


void read_gblvar_in_test_so2()
{
    char *perr = NULL;
    
    void* dl_lib_handler_test_so;    
    FUNC_LIB_READ2  read_handler_test_so;
    FUNC_LIB_WRITE2 write_handler_test_so;  
    
    printf("open [%s]  . . . ", DL_TEST_LIB2);

    /*open so 1*/
    dl_lib_handler_test_so = dlopen(DL_TEST_LIB2, RTLD_LAZY);
    if(!dl_lib_handler_test_so)
        {
        printf("failed \n");
        perr = dlerror();
        if(NULL != perr)
            {
            printf("%s\n", perr);
            }
        return;
        }

    printf("success\n");


    /*get read/write in so 1*/
    read_handler_test_so = (FUNC_LIB_READ2)dlsym(dl_lib_handler_test_so, DL_TEST_LIB_PRINT2);
    perr = dlerror();
    if(NULL != perr)
        {
        printf("%s\n", perr);
        goto closelib;
        }

    write_handler_test_so = (FUNC_LIB_WRITE2)dlsym(dl_lib_handler_test_so, DL_TEST_LIB_WRITE2);
    perr = dlerror();
    if(NULL != perr)
        {
        printf("%s\n", perr);
        goto closelib;
        }
    
    
    printf("%s : %d\n", __func__, read_handler_test_so());

closelib:
    if(!dl_lib_handler_test_so)
        dlclose(dl_lib_handler_test_so);
}

    
void write_gblvar_in_test_so2(int var)
{
    char *perr = NULL;
    
    void* dl_lib_handler_test_so;    
    FUNC_LIB_READ2  read_handler_test_so;
    FUNC_LIB_WRITE2 write_handler_test_so;  
    
    printf("open [%s]  . . . ", DL_TEST_LIB2);

    /*open so 1*/
    dl_lib_handler_test_so = dlopen(DL_TEST_LIB2, RTLD_LAZY);
    if(!dl_lib_handler_test_so)
        {
        printf("failed \n");
        perr = dlerror();
        if(NULL != perr)
            {
            printf("%s\n", perr);
            }
        return;
        }

    printf("success\n");


    /*get read/write in so 1*/
    read_handler_test_so = (FUNC_LIB_READ2)dlsym(dl_lib_handler_test_so, DL_TEST_LIB_PRINT2);
    perr = dlerror();
    if(NULL != perr)
        {
        printf("%s\n", perr);
        goto closelib;
        }

    write_handler_test_so = (FUNC_LIB_WRITE2)dlsym(dl_lib_handler_test_so, DL_TEST_LIB_WRITE2);
    perr = dlerror();
    if(NULL != perr)
        {
        printf("%s\n", perr);
        goto closelib;
        }
    
    write_handler_test_so(var);
    printf("%s : %d\n", __func__, var);
    
closelib:
    if(!dl_lib_handler_test_so)
        dlclose(dl_lib_handler_test_so);
    
}

#else
#include "test_so2.h"


void read_gblvar_in_test_so2()
{
    printf("%s : %d\n", __func__, test_lib_print());
}


void write_gblvar_in_test_so2(int var)
{
    test_lib_write(var);
    printf("%s : %d\n", __func__, var);
}

#endif
