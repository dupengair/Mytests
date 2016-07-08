#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int func(int aa)
{
    return aa;
}

inline void test_func(int para)
{
    printf("para = %d\n", para);
}

void printbuf(char *buf, int size)
{
    for(int i = 0; i < size; i++)
        {
        printf("%d ", buf[i]);
        }

     printf("\n");
}

int main()
{
    //test_func(func(33));

    char buf[6] = {0};
    char buf1[6] = {0};
    unsigned short type = 259;

    *(unsigned short*)(buf + 2) = type;
    memcpy(buf1 + 2, &type, 2);

    printbuf(buf, sizeof(buf));
    printbuf(buf1, sizeof(buf1));
    
    return 0;
}
