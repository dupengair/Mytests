#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//#define __TEST_NOMAIN
//#define __TEST_DTORS
//#define __TEST_ATEXIT
//#define __TEST_LONGJUMP
//#define __TEST_EXIT
#define __TEST_PRINTF

#ifdef __TEST_NOMAIN
#include <asm/unistd.h>

int errno;
_syscall3(int write, int fd, char * data, int len);
_syscall1(int exit, int status);

syscall(__NR_start())
{
            syscall(__NR_write, 0, "Hello world!\\n", 13);
            syscall(__NR_exit(0));
}
#endif

#ifdef __TEST_DTORS

char *glob;
void exit_func(void)
{
    printf("%s\n", glob);
}
static void before(void) __attribute__((constructor));
static void after(void) __attribute__((destructor));

int function(int a, int b, int c)
{
        char buffer[14];
        int     sum;
        int *ret;

        ret = buffer + 64;
        (*ret) += 13;
        sum = a + b + c;
        return sum;
}

void main()
{
        printf("start main\n");
        int x;

        x=0;
        function(1,2,3);
        x=1;

        printf("%d\n",x);
        printf("before : %p. \n", before);
        printf("after : %p. \n", after);      


}
static void before(void)
{
    printf("before main\n");
}

static void after(void)
{
    printf("after main\n");
}
#endif

#ifdef __TEST_ATEXIT

char *glob;
void exit_func(void)
{
    printf("%s\n", glob);
}

void main()
{
        atexit(exit_func);
        glob = "exiting.\n";
}

#endif

#ifdef __TEST_LONGJUMP
#include <setjmp.h>
jmp_buf buf;
void g(int n);
void h(int n);
int n = 6;

void f(void) 
    {
    setjmp(buf);
    g(n);
    }

void g(int n)
    {
    h(n);
    }

void h(int n)
    {
    longjmp(buf, 2);
    }
#endif

#ifdef __TEST_EXIT

extern char **environ;

static void myexit1(void)
{
    printf("myexit1\n");
}

static void myexit2(void)
{
    printf("myexit2\n");
}

int main()
{
    if(atexit(myexit1) != 0)
        {
        printf("can't register myexit1\n");
        }

    if(atexit(myexit2) != 0)
        {
        printf("can't register myexit2\n");
        }


    char *addr = alloca(100);
        
    while(2)
        {
        sleep(3);
        }

    free(addr);
}

#endif

#ifdef __TEST_PRINTF

int main(int argc, char * argv[])
{

#if 0
    static unsigned char shellcode[1024] = "\x90\x09\x09\x09\x09\x09/bin/sh";

    int i;
    unsigned char format_str[1024];

    strcpy(format_str, "\xaa\xaa\xaa\xaa");
    strcpy(format_str, "\xb4\x9b\x04\x08");
    strcpy(format_str, "\xcc\xcc\xcc\xcc");
    strcpy(format_str, "\xb6\x9b\x04\x08");

    for(i=0; i<3; i++)
        {
        strcat(format_str, "%x");
        }

    printf(format_str);
    exit(0);
#else

int i,j,k=0;

printf("%4$d %5$d %6$d \n", &k, &j, &i, 5, 6, 7);

printf("i = %d, j = %d, k = %d\n", i, j, k);

char *buf="123456879";
printf("buf = %.3s\n", buf);

#endif
}


#endif

