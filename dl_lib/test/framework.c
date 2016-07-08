#include <stdlib.h>
#include <stdio.h>

#ifdef USE_DL
#include <dlfcn.h>


#define DL_TEST  "./libtest_plugin.so"
#define DL_TEST_READ    "read_gblvar_in_plugin"
#define DL_TEST_WRITE  "write_gblvar_in_plugin"


#define DL_TEST2  "./libtest_sipmodule.so"
#define DL_TEST_READ2    "read_gblvar_in_sipmodule"
#define DL_TEST_WRITE2  "write_gblvar_in_sipmodule"


typedef void (*FUNC_READ)();
typedef void (*FUNC_WRITE)(int var);

int  main(void)
{
    char *perr = NULL;
    
    void* dl_lib_handler;    
    FUNC_READ  read_handler;
    FUNC_WRITE write_handler;  

    void* dl_lib_handler2;
    FUNC_READ  read_handler2;
    FUNC_WRITE write_handler2;
    
    
    printf("open [%s]  . . . ", DL_TEST);

    /*open so 1*/
    dl_lib_handler = dlopen(DL_TEST, RTLD_LAZY);
    if(!dl_lib_handler)
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

    printf("open [%s]  . . . ", DL_TEST2);

    /*open so 2*/
    dl_lib_handler2 = dlopen(DL_TEST2, RTLD_LAZY);
    if(!dl_lib_handler2)
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
    read_handler = (FUNC_READ)dlsym(dl_lib_handler, DL_TEST_READ);
    perr = dlerror();
    if(NULL != perr)
        {
        printf("%s\n", perr);
        goto closelib;
        }

    write_handler = (FUNC_READ)dlsym(dl_lib_handler, DL_TEST_WRITE);
    perr = dlerror();
    if(NULL != perr)
        {
        printf("%s\n", perr);
        goto closelib;
        }


    /*get read/write in so 2*/
    read_handler2 = (FUNC_READ)dlsym(dl_lib_handler2, DL_TEST_READ2);
    perr = dlerror();
    if(NULL != perr)
        {
        printf("%s\n", perr);
        goto closelib;
        }

    write_handler2 = (FUNC_READ)dlsym(dl_lib_handler2, DL_TEST_WRITE2);
    perr = dlerror();
    if(NULL != perr)
        {
        printf("%s\n", perr);
        goto closelib;
        }

    

    /*read global var in so 1/2*/
    read_handler();
    read_handler2();
    
    /*2 W -> 1 R*/
    write_handler2(999);
    read_handler();

     /*1 W -> 2 R*/
    write_handler(555);
    read_handler2();   


closelib:
    if(!dl_lib_handler)
        dlclose(dl_lib_handler);
    
    if(!dl_lib_handler2)
        dlclose(dl_lib_handler2);
    
    return 0;
}


#else
#include "test_plugin.h"
#include "test_sipmodule.h"

int  main(void)
{
    /*read global var in so 1/2*/
    read_gblvar_in_plugin();
    read_gblvar_in_sipmodule();
    
    /*2 W -> 1 R*/
    write_gblvar_in_sipmodule(999);
    read_gblvar_in_plugin();

     /*1 W -> 2 R*/
    write_gblvar_in_plugin(555);
    read_gblvar_in_sipmodule();   
}

#endif




