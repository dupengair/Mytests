#include <stdlib.h>
#include <stdio.h>

#include "test_libexosip.h"


void read_gblvar_in_plugin()
{
    //printf("%s : %d\n", __func__, test_lib_print());
    printf("%s \n", __func__);
}


void write_gblvar_in_plugin(int var)
{
    //test_lib_write(var);
    printf("%s : %d\n", __func__, var);
}

