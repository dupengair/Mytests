/*main thread : create mmap file*/

#include <sys/ipc.h>
#include <sys/shm.h> 
#include <sys/stat.h>   
#include <fcntl.h>   
#include <stdio.h>   
#include <stdlib.h>   
#include <unistd.h>  
#include <signal.h>
#include <error.h>   
#include <string.h>
#include <sys/file.h>


#define KEY_ID  125
#define BUF_SIZE 1024
#define SHM_FILE  "test_shm.txt"
#define TEST_DEBUG //printf("%s %d\n", __func__, __LINE__)

int alive = 0;

static void 
stop_sig(int signo)
{
	alive = 0;
	printf("stop signal!\n");
}

int test_file(char *file)
{
    int fd = -1;
    struct stat fst;
    int region_size = BUF_SIZE*sizeof(int);
    
    TEST_DEBUG;
    fd = open(file, O_CREAT|O_RDWR);
    if(fd < 0)
        {
        perror("file not exist:");
        fd = open(file, O_CREAT|O_RDWR);
        if(fd < 0)
            {
            perror("open file failed:");
            return -1;
            }
        }
    
    TEST_DEBUG;
    if(ftruncate(fd, region_size) != 0)
        {
        perror("ftruncate :");
        return -1;
        }

    close(fd);

    return 0;
}

int main(void)
{    
    int var_for_test = 10;
    int *shm = NULL;
    int region_size = BUF_SIZE*sizeof(int);
    key_t shkey;
    int shmid;
    

    signal(SIGINT, stop_sig);
    signal(SIGTSTP, stop_sig);
    signal(SIGTERM, stop_sig);

    #ifdef TEST_SHM_1
    if(test_file(SHM_FILE) < 0)
        {
        printf("can not creat file for shm\n");
        return -1;
        }
    #endif
        
    TEST_DEBUG; 
    shkey = ftok(SHM_FILE, KEY_ID);
    if(shkey < 0)
        {
        perror("ftok");
        return -1;
        }
    
    TEST_DEBUG; 
    shmid = shmget(shkey, region_size, IPC_CREAT|0777);  
    if(shmid < 0)
        {
        perror("shmget");
        return -1;
        } 

    TEST_DEBUG; 
    #ifdef TEST_SHM_1
    //shm = shmat(shmid, &var_for_test, 0);  
    shm = shmat(shmid, 0, 0);  
    #else
    shm = shmat(shmid, 0, 0);  
    #endif
    if(shm == (void *)-1)
        {
        perror("shmat");
        return -1;
        }      
   
   
    TEST_DEBUG;
    #ifdef TEST_SHM_1
    alive = 1;

    while(alive)
        {
        var_for_test += 100;
        *shm = var_for_test;      
        printf("test_shm proc1 - set val : %d \n", var_for_test);
        printf("test_shm proc1 - shm val: %d \n", *shm);
        sleep(8);
        }

    printf("test_shm proc1 exit \n");
    #endif

    #ifdef TEST_SHM_2
    alive = 1;

    while(alive)
        {
        var_for_test = *shm; 
        printf("test_shm proc2 - get val : %d \n", var_for_test);

        sleep(3);
        }

    printf("test_shm proc2 exit \n");
    #endif

    #ifdef TEST_SHM_3
    alive = 1;

    while(alive)
        {
        var_for_test = *shm;  
        printf("test_shm proc3 - get val : %d \n", var_for_test);

        sleep(3);
        }

    printf("test_shm proc3 exit \n");
    #endif

    if(shmdt(shm) < 0)
        {
        perror("shmdt");
        }
    
    return 0;
    
}









