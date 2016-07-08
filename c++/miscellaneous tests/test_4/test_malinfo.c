#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


void getMemStatus()
{
    struct mallinfo MI = mallinfo();
    printf("Ar = %u - MMap = %u - Mem uordblks = %u - Free fordblks = %u (ordblks %u)\n", MI.arena, MI.hblkhd, MI.uordblks, MI.fordblks, MI.ordblks);
}


int main()
{
    while(1)
        {
        getMemStatus();
        sleep(1);
        }
}
