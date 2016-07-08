#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



typedef struct
{
    void (*func)(void);
}test_st;

void st_func(void)
{
    printf("%s : %s : %d\n", __FILE__, __func__, __LINE__);
}

test_st st = 
{
    .func = st_func,
};

test_st* main_func(void)
{
    return &st;
}

void main(void)
{
    main_func()->func();
}
