/*main thread : create mmap file*/

#include <sys/mman.h>   
#include <sys/stat.h>   
#include <fcntl.h>   
#include <stdio.h>   
#include <stdlib.h>   
#include <unistd.h>  
#include <signal.h>
#include <error.h>   
#include <string.h>
#include <sys/file.h>


#define BUF_SIZE 1024
#define MMAP_FILE  "test_mmap.txt"
#define TEST_DEBUG //printf("%s %d\n", __func__, __LINE__)

int alive = 0;

static void 
stop_sig(int signo)
{
	alive = 0;
	printf("stop signal!\n");
}

int main(void)
{
    int fd = -1;
    int var_for_test = 0;
    struct stat fst;
    int *p_maped = NULL;
    int region_size = BUF_SIZE*sizeof(int);

    signal(SIGINT, stop_sig);
    signal(SIGTSTP, stop_sig);
    signal(SIGTERM, stop_sig);

    TEST_DEBUG;
    fd = open(MMAP_FILE, O_CREAT|O_RDWR);
    if(fd < 0)
        {
        perror("open mmap file :");
        return -1;
        }
    
    TEST_DEBUG;
    if(ftruncate(fd, region_size) != 0)
        {
        perror("ftruncate :");
        return -1;
        }

    TEST_DEBUG;
    if(fstat(fd, &fst) == -1)
        {
        perror("fstat :");
        goto failed;
        }
    
    TEST_DEBUG;    
    #ifdef TEST_MMAP_1
    p_maped = (int *)mmap(NULL, region_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);    
    //p_maped = (int *)mmap(&var_for_test, region_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);    
    //*p_maped = &var_for_test; 
    printf("test_mmap proc1 - val addr: %x \n", &var_for_test);
    printf("test_mmap proc1 - p_maped : %x \n", p_maped);
    #endif

     #ifdef TEST_MMAP_2
     p_maped = (int *)mmap(NULL, region_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
     #endif

     #ifdef TEST_MMAP_3
     p_maped = (int *)mmap(NULL, region_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);    
     #endif

     if(p_maped == NULL)
        {
        perror("mmap :");
        goto failed;
        }     
    
    close(fd);
    
    TEST_DEBUG;
    #ifdef TEST_MMAP_1
    alive = 1;

    while(alive)
        {
        var_for_test += 100;
        *p_maped = var_for_test;      
        printf("test_mmap proc1 - set val : %d \n", var_for_test);
        printf("test_mmap proc1 - p_maped val: %d \n", *p_maped);
        sleep(8);
        }

    printf("test_mmap proc1 exit \n");
    #endif

    #ifdef TEST_MMAP_2
    alive = 1;

    while(alive)
        {
        TEST_DEBUG;
        var_for_test = *p_maped; 
        //var_for_test = *(int *)(*p_maped); 
        TEST_DEBUG;
        printf("test_mmap proc2 - get val : %d \n", var_for_test);

        sleep(3);
        }

    printf("test_mmap proc2 exit \n");
    #endif

    #ifdef TEST_MMAP_3
    alive = 1;

    while(alive)
        {
        var_for_test = *p_maped; 
        //var_for_test = *(int *)(*p_maped); 
        printf("test_mmap proc3 - get val : %d \n", var_for_test);

        sleep(3);
        }

    printf("test_mmap proc3 exit \n");
    #endif

    
    return 0;
    

failed:
       if(fd > 0)
        {
        printf("failed to run : close fd\n");
        close(fd);
        }
}









