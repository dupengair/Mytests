#include <stdlib.h>
#include <stdio.h>

int global_var = 0;

int test_lib_print()
{
     return global_var;
}

void test_lib_write(int var)
{
     global_var = var;
}

